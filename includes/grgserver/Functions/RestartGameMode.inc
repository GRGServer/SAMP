/**
 * <summary>
 *	Restart the game mode.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player executing the restart.
 * </param>
 *
 * <param name="reason">
 *	The reason why the gamemode will be restarted.
 * </param>
 *
 * <remarks>
 *	All logged in players will be saved and receive a message containing the reason.
 * </remarks>
 */

RestartGameMode(playerID, reason[])
{
	PlayerLoop(currentPlayerID)
	{
		SavePlayer(currentPlayerID);
		if (currentPlayerID != playerID)
		{
			SendClientMessageEx(currentPlayerID, COLOR_INFO, "43", playerID, reason);
		}
	}
	SendClientMessageEx(playerID, COLOR_INFO, "42", reason);
	printf("%s has restarted the gamemode: %s", GetPlayerNameEx(playerID), reason);
	SendRconCommand("gmx");
}