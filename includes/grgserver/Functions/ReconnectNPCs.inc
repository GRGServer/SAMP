/**
 * <summary>
 *	Kick all currently connected NPCs and reconect NPCs which are tagged with AutoConnect in the npcs database table.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which executes a command which reconnects the NPCs (Optional).
 * </param>
 */

ReconnectNPCs(playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Kicking NPCs...");
	PlayerLoop(npcPlayerID)
	{
		if (IsPlayerNPC(npcPlayerID))
		{
			Kick(npcPlayerID);
		}
	}
	AdminPrint(playerID, COLOR_INFO, "* Connecting NPCs...");
	new count;
	mysql_query("SELECT * FROM `npcs` WHERE `AutoConnect` = '1'");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		ConnectNPC(GetMySQLField("Name"), NPC_SCRIPTNAME);
		count++;
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  %d NPCs connected", count);
}