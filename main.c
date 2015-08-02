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

#include <unistd.h>
#include <pwd.h>

#include "notify_wrap.h"
#include "pam_auth.h"

extern char * optarg;

// Simula alarm() con sleep()
typedef struct Alarma {
    int tiempo; // en segundos
    int repetir;
} Alarma;

typedef struct Opciones {
    char * usuario;
    char * clave;
    char * mensaje;
    char * titulo;
    Alarma alarma;
} Opciones;


_Noreturn void ayuda () 
{
    char const contenido [] = "Las opciones son:\n"
    "-u para el usuario\n"
    "-c para la clave\n"
    "-m para el mensaje\n"
    "-t para el título del mensaje\n"
    "-a alarma cada segundos:repetir\n"
    "-h muestra la ayuda.";

    printf ("Ayuda:\n%s\n", contenido);

    exit(EXIT_SUCCESS);
}


static void opciones_alarma (Opciones * op) 
{
    char const * const delim = ":";

    char * tok = strtok (optarg, delim);
    if (tok != NULL)
    {
        op->alarma.tiempo = atoi (tok);
    }

    tok = strtok (NULL, delim);
    if (tok != NULL)
    {
       int valor = atoi (tok);
       op->alarma.repetir =  ( valor <= 0) ? 1 : valor;
    }
}

// Soporta:
// -u para usuario 
// -c para clave
// -m mensaje
// -t titulo del mensaje
// -a alarma
// -h ayuda
static void opciones (int argc, char * argv [], Opciones * op)
{
    int opt = 0;

    while ((opt = getopt (argc, argv, "u:c:t:m:a:h")) != -1) 
    {
        switch (opt) 
        {
            case 'u': 
                if (optarg != NULL)
                    op->usuario = strdup (optarg);
                break;
            case 'c':
                if (optarg != NULL)
                    op->clave = strdup (optarg);
                break;
            case 'm':
                if (optarg != NULL)
                    op->mensaje = strdup (optarg);
                break;
            case 't':
                if (optarg != NULL) 
                    op->titulo = strdup (optarg);
                break;
            case 'a':
                if (optarg != NULL) 
                    opciones_alarma (op);
                break;
            default: // también implica -h
                ayuda();
                break;
        }
    }
}


static _Bool autenticar_notificar (Opciones const * const op)
{
    if (PAM_SUCCESS == pam_auth_user_pass (op->usuario, op->clave))
    {
        // Con .time = NOTIFY_EXPIRES_NEVER, se muestra un cuadro de
        // diálogo con botones. 
        NotifyExtra extra = {
            .time = NOTIFY_EXPIRES_DEFAULT,
            .urgency = NOTIFY_URGENCY_CRITICAL
        };

        notify_wrap_show (op->titulo, op->mensaje, "gtk-dialog-warning", &extra);
        
        return TRUE;
    }

    return FALSE;
}


char * const nombre_usuario_actual () 
{
    uid_t const usuario_id = geteuid ();
    struct passwd const * const datos = getpwuid (usuario_id);

    return strdup (datos->pw_name);
}


int main (int argc, char * argv []) 
{
    char * const nombre_usuario = nombre_usuario_actual ();

    Opciones op = {
        .usuario  = nombre_usuario,
        .clave    = "alumno",
        .mensaje  = "Por favor, debes cambiar la clave.",
        .titulo   = nombre_usuario,
        .alarma   = (Alarma){ .tiempo = 0, .repetir = 1 } 
    };

    opciones (argc, argv, &op);

    for (unsigned int i = 0; op.alarma.tiempo >= 0 && i <= op.alarma.repetir; ++i) 
    {
        if ( TRUE == autenticar_notificar (&op))
        {
            sleep (op.alarma.tiempo);
            continue;
        }

        free (nombre_usuario);
        return EXIT_FAILURE;
    }

    free (nombre_usuario);
    return EXIT_SUCCESS;
}
/* vim: set ts=4 sw=4 tw=80 et :*/
