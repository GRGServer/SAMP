PCMD:jetpack[ADMIN](playerid, params[], StringID:88("Get a JetPack"))
{
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	SendClientMessageEx(playerid, COLOR_INFO, StringID:87("Have fun with your new JetPack!"));
	return COMMAND_OK;
}