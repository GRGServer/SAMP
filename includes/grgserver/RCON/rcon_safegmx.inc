RCMD:safegmx(params[], 155)
{
	print("Restarting gamemode...");
	PlayerLoop(playerID)
	{
		SavePlayer(playerID);
		SendClientMessageEx(playerID, COLOR_INFO, 156);
	}
	SendRconCommand("gmx");
	print("Done");
	return true;
}