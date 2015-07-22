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

#include "pam_auth.h"

static int conv (int num_msg, pam_message const ** msg, pam_response ** resp, void * appdata_ptr)
{
    pam_response * reply = malloc (sizeof (pam_response));

    reply->resp = (char *)appdata_ptr;
    reply->resp_retcode = 0;
    *resp = reply;
    return PAM_SUCCESS;
}

int pam_auth_user_pass (char const * const user, char const * const pass)
{
    struct pam_conv pamc = { conv, strdup(pass) };
    pam_handle_t* pamh = NULL; 
    int retval = PAM_ABORT;

    if ( (retval = pam_start ("login", user, &pamc, &pamh) ) == PAM_SUCCESS)
    {
        retval = pam_authenticate (pamh, 0);
    }

    LOG ( pam_strerror (pamh, retval) );
    pam_end (pamh, 0); 
    return retval;
}

/* vim: set ts=4 sw=4 tw=80 et :*/
