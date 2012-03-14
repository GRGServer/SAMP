RCMD:safegmx(params[], "Safely restart the gamemode")
{
	print("Restarting gamemode...");
	PlayerLoop(playerID)
	{
		SavePlayer(playerID);
	}
	SendClientMessageToAll(COLOR_INFO, "Der Gamemode wurde per RCON neugestartet");
	SendRconCommand("gmx");
	print("Done");
	return true;
}