SavePlayer(playerID)
{
	if (IsLoggedIn(playerID))
	{
		Format:sqlQuery("`BankMoney` = '%f', `Money` = '%f', `JobID` = '%d', `LastNewsID` = '%d', `ChatMode` = '%s', `GodMode` = '%d'", PVar:playerID[BANKMONEY], PVar:playerID[MONEY], PVar:playerID[JOBID], PVar:playerID[LASTNEWSID], PVar:playerID[CHATMODE], PVar:playerID[GODMODE]);
		Format:sqlQuery("%s, `CurrentPropertyID` = '%d', `OnlineTime` = '%d', `LastPayDay` = '%d', `Skin` = '%d', `ShowClock` = '%d', `Deaths` = '%d'", sqlQuery, PVar:playerID[CURRENTPROPERTYID], GetOnlineTime(playerID), PVar:playerID[LASTPAYDAY], PVar:playerID[SKIN], PVar:playerID[SHOWCLOCK], PVar:playerID[DEATHS]);
		UpdateUserDB(playerID, "%s, `Language` = '%d'", sqlQuery, PVar:playerID[LANGUAGE]);
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
			UpdateUserDB(playerID, "`Health` = '%f', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f', `Interior` = '%d'", health, posX, posY, posZ, angle, GetPlayerInterior(playerID));
		}
	}
}