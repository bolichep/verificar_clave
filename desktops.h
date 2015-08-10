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
#ifndef DESKTOPS_H
#define DESKTOPS_H

#include <glib.h>

typedef enum { XFCE=0, MATE, GNOME, UKNOWN, NUM} DesktopType;

typedef struct Admin {
    DesktopType type;
    gchar const * const name;
} Admin;


static Admin const * const admin_list (DesktopType type);

gchar const * const desktop_admin ();

#endif
/* vim: set ts=4 sw=4 tw=80 et :*/
