/**
 * <summary>
 *	Get the number of connected players or NPCs.
 * </summary>
 *
 * <param name="countPlayers">
 *	Defines whether normal players should be counted.
 *	<item name="true">Count normal players</item>
 *	<item name="false">Do not count normal players</item>
 * </param>
 *
 * <param name="countNPCs">
 *	Defines whether NPCs should be counted.
 *	<item name="true">Count NPCs</item>
 *	<item name="false">Do not count NPCs</item>
 * </param>
 *
 * <returns>
 *	The number of connected players and/or NPCs.
 * </returns>
 */

GetConnectedPlayers(countPlayers, countNPCs)
{
	new players;
	PlayerLoop(playerID)
	{
		new iscountable;
		if (countPlayers)
		{
			iscountable = !IsPlayerNPC(playerID);
		}
		if (countNPCs)
		{
			iscountable = IsPlayerNPC(playerID);
		}
		if (iscountable)
		{
			players++;
		}
	}
	return players;
}