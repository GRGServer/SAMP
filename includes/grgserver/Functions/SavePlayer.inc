SavePlayer(playerID)
{
	if (IsLoggedIn(playerID))
	{
		Format:sqlQuery("`BankMoney` = '%f', `CreditMoney` = '%f', `Money` = '%f', `JobID` = '%d', `LastNewsID` = '%d'", PVar:playerID[BANKMONEY], PVar:playerID[CREDITMONEY], PVar:playerID[MONEY], PVar:playerID[JOBID], PVar:playerID[LASTNEWSID]);
		UpdateUserDB(playerID, "%s, `CurrentBuildingID` = '%d', `OnlineTime` = '%d', `LastPayDay` = '%d', `Skin` = '%d'", sqlQuery, PVar:playerID[CURRENTBUILDINGID], GetOnlineTime(playerID), PVar:playerID[LASTPAYDAY], PVar:playerID[SKIN]);
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