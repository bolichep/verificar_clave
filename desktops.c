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

#include "desktops.h"

Admin const * const admin_list (DesktopType type)
{
    static Admin admins [NUM] = { 
        { XFCE     , "/usr/bin/mate-users-admin" },
        { MATE     , "/usr/bin/mate-users-admin" },
        { GNOME    , "/usr/bin/users-admin"      },
        { UKNOWN   , "/usr/bin/mate-users-admin" },
    };

    return & admins [type];
}



gchar const * const desktop_admin (Accion const * const accion)
{
    if (NULL == accion->nombre)
    {
        return desktop_from_env ();
    }
    else
    {
        return accion->nombre;
    }
}




gchar const * const desktop_from_env ()
{
   gchar const * admin = NULL;

    gchar ** env = g_get_environ ();

    gchar const * const current = g_environ_getenv (env, "XDG_CURRENT_DESKTOP");

    g_assert (current != NULL);

    if (! g_strcmp0 (current, "MATE"))
    {
        admin = admin_list (MATE)->name;
    } 
    else if (! g_strcmp0 (current, "XFCE"))
    {
        admin = admin_list (XFCE)->name;
    }
    else if (! g_strcmp0 (current, "GNOME"))
    {
        admin = admin_list (GNOME)->name;
    }
    else 
    {
        admin = admin_list (UKNOWN)->name;
    }

    g_strfreev (env);

    g_assert (admin != NULL);

    return admin;


}

/* vim: set ts=4 sw=4 tw=80 et :*/
