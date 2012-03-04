RCMD:safegmx(params[], "Safely restart the gamemode")
{
	print("Restarting gamemode...");
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		SavePlayer(playerID);
	}
	SendClientMessageToAll(COLOR_INFO, "Der Gamemode wurde per RCON neugestartet");
	SendRconCommand("gmx");
	print("Done");
	return true;
}