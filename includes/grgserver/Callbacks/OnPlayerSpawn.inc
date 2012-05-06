public OnPlayerSpawn(playerid)
{
	if (IsPlayerNPC(playerid))
	{
		new npcName[MAX_PLAYER_NAME];
		GetPlayerName(playerid, npcName, sizeof(npcName));
		strdel(npcName, 0, 4);
		MySQLQuery("SELECT * FROM `npcs` WHERE `Name` = '%s'", MySQLEscapeString(npcName));
		mysql_store_result();
		SetPlayerSkin(playerid, strval(GetMySQLField("Skin")));
		new vehicleID = GetVehicleBySaveID(strval(GetMySQLField("VehicleID")));
		if (vehicleID == INVALID_VEHICLE_ID)
		{
			if (floatstr(GetMySQLField("SpawnPosX")) || floatstr(GetMySQLField("SpawnPosY")) || floatstr(GetMySQLField("SpawnPosZ")))
			{
				FormatNew:command[100]("teleport %s %s %s %s 0", GetMySQLField("SpawnPosX"), GetMySQLField("SpawnPosY"), GetMySQLField("SpawnPosZ"), GetMySQLField("SpawnAngle"));
				SendNPCCommand(playerid, command);
			}
			else
			{
				printf("WARNING: %s spawned without vehicle and no spawn position information!", npcName);
			}
		}
		else
		{
			PutPlayerInVehicle(playerid, vehicleID, 0);
		}
		mysql_free_result();
		return true;
	}
	if (PVar:playerid[SPAWNAFTERLOGIN])
	{
		PVar:playerid[SPAWNAFTERLOGIN] = false;
		SetPlayerPosEx(playerid, floatstr(GetUserDBValue(playerid, "PosX")), floatstr(GetUserDBValue(playerid, "PosY")), floatstr(GetUserDBValue(playerid, "PosZ")));
		SetPlayerFacingAngle(playerid, floatstr(GetUserDBValue(playerid, "Angle")));
		SetPlayerInterior(playerid, strval(GetUserDBValue(playerid, "Interior")));
		ShowNews(playerid, PVar:playerid[LASTNEWSID]);
		PlayerPlaySound(playerid, 1063, 0.0, 0.0, 0.0);// Stop music
		if (PVar:playerid[SHOWCLOCK])
		{
			TextDrawShowForPlayer(playerid, textDrawClock);
		}
	}
	else
	{
		InterpolateCameraPos(playerid, 2326.3, 1284.69, 160.559, 2037.28, 1344.28, 10.8203, 2500, CAMERA_CUT);
		InterpolateCameraLookAt(playerid, 2032.08, 1344.08, 10.8203, 2032.08, 1344.08, 10.8203, 2500, CAMERA_CUT);
		SetTimerEx("Timer_ScreenFader", 3500, false, "ddddddd", playerid, 0, 0, 0, 5, 0, FADE_RESPAWN_BLACK);
		PVar:playerid[CURRENTPROPERTYID] = 0;
	}
	SetPlayerSkin(playerid, PVar:playerid[SKIN]);
	return true;
}