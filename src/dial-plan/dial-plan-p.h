/*
 * dial-plan-p.h
 * Copyright (C) 2010-2017 Belledonne Communications SARL
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef _DIAL_PLAN_P_H_
#define _DIAL_PLAN_P_H_

#include "dial-plan.h"
#include "object/clonable-object-p.h"

// =============================================================================

LINPHONE_BEGIN_NAMESPACE

class DialPlanPrivate : public ClonableObjectPrivate {

public:
	std::string country;
	std::string isoCountryCode; /* ISO 3166-1 alpha-2 code, ex: FR for France*/
	std::string countryCallingCode; /*country calling code*/
	int nationalNumberLength = 0; /*maximum national number length*/
	std::string internationalCallPrefix; /*international call prefix, ex: 00 in europe*/

	L_DECLARE_PUBLIC(DialPlan);
};

LINPHONE_END_NAMESPACE

#endif // ifndef _DIAL_PLAN_P_H_
