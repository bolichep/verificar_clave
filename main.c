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

#include "notify_wrap.h"
#include "pam_auth.h"

extern char * optarg;

typedef struct Opciones {
    char * usuario;
    char * clave;
    char * mensaje;
    char * titulo;
} Opciones;

// Soporta:
// -u para usuario 
// -c para clave
// -m mensaje
// -t titulo del mensaje
static void opciones (int argc, char* argv [], Opciones * op)
{
    int opt = 0;

    while ( (opt = getopt (argc, argv, "u:c:t:m:") ) != -1) 
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
        }
    }
}


int main ( int argc, char * argv [] ) 
{
    Opciones op = {
        .usuario    = "alumno",
        .clave      = "alumno",
        .mensaje    = "Por favor, debes cambiar la clave.",
        .titulo     = "Huayra"

    };

    opciones ( argc, argv, &op);

    if ( PAM_SUCCESS == pam_auth_user_pass (op.usuario, op.clave) )
    {
        // Nota:
        // Con .time = NOTIFY_EXPIRES_NEVER, se muestra un cuadro de
        // diálogo con botones. 
        NotifyExtra extra = { .time = NOTIFY_EXPIRES_DEFAULT, .urgency = NOTIFY_URGENCY_CRITICAL};

        notify_wrap_show (op.titulo, op.mensaje, "gtk-dialog-warning", &extra);
    }
}
/* vim: set ts=4 sw=4 tw=80 et :*/
