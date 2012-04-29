public OnPlayerRequestSpawn(playerid)
{
	if (PVar:playerid[REGISTER_SELECTSKIN])
	{
		PVar:playerid[REGISTER_SELECTSKIN] = false;
		MySQLQuery("INSERT INTO `users` (`Username`, `Password`, `Gender`, `BirthDate`, `Location`) VALUES('%s', '%s', '%c', '%s', '%s')", MySQLEscapeString(GetPlayerNameEx(playerid)), MD5(PVar:playerid[REGISTERPASSWORD]), PVar:playerid[GENDER], PVar:playerid[BIRTHDATE], MySQLEscapeString(PVar:playerid[REGISTERLOCATION]));
		PVar:playerid[USERID] = mysql_insert_id();
		PVar:playerid[ONLINESINCE] = gettime();
		UpdateUserDB(playerid, "`RegisterTime` = NOW(), `LoginTime` = NOW(), `ClientVersion` = '%s'", MySQLEscapeString(GetPlayerVersionEx(playerid)));
		SavePlayer(playerid);
		ReloadTextDraws(playerid);
		printf("Player registered: %s (UserID: %d)", GetPlayerNameEx(playerid), PVar:playerid[USERID]);
		PlayerPlaySound(playerid, 1063, 0.0, 0.0, 0.0);// Stop music
		SendClientMessageEx(playerid, COLOR_INFO, 139);
		TogglePlayerControllable(playerid, false);
		StartScreenFader(playerid, 0, 0, 0, 2, 500, FADE_START_INPLANE1_BLACK);
	}
	return true;
}