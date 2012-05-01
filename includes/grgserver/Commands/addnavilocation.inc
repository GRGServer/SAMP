PCMD:addnavilocation[NAVI](playerID, params[], 380)
{
	ShowDialog(playerID, DIALOG_ADDNAVILOCATION_TYPE);
	return COMMAND_OK;
}