CMD:clear(playerID, params[], 510)
{
	for (new line = 0; line < 10; line++)
	{
		SendClientMessage(playerID, COLOR_SYSTEM, "");
	}
	return COMMAND_OK;
}