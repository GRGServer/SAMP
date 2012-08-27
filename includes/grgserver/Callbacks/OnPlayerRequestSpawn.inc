public OnPlayerRequestSpawn(playerid)
{
	if (PVar:playerid[REGISTER_SELECTSKIN])// Player comes from register skin selection -> Player is in register process
	{
		PVar:playerid[REGISTER_SELECTSKIN] = false;
		MySQLQuery("INSERT INTO `users` (`username`, `password`, `gender`, `birthDate`, `location`, `health`) VALUES('%s', '%s', '%c', '%s', '%s', '100')", MySQLEscapeString(GetPlayerNameEx(playerid)), MD5(PVar:playerid[REGISTERPASSWORD]), PVar:playerid[GENDER], PVar:playerid[BIRTHDATE], MySQLEscapeString(PVar:playerid[REGISTERLOCATION]));
		PVar:playerid[USERID] = mysql_insert_id();
		SetPVarStr:playerid[CHATMODE][STRINGLENGTH_CHATMODE]("INRANGE");
		PVar:playerid[INTUTORIAL] = true;
		PVar:playerid[SHOWCLOCK] = true;
		MySQLQuery("UPDATE `users` SET `registerTime` = NOW(), `loginTime` = NOW(), `clientVersion` = '%s' WHERE `id` = '%d'", MySQLEscapeString(GetPlayerVersionEx(playerid)), PVar:playerid[USERID]);
		SavePlayer(playerid);
		LoadPlayer(playerid);
		ReloadTextDraws(playerid);
		printf("Player registered: %s (UserID: %d)", GetPlayerNameEx(playerid), PVar:playerid[USERID]);
		PlayerLoop(playerID)
		{
			if (playerID != playerid)
			{
				SendClientMessageEx(playerID, COLOR_JOINLEAVE, 7, playerid);
			}
		}
		PVar:playerid[SPAWNAFTERTUTORIALSTART] = false;
		PlayerPlaySound(playerid, 1063, 0.0, 0.0, 0.0);
		TogglePlayerSpectating(playerid, true);
		StartScreenFader(playerid, 0, 0, 0, 10, 0, FADE_TUTORIAL_START, 0);
		SendClientMessageEx(playerid, COLOR_INFO, 139);
	}
	return true;
}