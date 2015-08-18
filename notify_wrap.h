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

#ifndef NOTIFY_WRAP_H
#define NOTIFY_WRAP_H

#include <libnotify/notify.h>
#include <string.h> // strcmp

#include "log.h"

static NotifyNotification * notify_obj = NULL;

typedef struct NotifyExtra {
    gint time;
    NotifyUrgency urgency;
    NotifyActionCallback callback;
    gpointer dato; //extra de un extra :)
} NotifyExtra;


void notify_wrap_show (gchar const * summary,
        gchar const * body,
        gchar const * const icon,
        NotifyExtra const * extra);

gboolean notify_wrap_is_closed ();
static int notify_wrap_init ();
void notify_wrap_end ();
static void remove_ampersand (gchar const * str);
static void extra_init ();
static gboolean const support_actions ();
#endif 
/* vim: set ts=4 sw=4 tw=80 et :*/
