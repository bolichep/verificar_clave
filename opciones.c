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
#include "opciones.h"


// Soporta:
// -u para usuario 
// -c para clave
// -m mensaje
// -t titulo del mensaje
// -a alarma
// -h ayuda
// -b sin botón "Cambiar clave..."
void opciones (int argc, char * argv [], Opciones * op)
{
    int opt = 0;

    while ((opt = getopt (argc, argv, "u:c:t:m:a:hb")) != -1) 
    {
        switch (opt) 
        {
            case 'u': 
                if (optarg != NULL)
                    op->usuario = g_strdup (optarg);
                break;
            case 'c':
                if (optarg != NULL)
                    op->clave = g_strdup (optarg);
                break;
            case 'm':
                if (optarg != NULL)
                    op->mensaje = g_strdup (optarg);
                break;
            case 't':
                if (optarg != NULL) 
                    op->titulo = g_strdup (optarg);
                break;
            case 'a':
                if (optarg != NULL) 
                    opciones_alarma (op);
                break;
            case 'b':
                op->accion = FALSE;
                break;
            default: // también implica -h
                ayuda();
                break;
        }
    }
}



void opciones_alarma (Opciones * op) 
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



_Noreturn void ayuda () 
{
    char const contenido [] = "Las opciones son:\n"
    "-u para el usuario\n"
    "-c para la clave\n"
    "-m para el mensaje\n"
    "-t para el título del mensaje\n"
    "-a alarma cada segundos:repetir\n"
    "-b no mostrar botón de acción \"Cambiar clave...\"\n"
    "-h muestra la ayuda.";

    printf ("Ayuda:\n%s\n", contenido);

    exit(EXIT_SUCCESS);
}
/* vim: set ts=4 sw=4 tw=80 et :*/
