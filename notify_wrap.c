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

void notify_wrap_show (char * summary, 
        char * body, 
        char const * const icon, 
        NotifyExtra const * extra)
{
    remove_ampersand (summary);
    remove_ampersand (body);

    if (0 == notify_wrap_init ())
    {
        return;
    }

    if (notify_obj == NULL)
    {
        notify_obj = notify_notification_new (summary, body, icon);

        if (NULL == notify_obj)
        {
            notify_uninit ();
            return;
        }

        extra_init (extra);
    }
    else
    {
        notify_notification_update (notify_obj, summary, body, icon);
    }

    GError * err = NULL;
    if (!notify_notification_show (notify_obj, &err))
    {
        g_error_free (err);
        notify_wrap_end ();
    }
}


void extra_init (NotifyExtra const * const extra)
{
    if (extra == NULL)
    {
        return;
    }
    notify_notification_set_timeout (notify_obj, extra->time);
    notify_notification_set_urgency (notify_obj, extra->urgency);
    
    if (support_actions () && extra->callback != NULL)
    {
        notify_notification_add_action (notify_obj,
                "open",
                "Cambiar clave...",
                extra->callback,
                NULL,
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
void remove_ampersand (char * str)
{
    if (str != NULL)
    {
        char * ptr = str;
        while (*ptr++)
        {
            if (*ptr == '&') { *ptr = ' '; }
        }
    }
}
/* vim: set ts=4 sw=4 tw=80 et :*/
