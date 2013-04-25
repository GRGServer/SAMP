CMD:clear(playerID, params[], StringID:510("Clear the chat window"))
{
	for (new line = 0; line < 10; line++)
	{
		SendClientMessage(playerID, COLOR_SYSTEM, "");
	}
	return COMMAND_OK;
}