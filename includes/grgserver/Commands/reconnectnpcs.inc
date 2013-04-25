PCMD:reconnectnpcs[SERVERADMIN](playerID, params[], StringID:150("Reconnect all NPCs"))
{
	ReconnectNPCs(playerID);
	return COMMAND_OK;
}