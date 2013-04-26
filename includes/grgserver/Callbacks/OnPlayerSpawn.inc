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
	if (IsPlayerNPC(playerid))// The player is a NPC
	{
		new playerName[MAX_PLAYER_NAME];
		GetPlayerName(playerid, playerName, sizeof(playerName));
		Foreach(arrayIndex, npcs)
		{
			if (!IsStr(npcs[arrayIndex][NPC_NAME], playerName))
			{
				continue;// This is not the connected NPC -> Jump to the next one in the array
			}

			SetPlayerSkin(playerid, npcs[arrayIndex][NPC_SKIN]);

			new recordingType;
			if (npcs[arrayIndex][NPC_VEHICLEID])
			{
				recordingType = PLAYER_RECORDING_TYPE_DRIVER;
				PutPlayerInVehicle(playerid, npcs[arrayIndex][NPC_VEHICLEID], 0);
				SetVehicleEngineState(npcs[arrayIndex][NPC_VEHICLEID], true);
			}
			else
			{
				recordingType = PLAYER_RECORDING_TYPE_ONFOOT;
			}

			if (StrNotNull(npcs[arrayIndex][NPC_RECORDING]))// Check if a recording is defined
			{
				FormatNew:command[100]("setrec %s %d %d %d %d", npcs[arrayIndex][NPC_RECORDING], recordingType, npcs[arrayIndex][NPC_AUTOREPEAT], npcs[arrayIndex][NPC_AUTOSTART], npcs[arrayIndex][NPC_STARTDELAY]);
				SendNPCCommand(playerid, command);
			}

			if (npcs[arrayIndex][NPC_SPAWNPOS][0] || npcs[arrayIndex][NPC_SPAWNPOS][1] || npcs[arrayIndex][NPC_SPAWNPOS][2])// Check if a spawn position is defined
			{
				FormatNew:command[100]("teleport %f %f %f %f", npcs[arrayIndex][NPC_SPAWNPOS][0], npcs[arrayIndex][NPC_SPAWNPOS][1], npcs[arrayIndex][NPC_SPAWNPOS][2], npcs[arrayIndex][NPC_SPAWNANGLE]);
				SendNPCCommand(playerid, command);
			}

			break;
		}
		return true;
	}

	SetPlayerSkin(playerid, PVar:playerid[SKIN]);
	if (PVar:playerid[SHOWCLOCK])
	{
		TextDrawShowForPlayer(playerid, textDrawClock);
	}
	if (PVar:playerid[SPAWNAFTERLOGIN])// The player spawns after login
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
			SendClientMessageEx(playerid, COLOR_INFO, StringID:498("There are %d friendship requests. Use /friendrequests to see them."), rows);
		}
		StartScreenFader(playerid, 0, 0, 0, -5, 0, FADE_LOGIN, 1);
		return true;
	}
	if (PVar:playerid[INTUTORIAL])// The player is currently in the tutorial
	{
		if (PVar:playerid[SPAWNAFTERTUTORIALSTART])// We have already seen the FADE_TUTORIAL_START screen fader
		{
			PVar:playerid[SPAWNAFTERTUTORIALSTART] = false;
			TogglePlayerControllable(playerid, false);
			TeleportToInterior(playerid, 138);
			InterpolateCameraPos(playerid, 315.8, 825.206, 1981.83, 315.075, 1035.86, 1939.33, 5000, CAMERA_CUT);
			InterpolateCameraLookAt(playerid, 313.852, 976.442, 1959.13, 316.852, 1082.44, 1925.13, 5000, CAMERA_CUT);
			StartScreenFader(playerid, 0, 0, 0, -5, 0, FADE_START_INPLANE1, 1);
			SetTimerEx("Timer_ScreenFader", 5000, false, "dddddddd", playerid, 0, 0, 0, 5, 0, FADE_START_INPLANE2, 0);
		}
		return true;
	}
	if (PVar:playerid[SPAWNAFTERDEATH] != -1)// The player spawned after death
	{
		SetPlayerPosEx(playerid, pickups[PVar:playerid[SPAWNAFTERDEATH]][PICKUP_POSX], pickups[PVar:playerid[SPAWNAFTERDEATH]][PICKUP_POSY], pickups[PVar:playerid[SPAWNAFTERDEATH]][PICKUP_POSZ]);
		SetCameraBehindPlayer(playerid);
		PVar:playerid[SPAWNAFTERDEATH] = -1;
		PVar:playerid[CURRENTPROPERTYID] = 0;
		StartScreenFader(playerid, 100, 0, 0, -5, 0, FADE_DEATH, 1);
		return true;
	}
	return true;
}