/**
 * <summary>
 *	Spawn a player
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 */

Timer:SpawnPlayer(playerID)
{
	SpawnPlayer(playerID);
	if (IsPlayerNPC(playerID))
	{
		return true;
	}
	TogglePlayerSpectating(playerID, true);
	PVar:playerID[PLAYRANDOMCAMERACUTS] = true;
	PlayRandomCameraCuts(playerID);
	MySQLQuery("SELECT * FROM `users` WHERE `username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerID)));
	mysql_store_result();
	if (strval(GetMySQLField("id")))
	{
		strcat(PVar:playerID[LANGUAGE], GetMySQLField("language"), STRINGLENGTH_LANGUAGE);
		PVar:playerID[REGISTERED] = true;
		ShowDialog:PreviewInfo(playerID);
	}
	else
	{
		new countryCode[3];
		strcat(countryCode, GetPlayerCountryCode(playerID));
		if (strlen(countryCode) && (!strcmp(countryCode, "AT", true) || !strcmp(countryCode, "CH", true) || !strcmp(countryCode, "DE", true)))
		{
			PVar:playerID[LANGUAGE] = "de";
		}
		else
		{
			PVar:playerID[LANGUAGE] = "en";
		}
		PVar:playerID[REGISTERED] = false;
		PlaySound(playerID, musicSoundIDs[random(sizeof(musicSoundIDs))]);
		ShowDialog:Register_Language(playerID);
	}
	mysql_free_result();
	SendClientMessageEx(playerID, COLOR_SYSTEM, "138");
	SendClientMessageEx(playerID, COLOR_SYSTEM, "5", COMPILER_SVN_REVISION);
	PlayerLoop(currentPlayerID)
	{
		if (!IsPlayerNPC(currentPlayerID) && currentPlayerID != playerID)
		{
			SendClientMessageEx(currentPlayerID, COLOR_JOINLEAVE, "3", playerID);
		}
	}
	ReloadTextDraws(playerID);
	return true;
}