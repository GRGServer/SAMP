public OnPlayerRequestSpawn(playerid)
{
	if (PVar:playerid[REGISTER_SELECTSKIN])
	{
		PVar:playerid[REGISTER_SELECTSKIN] = false;
		MySQLQuery("INSERT INTO `users` (`username`, `password`, `gender`, `birthDate`, `location`) VALUES('%s', '%s', '%c', '%s', '%s')", MySQLEscapeString(GetPlayerNameEx(playerid)), MD5(PVar:playerid[REGISTERPASSWORD]), PVar:playerid[GENDER], PVar:playerid[BIRTHDATE], MySQLEscapeString(PVar:playerid[REGISTERLOCATION]));
		PVar:playerid[USERID] = mysql_insert_id();
		PVar:playerid[ONLINESINCE] = gettime();
		PVar:playerid[SHOWCLOCK] = true;
		SetPVarStr:playerid[CHATMODE][STRINGLENGTH_CHATMODE]("INRANGE");
		MySQLQuery("UPDATE `users` SET `registerTime` = NOW(), `loginTime` = NOW(), `clientVersion` = '%s' WHERE `id` = '%d'", MySQLEscapeString(GetPlayerVersionEx(playerid)), PVar:playerid[USERID]);
		SavePlayer(playerid);
		ReloadTextDraws(playerid);
		printf("Player registered: %s (UserID: %d)", GetPlayerNameEx(playerid), PVar:playerid[USERID]);
		PlayerLoop(playerID)
		{
			if (playerID != playerid)
			{
				SendClientMessageEx(playerID, COLOR_JOINLEAVE, 7, playerid);
			}
		}
		PlayerPlaySound(playerid, 1063, 0.0, 0.0, 0.0);// Stop music
		SendClientMessageEx(playerid, COLOR_INFO, 139);
		if (PVar:playerid[SHOWCLOCK])
		{
			TextDrawShowForPlayer(playerid, textDrawClock);
		}
	}
	return true;
}