PCMD:jetpack[ADMIN](playerid, params[], "Bekomme ein Jetpack")
{
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	SendClientMessage(playerid, COLOR_INFO, "Viel Spaﬂ mit deinem neuen JetPack!");
	return COMMAND_OK;
}