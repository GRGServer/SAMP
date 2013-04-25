PCMD:teleport[TELEPORT](playerID, params[], StringID:121("Teleport to a predefined location"))
{
	ShowDialog:TeleportLocations(playerID);
	return COMMAND_OK;
}