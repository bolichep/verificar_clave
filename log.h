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

#ifndef LOG_H
#define LOG_H 

#include <syslog.h>

#define LOG(...) {                                  \
    char * msg = NULL;                              \
    asprintf (&msg, __VA_ARGS__);                   \
    syslog (LOG_ERR, "#Func:%s #Line:%d #Msg:%s",   \
            __func__ , __LINE__ , msg);             \
    free (msg);                                     \
}


// En caso que valor sea verdadero: se escribe el LOG
// y se ejecuta la accion.
#define Comprobar(valor, accion, ...) {             \
    if (! (valor)) {                                \
        LOG(__VA_ARGS__);                           \
        accion;                                     \
    }                                               \
}
#endif
/* vim: set ts=4 sw=4 tw=80 et :*/
