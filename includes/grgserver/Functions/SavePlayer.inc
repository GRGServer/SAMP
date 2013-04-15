SavePlayer(playerID)
{
	if (IsLoggedIn(playerID))
	{
		Format:sqlQuery("`money` = '%f', `jobId` = '%d', `lastNewsId` = '%d', `chatMode` = '%s', `chatModeUserId` = '%d', `godMode` = '%d'", PVar:playerID[MONEY], PVar:playerID[JOBID], PVar:playerID[LASTNEWSID], PVar:playerID[CHATMODE], PVar:playerID[CHATMODE_USERID], PVar:playerID[GODMODE]);
		Format:sqlQuery("%s, `currentPropertyId` = '%d', `onlineTime` = '%d', `lastPayDay` = '%d', `skin` = '%d', `showClock` = '%d', `inTutorial` = '%d', `deaths` = '%d'", sqlQuery, PVar:playerID[CURRENTPROPERTYID], GetOnlineTime(playerID), PVar:playerID[LASTPAYDAY], PVar:playerID[SKIN], PVar:playerID[SHOWCLOCK], PVar:playerID[INTUTORIAL], PVar:playerID[DEATHS]);
		Format:sqlQuery("%s, `bladder` = '%f', `energy` = '%f', `hunger` = '%f', `thirst` = '%f'", sqlQuery, PVar:playerID[NEEDS_BLADDER], PVar:playerID[NEEDS_ENERGY], PVar:playerID[NEEDS_HUNGER], PVar:playerID[NEEDS_THIRST]);
		MySQLQuery("UPDATE `users` SET %s, `language` = '%d', `wantedLevel` = '%d', `vehicleBought` = '%d' WHERE `id` = '%d'", sqlQuery, PVar:playerID[LANGUAGE], GetPlayerWantedLevel(playerID), PVar:playerID[VEHICLEBOUGHT], PVar:playerID[USERID]);

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