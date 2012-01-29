/*----------------------------------------------------------------------------*-
					=====================
					Y Server Fixes - Main
					=====================
Description:
	Provides native declarations for YSF functions.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI 2.0 SA:MP plugin.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2008
	the Initial Developer. All Rights Reserved.
	
	Contributor(s):
	
	Peter Beverloo
	Marcus Bauer
	
	Special Thanks to:
	
	SA:MP Team past, present and future
Version:
	0.1.3
Changelog:
	13/12/09:
		0.3 version.
	02/11/08:
		First version
Functions:
	Public:
		-
	Core:
		-
	Stock:
		-
	Static:
		-
	Inline:
		-
	API:
		-
Callbacks:
	-
Definitions:
	-
Enums:
	-
Macros:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	-
Operators:
	-
-*----------------------------------------------------------------------------*/

#if defined _YSF_included
	#endinput
#endif
#define _YSF_included

/*----------------------------------------------------------------------------*-
					=============
					YSF Libraries
					=============
-*----------------------------------------------------------------------------*/

// Generic functions
native SetModeRestartTime(Float:seconds);
native SetPlayerGravity(playerid, Float:gravity);
native AddServerRule(name[], value[]);
native SetServerRule(name[], value[]);

// File functions
native ffind(const pattern[], filename[], len, &idx);
native frename(const oldname[], const newname[]);

// Directory functions
native dfind(const pattern[], filename[], len, &idx);
native dcreate(const name[]);
native drename(const oldname[], const newname[]);
