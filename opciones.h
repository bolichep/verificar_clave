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

#ifndef OPCIONES_H
#define OPCIONES_H

#include <unistd.h> //getopt
#include <stdlib.h> // exit
#include <string.h> // strtok
#include <pwd.h>    // getpwuid
#include <glib.h>
#include <glib/gprintf.h>


extern char * optarg;

// Simula alarm() con sleep()
typedef struct Alarma {
    int tiempo; // en segundos
    int repetir;
} Alarma;



typedef struct Accion {
    gboolean activo; // mostrar botón 'Cambiar clave...'
    gchar * nombre;
} Accion;



typedef struct Opciones {
    gchar * usuario;
    gchar * clave;
    gchar * mensaje;
    gchar * titulo;
    Accion accion;
    Alarma alarma;
} Opciones;



void opciones (int argc, char * argv [], Opciones * op);

static _Noreturn void ayuda ();

static void opciones_alarma (Opciones * op);

#endif
/* vim: set ts=4 sw=4 tw=80 et :*/
