/*
    SA-MP Streamer Plugin v2.6
    Copyright © 2012 Incognito

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <a_samp>

// Definitions

#define STREAMER_TYPE_OBJECT (0)
#define STREAMER_TYPE_PICKUP (1)
#define STREAMER_TYPE_CP (2)
#define STREAMER_TYPE_RACE_CP (3)
#define STREAMER_TYPE_MAP_ICON (4)
#define STREAMER_TYPE_3D_TEXT_LABEL (5)
#define STREAMER_TYPE_AREA (6)

#define STREAMER_AREA_TYPE_CIRCLE (0)
#define STREAMER_AREA_TYPE_RECTANGLE (1)
#define STREAMER_AREA_TYPE_SPHERE (2)
#define STREAMER_AREA_TYPE_CUBE (3)
#define STREAMER_AREA_TYPE_POLYGON (4)

#if !defined FLOAT_INFINITY
    #define FLOAT_INFINITY (Float:0x7F800000)
#endif

// Enumerator

enum
{
	E_STREAMER_ATTACHED_PLAYER,
	E_STREAMER_ATTACHED_VEHICLE,
	E_STREAMER_COLOR,
	E_STREAMER_DRAW_DISTANCE,
	E_STREAMER_EXTRA_ID,
	E_STREAMER_INTERIOR_ID,
	E_STREAMER_MAX_X,
	E_STREAMER_MAX_Y,
	E_STREAMER_MAX_Z,
	E_STREAMER_MIN_X,
	E_STREAMER_MIN_Y,
	E_STREAMER_MIN_Z,
	E_STREAMER_MODEL_ID,
	E_STREAMER_MOVE_R_X,
	E_STREAMER_MOVE_R_Y,
	E_STREAMER_MOVE_R_Z,
	E_STREAMER_MOVE_SPEED,
	E_STREAMER_MOVE_X,
	E_STREAMER_MOVE_Y,
	E_STREAMER_MOVE_Z,
	E_STREAMER_NEXT_X,
	E_STREAMER_NEXT_Y,
	E_STREAMER_NEXT_Z,
	E_STREAMER_PLAYER_ID,
	E_STREAMER_R_X,
	E_STREAMER_R_Y,
	E_STREAMER_R_Z,
	E_STREAMER_SIZE,
	E_STREAMER_STREAM_DISTANCE,
	E_STREAMER_STYLE,
	E_STREAMER_TEST_LOS,
	E_STREAMER_TYPE,
	E_STREAMER_WORLD_ID,
	E_STREAMER_X,
	E_STREAMER_Y,
	E_STREAMER_Z
}

// Setting Natives

native Streamer_TickRate(rate);
native Streamer_MaxItems(type, items);
native Streamer_VisibleItems(type, items);
native Streamer_CellDistance(Float:distance);
native Streamer_CellSize(Float:size);

// Update Natives

native Streamer_Update(playerid);
native Streamer_UpdateEx(playerid, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1);
native Streamer_ToggleIdleUpdate(playerid, toggle);

// Data Manipulation Natives

native Streamer_GetFloatData(type, {Text3D,_}:id, data, &Float:result);
native Streamer_SetFloatData(type, {Text3D,_}:id, data, Float:value);
native Streamer_GetIntData(type, {Text3D,_}:id, data);
native Streamer_SetIntData(type, {Text3D,_}:id, data, value);
native Streamer_GetArrayData(type, {Text3D,_}:id, data, dest[], maxlength = sizeof dest);
native Streamer_SetArrayData(type, {Text3D,_}:id, data, const src[], maxlength = sizeof src);
native Streamer_IsInArrayData(type, {Text3D,_}:id, data, value);
native Streamer_AppendArrayData(type, {Text3D,_}:id, data, value);
native Streamer_RemoveArrayData(type, {Text3D,_}:id, data, value);
native Streamer_GetUpperBound(type);

// Miscellaneous Natives

native Streamer_IsItemVisible(playerid, type, {Text3D,_}:id);
native Streamer_DestroyAllVisibleItems(playerid, type);
native Streamer_CountVisibleItems(playerid, type);

// Object Natives

native CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 300.0);
native DestroyDynamicObject(objectid);
native IsValidDynamicObject(objectid);
native SetDynamicObjectPos(objectid, Float:x, Float:y, Float:z);
native GetDynamicObjectPos(objectid, &Float:x, &Float:y, &Float:z);
native SetDynamicObjectRot(objectid, Float:rx, Float:ry, Float:rz);
native GetDynamicObjectRot(objectid, &Float:rx, &Float:ry, &Float:rz);
native MoveDynamicObject(objectid, Float:x, Float:y, Float:z, Float:speed, Float:rx = -1000.0, Float:ry = -1000.0, Float:rz = -1000.0);
native StopDynamicObject(objectid);
native IsDynamicObjectMoving(objectid);
native DestroyAllDynamicObjects();
native CountDynamicObjects();

// Pickup Natives

native CreateDynamicPickup(modelid, type, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 100.0);
native DestroyDynamicPickup(pickupid);
native IsValidDynamicPickup(pickupid);
native DestroyAllDynamicPickups();
native CountDynamicPickups();

// Checkpoint Natives

native CreateDynamicCP(Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 100.0);
native DestroyDynamicCP(checkpointid);
native IsValidDynamicCP(checkpointid);
native TogglePlayerDynamicCP(playerid, checkpointid, toggle);
native TogglePlayerAllDynamicCPs(playerid, toggle);
native IsPlayerInDynamicCP(playerid, checkpointid);
native DestroyAllDynamicCPs();
native CountDynamicCPs();

// Race Checkpoint Natives

native CreateDynamicRaceCP(type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 100.0);
native DestroyDynamicRaceCP(checkpointid);
native IsValidDynamicRaceCP(checkpointid);
native TogglePlayerDynamicRaceCP(playerid, checkpointid, toggle);
native TogglePlayerAllDynamicRaceCPs(playerid, toggle);
native IsPlayerInDynamicRaceCP(playerid, checkpointid);
native DestroyAllDynamicRaceCPs();
native CountDynamicRaceCPs();

// Map Icon Natives

native CreateDynamicMapIcon(Float:x, Float:y, Float:z, type, color, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 100.0);
native DestroyDynamicMapIcon(iconid);
native IsValidDynamicMapIcon(iconid);
native DestroyAllDynamicMapIcons();
native CountDynamicMapIcons();

// 3D Text Label Natives

native Text3D:CreateDynamic3DTextLabel(const text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 100.0);
native DestroyDynamic3DTextLabel(Text3D:id);
native IsValidDynamic3DTextLabel(Text3D:id);
native UpdateDynamic3DTextLabelText(Text3D:id, color, const text[]);
native DestroyAllDynamic3DTextLabels();
native CountDynamic3DTextLabels();

// Area Natives

native CreateDynamicCircle(Float:x, Float:y, Float:size, worldid = -1, interiorid = -1, playerid = -1);
native CreateDynamicRectangle(Float:minx, Float:miny, Float:maxx, Float:maxy, worldid = -1, interiorid = -1, playerid = -1);
native CreateDynamicSphere(Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1, playerid = -1);
native CreateDynamicCube(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worldid = -1, interiorid = -1, playerid = -1);
native CreateDynamicPolygon(Float:points[], Float:minz = -FLOAT_INFINITY, Float:maxz = FLOAT_INFINITY, maxpoints = sizeof points, worldid = -1, interiorid = -1, playerid = -1);
native DestroyDynamicArea(areaid);
native IsValidDynamicArea(areaid);
native TogglePlayerDynamicArea(playerid, areaid, toggle);
native TogglePlayerAllDynamicAreas(playerid, toggle);
native IsPlayerInDynamicArea(playerid, areaid);
native IsPlayerInAnyDynamicArea(playerid);
native AttachDynamicAreaToPlayer(areaid, playerid);
native AttachDynamicAreaToVehicle(areaid, vehicleid);
native DestroyAllDynamicAreas();
native CountDynamicAreas();

// Extended Natives

native CreateDynamicObjectEx(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:drawdistance = 0.0, Float:streamdistance = 200.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native CreateDynamicPickupEx(modelid, type, Float:x, Float:y, Float:z, Float:streamdistance = 100.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native CreateDynamicCPEx(Float:x, Float:y, Float:z, Float:size, Float:streamdistance = 100.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native CreateDynamicRaceCPEx(type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, Float:streamdistance = 100.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native CreateDynamicMapIconEx(Float:x, Float:y, Float:z, type, color, style = MAPICON_LOCAL, Float:streamdistance = 100.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native Text3D:CreateDynamic3DTextLabelEx(const text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, Float:streamdistance = 100.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native CreateDynamicCircleEx(Float:x, Float:y, Float:size, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native CreateDynamicRectangleEx(Float:minx, Float:miny, Float:maxx, Float:maxy, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native CreateDynamicSphereEx(Float:x, Float:y, Float:z, Float:size, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native CreateDynamicCubeEx(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
native CreateDynamicPolygonEx(Float:points[], Float:minz = -FLOAT_INFINITY, Float:maxz = FLOAT_INFINITY, maxpoints = sizeof points, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);

// Internal Natives

native Streamer_CallbackHook(callback, ...);

// Callbacks

forward OnDynamicObjectMoved(objectid);
forward OnPlayerPickUpDynamicPickup(playerid, pickupid);
forward OnPlayerEnterDynamicCP(playerid, checkpointid);
forward OnPlayerLeaveDynamicCP(playerid, checkpointid);
forward OnPlayerEnterDynamicRaceCP(playerid, checkpointid);
forward OnPlayerLeaveDynamicRaceCP(playerid, checkpointid);
forward OnPlayerEnterDynamicArea(playerid, areaid);
forward OnPlayerLeaveDynamicArea(playerid, areaid);

// Callback Hook Section

#define STREAMER_OPC (0)
#define STREAMER_OPDC (1)
#define STREAMER_OPPP (2)
#define STREAMER_OPEC (3)
#define STREAMER_OPLC (4)
#define STREAMER_OPERC (5)
#define STREAMER_OPLRC (6)

static bool:Streamer_g_OPC = false;
static bool:Streamer_g_OPDC = false;
static bool:Streamer_g_OPPP = false;
static bool:Streamer_g_OPEC = false;
static bool:Streamer_g_OPLC = false;
static bool:Streamer_g_OPERC = false;
static bool:Streamer_g_OPLRC = false;

public OnFilterScriptInit()
{
	Streamer_g_OPC = funcidx("Streamer_OnPlayerConnect") != -1;
	Streamer_g_OPDC = funcidx("Streamer_OnPlayerDisconnect") != -1;
	Streamer_g_OPPP = funcidx("Streamer_OnPlayerPickUpPickup") != -1;
	Streamer_g_OPEC = funcidx("Streamer_OnPlayerEnterCP") != -1;
	Streamer_g_OPLC = funcidx("Streamer_OnPlayerLeaveCP") != -1;
	Streamer_g_OPERC = funcidx("Streamer_OnPlayerEnterRaceCP") != -1;
	Streamer_g_OPLRC = funcidx("Streamer_OnPlayerLeaveRaceCP") != -1;
	if (funcidx("Streamer_OnFilterScriptInit") != -1)
	{
		return CallLocalFunction("Streamer_OnFilterScriptInit", "");
	}
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit Streamer_OnFilterScriptInit

forward Streamer_OnFilterScriptInit();

public OnGameModeInit()
{
	Streamer_g_OPC = funcidx("Streamer_OnPlayerConnect") != -1;
	Streamer_g_OPDC = funcidx("Streamer_OnPlayerDisconnect") != -1;
	Streamer_g_OPPP = funcidx("Streamer_OnPlayerPickUpPickup") != -1;
	Streamer_g_OPEC = funcidx("Streamer_OnPlayerEnterCP") != -1;
	Streamer_g_OPLC = funcidx("Streamer_OnPlayerLeaveCP") != -1;
	Streamer_g_OPERC = funcidx("Streamer_OnPlayerEnterRaceCP") != -1;
	Streamer_g_OPLRC = funcidx("Streamer_OnPlayerLeaveRaceCP") != -1;
	if (funcidx("Streamer_OnGameModeInit") != -1)
	{
		return CallLocalFunction("Streamer_OnGameModeInit", "");
	}
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit Streamer_OnGameModeInit

forward Streamer_OnGameModeInit();

public OnPlayerConnect(playerid)
{
	if (!IsPlayerNPC(playerid))
	{
		Streamer_CallbackHook(STREAMER_OPC, playerid);
	}
	if (Streamer_g_OPC)
	{
		return CallLocalFunction("Streamer_OnPlayerConnect", "d", playerid);
	}
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect Streamer_OnPlayerConnect

forward Streamer_OnPlayerConnect(playerid);

public OnPlayerDisconnect(playerid, reason)
{
	if (!IsPlayerNPC(playerid))
	{
		Streamer_CallbackHook(STREAMER_OPDC, playerid, reason);
	}
	if (Streamer_g_OPDC)
	{
		return CallLocalFunction("Streamer_OnPlayerDisconnect", "dd", playerid, reason);
	}
	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect Streamer_OnPlayerDisconnect

forward Streamer_OnPlayerDisconnect(playerid, reason);

public OnPlayerPickUpPickup(playerid, pickupid)
{
	if (!IsPlayerNPC(playerid))
	{
		Streamer_CallbackHook(STREAMER_OPPP, playerid, pickupid);
	}
	if (Streamer_g_OPPP)
	{
		return CallLocalFunction("Streamer_OnPlayerPickUpPickup", "dd", playerid, pickupid);
	}
	return 1;
}

#if defined _ALS_OnPlayerPickUpPickup
	#undef OnPlayerPickUpPickup
#else
	#define _ALS_OnPlayerPickUpPickup
#endif
#define OnPlayerPickUpPickup Streamer_OnPlayerPickUpPickup

forward Streamer_OnPlayerPickUpPickup(playerid, pickupid);

public OnPlayerEnterCheckpoint(playerid)
{
	if (!IsPlayerNPC(playerid))
	{
		Streamer_CallbackHook(STREAMER_OPEC, playerid);
	}
	if (Streamer_g_OPEC)
	{
		return CallLocalFunction("Streamer_OnPlayerEnterCP", "d", playerid);
	}
	return 1;
}

#if defined _ALS_OnPlayerEnterCheckpoint
	#undef OnPlayerEnterCheckpoint
#else
	#define _ALS_OnPlayerEnterCheckpoint
#endif
#define OnPlayerEnterCheckpoint Streamer_OnPlayerEnterCP

forward Streamer_OnPlayerEnterCP(playerid);

public OnPlayerLeaveCheckpoint(playerid)
{
	if (!IsPlayerNPC(playerid))
	{
		Streamer_CallbackHook(STREAMER_OPLC, playerid);
	}
	if (Streamer_g_OPLC)
	{
		return CallLocalFunction("Streamer_OnPlayerLeaveCP", "d", playerid);
	}
	return 1;
}

#if defined _ALS_OnPlayerLeaveCheckpoint
	#undef OnPlayerLeaveCheckpoint
#else
	#define _ALS_OnPlayerLeaveCheckpoint
#endif
#define OnPlayerLeaveCheckpoint Streamer_OnPlayerLeaveCP

forward Streamer_OnPlayerLeaveCP(playerid);

public OnPlayerEnterRaceCheckpoint(playerid)
{
	if (!IsPlayerNPC(playerid))
	{
		Streamer_CallbackHook(STREAMER_OPERC, playerid);
	}
	if (Streamer_g_OPERC)
	{
		return CallLocalFunction("Streamer_OnPlayerEnterRaceCP", "d", playerid);
	}
	return 1;
}

#if defined _ALS_OnPlayerEnterRaceCP
	#undef OnPlayerEnterRaceCheckpoint
#else
	#define _ALS_OnPlayerEnterRaceCP
#endif
#define OnPlayerEnterRaceCheckpoint Streamer_OnPlayerEnterRaceCP

forward Streamer_OnPlayerEnterRaceCP(playerid);

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	if (!IsPlayerNPC(playerid))
	{
		Streamer_CallbackHook(STREAMER_OPLRC, playerid);
	}
	if (Streamer_g_OPLRC)
	{
		return CallLocalFunction("Streamer_OnPlayerLeaveRaceCP", "d", playerid);
	}
	return 1;
}

#if defined _ALS_OnPlayerLeaveRaceCP
	#undef OnPlayerLeaveRaceCheckpoint
#else
	#define _ALS_OnPlayerLeaveRaceCP
#endif
#define OnPlayerLeaveRaceCheckpoint Streamer_OnPlayerLeaveRaceCP

forward Streamer_OnPlayerLeaveRaceCP(playerid);
