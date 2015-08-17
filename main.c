/*
	Copyright (C) 2015 Daniel T. Borelli

	This file is part of verificar_clave.

    verificar_clave is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    verificar_clave is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with verificar_clave.  If not, see <http://www.gnu.org/licenses/>.
*/

//#include <unistd.h>
//#include <pwd.h>

#include "notify_wrap.h"
#include "pam_auth.h"
#include "desktops.h"
#include "opciones.h"


static GMainLoop * main_loop = NULL;



static void accion_terminada (GObject * object,
                        GAsyncResult * res,
                        gpointer datos)
{

    gboolean * accion = (gboolean *) datos;
    *accion = ! *accion;
}



// Básicamente, oculta el botón 'Cambiar clave..."
//  si el proceso de administrador de claves esta abierto.
static void accion_esperar (GSubprocess const * const  subproc, gpointer dato)
{
    gboolean * const accion = (gboolean * const ) dato; // opciones.accion

    *accion = FALSE; // ref: accion_terminada

    g_subprocess_wait_async (subproc, NULL, accion_terminada, dato);
}



// * Dependencias:
// MATE : mate-system-tools
// GNOME: gnome-system-tools 
// XFCE : mate-system-tools
static void accion_de_notificacion (NotifyNotification * notify,
        char const * const action, gpointer dato)
{
    GSubprocessLauncher * proc = NULL;
    
    if (NULL == (proc = g_subprocess_launcher_new (G_SUBPROCESS_FLAGS_NONE)))
    {
        LOG ("Error al crear el sub-proceso.");
        return;
    }

    GError * error = NULL;
    gchar const * const admin = desktop_admin (); 
    GSubprocess * subproc = g_subprocess_launcher_spawn (proc, &error, admin, NULL);

    Comprobar (NULL != subproc, "Error al ejecutar el sub-proceso %s", admin);

    accion_esperar (subproc, dato);

    g_clear_object (&subproc);
    g_clear_object (&proc);

    return;

error:
    g_error_free (error);
    g_clear_object (&proc);
}



static gboolean autenticar_notificar (Opciones const * const op)
{
    gchar * pass_cpy = g_strdup (op->clave);

    if (PAM_SUCCESS == pam_auth_user_pass (op->usuario, pass_cpy))
    {
        // Con .time = NOTIFY_EXPIRES_NEVER, se muestra un cuadro de
        // diálogo con botones. 
        NotifyExtra extra = {
            .time = NOTIFY_EXPIRES_DEFAULT,
            .urgency = NOTIFY_URGENCY_CRITICAL,
            .callback = (op->accion) ? accion_de_notificacion : NULL,
            .dato = & op->accion
        };

        notify_wrap_show (op->titulo, op->mensaje, "gtk-dialog-warning", &extra);

        return TRUE;
    }

    return FALSE;
}



static char * const nombre_usuario_actual () 
{
    uid_t const usuario_id = geteuid ();
    struct passwd const * const datos = getpwuid (usuario_id);

    gchar const * const nombre = g_strdup (datos->pw_name);

    endpwent ();

    return nombre;
}



static gpointer autenticar_notificar_thread (gpointer data)
{
    Opciones const * const op = (Opciones const * const) data;
    gboolean autenticado = FALSE;

    for (unsigned int i = 0; op->alarma.tiempo >= 0 && i <= op->alarma.repetir; ++i) 
    {
        if ( TRUE == (autenticado = autenticar_notificar (op)))
        {
            sleep (op->alarma.tiempo);
        }
    }

    // dirty-hack,
    // Antes de terminar, esperar a que la notificación se cierre.
    // Esto evita el desfase entre el servidor de notificaciones y el
    // programa.
    for (; autenticado && ! notify_wrap_is_closed () ;)
    {
        sleep (1); //seg
    }

    if (autenticado) 
    {
        notify_wrap_end ();
    }

    g_main_loop_quit (main_loop);

    return NULL;
}



int main (int argc, char * argv []) 
{
    char * const nombre_usuario = nombre_usuario_actual ();

    Opciones op = {
        .usuario  = nombre_usuario,
        .clave    = "alumno",
        .mensaje  = "Por favor, debes cambiar la clave.",
        .titulo   = nombre_usuario,
        .accion   = TRUE,
        .alarma   = (Alarma){ .tiempo = 0, .repetir = 1 } 
    };

    opciones (argc, argv, &op);

    GThread * thread = g_thread_new (NULL, autenticar_notificar_thread, &op);

    Comprobar (NULL != thread, "Fallo el inicio del thread");

    main_loop = g_main_loop_new (NULL, FALSE);

    g_main_loop_run (main_loop);

error:
    return EXIT_FAILURE;
}
/* vim: set ts=4 sw=4 tw=80 et :*/
