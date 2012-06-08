RestartGameMode(playerID, reason[])
{
	PlayerLoop(currentPlayerID)
	{
		SavePlayer(currentPlayerID);
		if (currentPlayerID != playerID)
		{
			SendClientMessageEx(currentPlayerID, COLOR_INFO, 43, playerID, reason);
		}
	}
	SendClientMessageEx(playerID, COLOR_INFO, 42, reason);
	printf("%s has restarted the gamemode: %s", GetPlayerNameEx(playerID), reason);
	SendRconCommand("gmx");
}