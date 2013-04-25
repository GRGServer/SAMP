CMD:relogin(playerID, params[], StringID:507("Relogin with your current name or a new name"))
{
	if (!StrNotNull(params))
	{
		CmdUsageMsg(playerID, "relogin", "Playername");
		return COMMAND_USAGE;
	}
	new checkPlayerID = GetPlayerID(params);
	if (checkPlayerID != INVALID_PLAYER_ID && checkPlayerID != playerID)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:508("Another player with this name is already connected!"));
		return COMMAND_ERROR;
	}
	OnPlayerDisconnect(playerID, 3);
	if (SetPlayerName(playerID, params) == -1)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:509("Your name could not be changed! Your old name will be used."));
	}
	ForceClassSelection(playerID);
	TogglePlayerSpectating(playerID, true);
	TogglePlayerSpectating(playerID, false);
	OnPlayerConnect(playerID);
	return COMMAND_OK;
}