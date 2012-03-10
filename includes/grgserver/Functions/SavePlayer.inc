SavePlayer(playerID)
{
	if (IsLoggedIn(playerID))
	{
		SetUserDBValue(playerID, "Money", Float2Str(PVar:playerID[MONEY]));
		SetUserDBValue(playerID, "Skin", val2str(PVar:playerID[SKIN]));
		SetUserDBValue(playerID, "CurrentBuildingID", val2str(PVar:playerID[CURRENTBUILDINGID]));
		SetUserDBValue(playerID, "JobID", val2str(PVar:playerID[JOBID]));
		SetUserDBValue(playerID, "OnlineTime", val2str(PVar:playerID[ONLINETIME] + (gettime() - PVar:playerID[ONLINESINCE])));
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetPlayerPos(playerID, posX, posY, posZ);
		GetPlayerFacingAngle(playerID, angle);
		if (posX != 0 && posY != 0 && posZ != 0)
		{
			MySQLQuery("UPDATE `users` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f', `Interior` = '%d' WHERE `UserID` = '%d'", posX, posY, posZ, angle, GetPlayerInterior(playerID), PVar:playerID[USERID]);
		}
	}
}