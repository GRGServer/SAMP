PCMD:showinterior[TELEPORT](playerid, params[], "In einen Interior teleportieren")
{
	if (GetPVar:playerid[CURRENTBUILDINGID])
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
		SetPVar:playerid[SHOWINTERIOR_OLDPOSX](posX);
		SetPVar:playerid[SHOWINTERIOR_OLDPOSY](posY);
		SetPVar:playerid[SHOWINTERIOR_OLDPOSZ](posZ);
		SetPVar:playerid[SHOWINTERIOR_OLDINTERIOR](GetPlayerInterior(playerid));
		ShowInteriorDialog(playerid, INTERIORDIALOG_SHOWINTERIOR);
		return COMMAND_OK;
	}
}