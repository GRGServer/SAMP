public OnPlayerRequestSpawn(playerid)
{
	if (PVar:playerid[REGISTER_SELECTSKIN])
	{
		PVar:playerid[REGISTER_SELECTSKIN] = false;
		MySQLQuery("INSERT INTO `users` (`Username`, `Password`, `Gender`, `BirthDate`, `Location`, `RegisterTime`, `LoginTime`) VALUES ('%s', '%s', '%c', '%s', '%s', NOW(), NOW())", MySQLEscapeString(GetPlayerNameEx(playerid)), MD5(PVar:playerid[REGISTERPASSWORD]), PVar:playerid[GENDER], PVar:playerid[BIRTHDATE], MySQLEscapeString(PVar:playerid[REGISTERLOCATION]));
		PVar:playerid[USERID] = mysql_insert_id();
		PVar:playerid[ONLINESINCE] = gettime();
		SavePlayer(playerid);
		printf("Player registered: %s (UserID: %d)", GetPlayerNameEx(playerid), PVar:playerid[USERID]);
		SendClientMessage(playerid, COLOR_INFO, "Du wurdest erfolgreich registriert und bist nun eingeloggt.");
		TeleportTo(playerid, 1.7414, 31.6997, 1199.6012, 177.4850, 1, playerid);
		SetPlayerCheckpointEx(playerid, CHECKPOINT_WALKTOSEAT);
	}
	return true;
}