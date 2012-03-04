PCMD:teleport[TELEPORT](playerid, params[], "An einen vordefinierten Ort teleportieren")
{
	ShowDialog(playerid, DIALOG_TELEPORTLOCATIONS);
	return COMMAND_OK;
}