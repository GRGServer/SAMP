PCMD:showinterior[TELEPORT](playerid, params[], StringID:119(""))
{
	if (PVar:playerid[CURRENTPROPERTYID])
	{
		SendClientMessageEx(playerid, COLOR_ERROR, StringID:56(""));
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