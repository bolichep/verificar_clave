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

#include "notify_wrap.h"
#include "pam_auth.h"

// Soporta:
// -u para usuario 
// -c para clave
static void opciones (int argc, char* argv [], 
        char const ** usuario, char const ** clave)
{
    int opt = 0;

    while ( (opt = getopt (argc, argv, "u:c:") ) != -1) {
        switch (opt) {
            case 'u': 
                if (optarg != NULL) {
                    *usuario = strdup (optarg);
                    break;
                }
            case 'c':
                if (optarg != NULL) {
                    *clave = strdup (optarg);
                    break;
                }
        }
    }
}


int main ( int argc, char * argv [] ) 
{
    char const * usuario  = "alumno";
    char const * clave    = "alumno";

    opciones ( argc, argv, &usuario, &clave);

    if ( PAM_SUCCESS == pam_auth_user_pass (usuario, clave) )
    {
        notify_wrap_show ("Huayra", "Debe cambiar la clave", "gtk-dialog-warning");
    }
}
/* vim: set ts=4 sw=4 tw=80 et :*/
