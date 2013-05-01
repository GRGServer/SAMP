SavePlayer(playerID)
{
	if (IsLoggedIn(playerID))
	{
		// Bank
		Format:sqlQuery("`bankId` = '%d', `bankMoney` = '%f', `bankPin` = '%d', `bankPinAttempts` = '%d'", PVar:playerID[BANK_ID], PVar:playerID[BANK_MONEY], PVar:playerID[BANK_PIN], PVar:playerID[BANK_PIN_ATTEMPTS]);

		// Needs
		Format:sqlQuery("%s, `bladder` = '%f', `energy` = '%f', `hunger` = '%f', `thirst` = '%f'", sqlQuery, PVar:playerID[NEEDS_BLADDER], PVar:playerID[NEEDS_ENERGY], PVar:playerID[NEEDS_HUNGER], PVar:playerID[NEEDS_THIRST]);

		// Misc
		Format:sqlQuery("%s, `money` = '%f', `language` = '%s', `jobId` = '%d', `lastNewsId` = '%d', `chatMode` = '%s', `chatModeUserId` = '%d', `godMode` = '%d'", sqlQuery, PVar:playerID[MONEY], GetLanguageName(PVar:playerID[LANGUAGE]), PVar:playerID[JOBID], PVar:playerID[LASTNEWSID], PVar:playerID[CHATMODE], PVar:playerID[CHATMODE_USERID], PVar:playerID[GODMODE]);
		Format:sqlQuery("%s, `currentPropertyId` = '%d', `onlineTime` = '%d', `lastPayDay` = '%d', `skin` = '%d', `showClock` = '%d', `inTutorial` = '%d', `deaths` = '%d'", sqlQuery, PVar:playerID[CURRENTPROPERTYID], GetOnlineTime(playerID), PVar:playerID[LASTPAYDAY], PVar:playerID[SKIN], PVar:playerID[SHOWCLOCK], PVar:playerID[INTUTORIAL], PVar:playerID[DEATHS]);
		Format:sqlQuery("%s, `wantedLevel` = '%d', `speedLimitPoints` = '%d'", sqlQuery, GetPlayerWantedLevel(playerID), PVar:playerID[SPEEDLIMITPOINTS]);

		MySQLQuery("UPDATE `users` SET %s WHERE `id` = '%d'", sqlQuery, PVar:playerID[USERID]);

		new Float:health;
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetPlayerHealth(playerID, health);
		GetPlayerPos(playerID, posX, posY, posZ);
		GetPlayerFacingAngle(playerID, angle);
		GetPlayerWantedLevel(playerID);

		if (posX != 0 && posY != 0 && posZ != 0)
		{
			MySQLQuery("UPDATE `users` SET `health` = '%f', `posX` = '%f', `posY` = '%f', `posZ` = '%f', `angle` = '%f', `interior` = '%d' WHERE `id` = '%d'", health, posX, posY, posZ, angle, GetPlayerInterior(playerID), PVar:playerID[USERID]);
		}
	}
}