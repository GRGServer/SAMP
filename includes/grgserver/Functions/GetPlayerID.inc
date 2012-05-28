/**
 * <summary>
 *	The the ID of the player specified by the name.
 * </summary>
 *
 * <param name="playerName">
 *	The name of the player to search for.
 * </param>
 *
 * <returns>
 *	<item>The ID of the player</item>
 *	<item>INVALID_PLAYER_ID if the player was not found</item>
 * </returns>
 *
 * <remarks>
 *	This function checks for the whole name of the player (Not just a part).
 * </remarks>
 */

GetPlayerID(playerName[])
{
	PlayerLoop(playerID)
	{
		if (IsStr(GetPlayerNameEx(playerID), playerName))
		{
			return playerID;
		}
	}
	return INVALID_PLAYER_ID;
}