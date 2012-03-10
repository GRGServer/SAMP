PCMD:showinterior[TELEPORT](playerid, params[], "In einen Interior teleportieren")
{
	if (PVar:playerid[CURRENTBUILDINGID])
	{
		SendClientMessage(playerid, COLOR_ERROR, "Du bist aktuell in einem Gebäude! Bitte verlasse das Gebäude und versuche es erneut.");
		return COMMAND_ERROR;
	}
	else
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		GetPlayerPos(playerid, posX, posY, posZ);
		PVar:playerid[SHOWINTERIOR_OLDPOSX] = posX;
		PVar:playerid[SHOWINTERIOR_OLDPOSY] = posY;
		PVar:playerid[SHOWINTERIOR_OLDPOSZ] = posZ;
		PVar:playerid[SHOWINTERIOR_OLDINTERIOR] = GetPlayerInterior(playerid);
		ShowInteriorDialog(playerid, INTERIORDIALOG_SHOWINTERIOR);
		return COMMAND_OK;
	}
}