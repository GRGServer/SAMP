/**
 * <summary>
 *	This callback is called when a player spawns.
 * </summary>
 *
 * <param name="playerid">
 *	The ID of the player which was spawned.
 * </param>
 *
 * <returns>
 *	Returning false will force the player to enter class selection at the next respawn.
 * </returns>
 *
 * <remarks>
 *	<title>The following task are done in this callback:</title>
 *	<item>If the player is a NPC: Set all required information like recording, teleporting place, etc.</item>
 *	<item>If the player spawns after login: Spawn the player at the save position and show the latest news</item>
 *	<item>If the player spawns after death: Spawn the player at the next hospital</item>
 *	<item>If nothing applies: Spawn the player at the default spawn</item>
 * </remarks>
 */

public OnPlayerSpawn(playerid)
{
	if (IsPlayerNPC(playerid))
	{
		MySQLQuery("SELECT * FROM `npcs` WHERE `Name` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
		mysql_store_result();
		SetPlayerSkin(playerid, strval(GetMySQLField("Skin")));
		new vehicleID = GetVehicleBySaveID(strval(GetMySQLField("VehicleID")));
		if (vehicleID)
		{
			PVar:playerid[NPC_RECORDINGTYPE] = PLAYER_RECORDING_TYPE_DRIVER;
			VehicleProperty:vehicleID[ALLOWDESTROY] = false;
			VehicleProperty:vehicleID[ALLOWSAVE] = false;
			PutPlayerInVehicle(playerid, vehicleID, 0);
			SetVehicleEngineState(vehicleID, true);
		}
		else
		{
			PVar:playerid[NPC_RECORDINGTYPE] = PLAYER_RECORDING_TYPE_ONFOOT;
		}
		new tryMultiRecForID;
		new startOnConnect = strval(GetMySQLField("StartOnConnect"));
		PVar:playerid[NPC_AUTOREPEAT] = strval(GetMySQLField("AutoRepeat"));
		if (floatstr(GetMySQLField("SpawnPosX")) || floatstr(GetMySQLField("SpawnPosY")) || floatstr(GetMySQLField("SpawnPosZ")))
		{
			FormatNew:command[100]("teleport %s %s %s %s", GetMySQLField("SpawnPosX"), GetMySQLField("SpawnPosY"), GetMySQLField("SpawnPosZ"), GetMySQLField("SpawnAngle"));
			SendNPCCommand(playerid, command);
			tryMultiRecForID = 0;
		}
		if (strlen(GetMySQLField("Recording")))
		{
			FormatNew:command[40]("setrec %s %d %d %d", GetMySQLField("Recording"), PVar:playerid[NPC_RECORDINGTYPE], PVar:playerid[NPC_AUTOREPEAT], startOnConnect);
			SendNPCCommand(playerid, command);
		}
		else
		{
			tryMultiRecForID = strval(GetMySQLField("ID"));
		}
		mysql_free_result();
		if (tryMultiRecForID)
		{
			new slot;
			MySQLQuery("SELECT * FROM `npcmultirecs` WHERE `NPCID` = '%d'", tryMultiRecForID);
			mysql_store_result();
			while (FetchMySQLRow())
			{
				PVar:playerid[NPC_RECORDINGS][slot] = strval(GetMySQLField("ID"));
				slot++;
			}
			mysql_free_result();
			if (slot)
			{
				if (startOnConnect)
				{
					PlayNextNPCRecording(playerid);
				}
			}
		}
		return true;
	}
	SetPlayerSkin(playerid, PVar:playerid[SKIN]);
	if (PVar:playerid[SPAWNAFTERLOGIN])
	{
		PVar:playerid[SPAWNAFTERLOGIN] = false;
		SetPlayerPosEx(playerid, floatstr(GetUserDBValue(playerid, "PosX")), floatstr(GetUserDBValue(playerid, "PosY")), floatstr(GetUserDBValue(playerid, "PosZ")), strval(GetUserDBValue(playerid, "Interior")));
		SetPlayerFacingAngle(playerid, floatstr(GetUserDBValue(playerid, "Angle")));
		ShowNews(playerid, PVar:playerid[LASTNEWSID]);
		if (PVar:playerid[SHOWCLOCK])
		{
			TextDrawShowForPlayer(playerid, textDrawClock);
		}
		return true;
	}
	if (PVar:playerid[SPAWNAFTERDEATH] != -1)
	{
		SetPlayerPosEx(playerid, pickups[PVar:playerid[SPAWNAFTERDEATH]][PICKUP_POSX], pickups[PVar:playerid[SPAWNAFTERDEATH]][PICKUP_POSY], pickups[PVar:playerid[SPAWNAFTERDEATH]][PICKUP_POSZ]);
		PVar:playerid[SPAWNAFTERDEATH] = -1;
		PVar:playerid[CURRENTPROPERTYID] = 0;
		return true;
	}
	TogglePlayerControllable(playerid, false);
	InterpolateCameraPos(playerid, 2326.3, 1284.69, 160.559, 2037.28, 1344.28, 10.8203, 2500, CAMERA_CUT);
	InterpolateCameraLookAt(playerid, 2032.08, 1344.08, 10.8203, 2032.08, 1344.08, 10.8203, 2500, CAMERA_CUT);
	SetTimerEx("Timer_ScreenFader", 3500, false, "ddddddd", playerid, 0, 0, 0, 5, 0, FADE_RESPAWN_BLACK);
	return true;
}