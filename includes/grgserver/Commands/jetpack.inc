PCMD:jetpack[ADMIN](playerid, params[], StringID:88(""))
{
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	SendClientMessageEx(playerid, COLOR_INFO, StringID:87(""));
	return COMMAND_OK;
}