SavePlayer(playerID)
{
	if (IsLoggedIn(playerID))
	{
		Format:sqlQuery("`bankMoney` = '%f', `money` = '%f', `jobId` = '%d', `lastNewsId` = '%d', `chatMode` = '%s', `chatModeUserId` = '%d', `godMode` = '%d'", PVar:playerID[BANKMONEY], PVar:playerID[MONEY], PVar:playerID[JOBID], PVar:playerID[LASTNEWSID], PVar:playerID[CHATMODE], PVar:playerID[CHATMODE_USERID], PVar:playerID[GODMODE]);
		Format:sqlQuery("%s, `currentPropertyId` = '%d', `onlineTime` = '%d', `lastPayDay` = '%d', `skin` = '%d', `showClock` = '%d', `deaths` = '%d'", sqlQuery, PVar:playerID[CURRENTPROPERTYID], GetOnlineTime(playerID), PVar:playerID[LASTPAYDAY], PVar:playerID[SKIN], PVar:playerID[SHOWCLOCK], PVar:playerID[DEATHS]);
		MySQLQuery("UPDATE `users` SET %s, `language` = '%d' WHERE `id` = '%d'", sqlQuery, PVar:playerID[LANGUAGE], PVar:playerID[USERID]);
		new Float:health;
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetPlayerHealth(playerID, health);
		GetPlayerPos(playerID, posX, posY, posZ);
		GetPlayerFacingAngle(playerID, angle);
		if (posX != 0 && posY != 0 && posZ != 0)
		{
			MySQLQuery("UPDATE `users` SET `health` = '%f', `posX` = '%f', `posY` = '%f', `posZ` = '%f', `angle` = '%f', `interior` = '%d' WHERE `id` = '%d'", health, posX, posY, posZ, angle, GetPlayerInterior(playerID), PVar:playerID[USERID]);
		}
	}
}