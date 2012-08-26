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
		MySQLQuery("SELECT * FROM `npcs` WHERE `name` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
		mysql_store_result();
		SetPlayerSkin(playerid, strval(GetMySQLField("skin")));
		new vehicleID = GetVehicleBySaveID(strval(GetMySQLField("vehicleId")));
		if (vehicleID)
		{
			PVar:playerid[NPC_RECORDINGTYPE] = PLAYER_RECORDING_TYPE_DRIVER;
			VehicleProperty:vehicleID[ALLOWDESTROY] = false;
			VehicleProperty:vehicleID[ALLOWPOSSAVE] = false;
			PutPlayerInVehicle(playerid, vehicleID, 0);
			SetVehicleEngineState(vehicleID, true);
		}
		else
		{
			PVar:playerid[NPC_RECORDINGTYPE] = PLAYER_RECORDING_TYPE_ONFOOT;
		}
		new tryMultiRecForID;
		new startOnConnect = strval(GetMySQLField("startOnConnect"));
		PVar:playerid[NPC_AUTOREPEAT] = strval(GetMySQLField("autoRepeat"));
		if (floatstr(GetMySQLField("spawnPosX")) || floatstr(GetMySQLField("spawnPosY")) || floatstr(GetMySQLField("spawnPosZ")))
		{
			FormatNew:command[100]("teleport %s %s %s %s", GetMySQLField("spawnPosX"), GetMySQLField("spawnPosY"), GetMySQLField("spawnPosZ"), GetMySQLField("spawnAngle"));
			SendNPCCommand(playerid, command);
			tryMultiRecForID = 0;
		}
		if (strlen(GetMySQLField("recording")))
		{
			FormatNew:command[40]("setrec %s %d %d %d %d", GetMySQLField("recording"), PVar:playerid[NPC_RECORDINGTYPE], PVar:playerid[NPC_AUTOREPEAT], startOnConnect, strval(GetMySQLField("startDelay")));
			SendNPCCommand(playerid, command);
		}
		else
		{
			tryMultiRecForID = strval(GetMySQLField("id"));
		}
		mysql_free_result();
		if (tryMultiRecForID)
		{
			new slot;
			MySQLQuery("SELECT * FROM `npcmultirecs` WHERE `npcId` = '%d'", tryMultiRecForID);
			mysql_store_result();
			while (FetchMySQLRow())
			{
				PVar:playerid[NPC_RECORDINGS][slot] = strval(GetMySQLField("id"));
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
	if (PVar:playerid[SHOWCLOCK])
	{
		TextDrawShowForPlayer(playerid, textDrawClock);
	}
	if (PVar:playerid[SPAWNAFTERLOGIN] && !PVar:playerid[INTUTORIAL])
	{
		PVar:playerid[SPAWNAFTERLOGIN] = false;
		MySQLQuery("SELECT * FROM `users` WHERE `id` = '%d'", PVar:playerid[USERID]);
		mysql_store_result();
		SetPlayerPosEx(playerid, floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ")), strval(GetMySQLField("interior")));
		SetPlayerFacingAngle(playerid, floatstr(GetMySQLField("angle")));
		mysql_free_result();
		ShowNews(playerid, PVar:playerid[LASTNEWSID]);
		MySQLQuery("SELECT * FROM `friends` WHERE `userId2` = '%d' AND `accepted` = '0'", PVar:playerid[USERID]);
		mysql_store_result();
		new rows = mysql_num_rows();
		mysql_free_result();
		if (rows)
		{
			SendClientMessageEx(playerid, COLOR_INFO, 498, rows);
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
	if (PVar:playerid[INTUTORIAL])
	{
		TogglePlayerControllable(playerid, false);
		StartScreenFader(playerid, 0, 0, 0, 2, 500, FADE_START_INPLANE1, 0);
		return true;
	}
	return true;
}