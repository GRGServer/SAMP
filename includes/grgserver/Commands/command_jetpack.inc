PCMD:jetpack[ADMIN](playerid, params[], 88)
{
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	SendClientMessageEx(playerid, COLOR_INFO, 87);
	return COMMAND_OK;
}