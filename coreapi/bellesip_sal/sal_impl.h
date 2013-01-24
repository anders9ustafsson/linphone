/*
linphone
Copyright (C) 2012  Belledonne Communications, Grenoble, France

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef SAL_IMPL_H_
#define SAL_IMPL_H_
#include "sal.h"
#include "belle-sip/belle-sip.h"
#include "belle-sip/belle-sdp.h"

struct Sal{
	SalCallbacks callbacks;
	MSList *pending_auths;/*MSList of SalOp */
	belle_sip_listener_callbacks_t listener_callbacks;
	belle_sip_stack_t* stack;
	belle_sip_provider_t *prov;
	belle_sip_header_user_agent_t* user_agent;
	void *up; /*user pointer*/
	int session_expires;
	bool_t one_matching_codec;
};

typedef enum SalOpSate {
	SalOpStateEarly=0
	,SalOpStateActive
	,SalOpStateTerminating /*this state is used to wait until a proceeding state, so we can send the cancel*/
	,SalOpStateTerminated
}SalOpSate_t;

typedef enum SalOpDir {
	SalOpDirIncoming=0
	,SalOpDirOutgoing
}SalOpDir_t;

struct SalOp{
	SalOpBase base;
	belle_sip_listener_callbacks_t callbacks;
	belle_sip_request_t* request;
	belle_sip_response_t* response;
	belle_sip_server_transaction_t* pending_server_trans;
	belle_sip_client_transaction_t* pending_inv_client_trans;
	SalAuthInfo* auth_info;
	belle_sip_refresher_t*  registration_refresher;
	bool_t sdp_offering;
	belle_sip_dialog_t* dialog;
	belle_sip_header_address_t *replaces;
	belle_sip_header_address_t *referred_by;
	bool_t auto_answer_asked;
	SalMediaDescription *result;
	belle_sdp_session_description_t *sdp_answer;
	bool_t supports_session_timers;
	SalOpSate_t state;
	SalOpDir_t dir;
	belle_sip_refresher_t* refresher;
};

belle_sdp_session_description_t * media_description_to_sdp(const SalMediaDescription *sal);
int sdp_to_media_description(belle_sdp_session_description_t  *sdp, SalMediaDescription *desc);
belle_sip_request_t* sal_op_build_request(SalOp *op,const char* method);


void sal_op_call_fill_cbs(SalOp*op);
void set_or_update_dialog(SalOp* op, belle_sip_dialog_t* dialog);

void sal_op_set_remote_ua(SalOp*op,belle_sip_message_t* message);
int sal_op_send_request(SalOp* op, belle_sip_request_t* request);
void sal_op_resend_request(SalOp* op, belle_sip_request_t* request);
void sal_process_authentication(SalOp *op, belle_sip_response_t *response);

bool_t sal_compute_sal_errors(belle_sip_response_t* response,SalError* sal_err,SalReason* sal_reason,char* reason, size_t reason_size);
void sal_compute_sal_errors_from_code(int code ,SalError* sal_err,SalReason* sal_reason) ;
/*presence*/
void sal_op_presence_fill_cbs(SalOp*op);

#endif /* SAL_IMPL_H_ */
