SavePlayer(playerID)
{
	if (IsLoggedIn(playerID))
	{
		new onlineTime = PVar:playerID[ONLINETIME] + (gettime() - PVar:playerID[ONLINESINCE]);
		Format:sqlQuery("`BankMoney` = '%f', `CreditMoney` = '%f', `Money` = '%f', `JobID` = '%d'", PVar:playerID[BANKMONEY], PVar:playerID[CREDITMONEY], PVar:playerID[MONEY], PVar:playerID[JOBID]);
		UpdateUserDB(playerID, "%s, `CurrentBuildingID` = '%d', `OnlineTime` = '%d', `Skin` = '%d'", sqlQuery, PVar:playerID[CURRENTBUILDINGID], onlineTime, PVar:playerID[SKIN]);
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