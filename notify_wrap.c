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

void notify_wrap_show (gchar const * summary,
        gchar const * body,
        gchar const * const icon,
        NotifyExtra const * extra)
{
    remove_ampersand (summary);
    remove_ampersand (body);

    Comprobar ( 0 != notify_wrap_init (), return,
            "Fallo en iniciar notify_wrap_init")

    if (notify_obj == NULL)
    {
        notify_obj = notify_notification_new (summary, body, icon);

        // TODO: a confirmar posible bug: ¿ es g_object_unref safe si
        // notify_obj ya es NULL ?
        Comprobar ( NULL != notify_obj, goto error_notification_new,
                "Fallo en crear nueva instancia de notify_notification_new");
    }
    else
    {
        notify_notification_update (notify_obj, summary, body, icon);
    }

    extra_init (extra);

    GError * err = NULL;
    gboolean const is_show = notify_notification_show (notify_obj, &err);

    Comprobar (FALSE != is_show, goto error_notification_show,
            "Fallo en mostrar la notificación");

    return;

error_notification_show:

    g_error_free (err);

error_notification_new:

    notify_wrap_end();
}



void extra_init (NotifyExtra const * const extra)
{
    if (extra == NULL)
    {
        return;
    }

    notify_notification_clear_actions (notify_obj);
    notify_notification_set_timeout (notify_obj, extra->time);
    notify_notification_set_urgency (notify_obj, extra->urgency);
    
    if (support_actions () && extra->callback != NULL)
    {
        notify_notification_add_action (notify_obj,
                "open",
                "Cambiar clave...",
                extra->callback,
                extra->dato,
                NULL);
    }
}



gboolean const support_actions ()
{
    g_assert (notify_obj != NULL);

    GList * caps = notify_get_server_caps ();
    gboolean ret = FALSE;

    if (g_list_find_custom( caps, "actions", (GCompareFunc) strcmp))
    {
        ret = TRUE;
    }

    g_list_foreach (caps, (GFunc) g_free, NULL);
    g_list_free (caps);

    return ret;
}



// Sólo falla si se acabaron todas las instancias posibles.
int notify_wrap_init ()
{
    if (!notify_is_initted ())
    {
        if (!notify_init ("verificar_clave"))
        {
            return 0;
        }
    }
    return 1;
}



void notify_wrap_end ()
{
    g_object_unref (G_OBJECT (notify_obj));

    notify_obj = NULL;

    notify_uninit ();
}



//This fix gtk &amp error
void remove_ampersand (gchar const * str)
{
    g_assert (NULL != str);

    gchar * find = NULL;

    while (NULL != (find = g_strrstr (str, "&")))
    {
        *find = ' ';
    }
}



gboolean notify_wrap_is_closed () 
{
    g_assert (notify_obj != NULL);

    return -1 != notify_notification_get_closed_reason (notify_obj);
}


/* vim: set ts=4 sw=4 tw=80 et :*/
