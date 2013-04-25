PCMD:showinterior[TELEPORT](playerid, params[], StringID:119("Teleport to an interior"))
{
	if (PVar:playerid[CURRENTPROPERTYID])
	{
		SendClientMessageEx(playerid, COLOR_ERROR, StringID:56("You are currently in a building! Please exit the building and try it again."));
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