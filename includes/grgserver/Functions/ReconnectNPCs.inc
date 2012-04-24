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
		FormatNew:npcName[MAX_PLAYER_NAME]("NPC_%s", GetMySQLField("Name"));
		ConnectNPC(npcName, NPC_SCRIPTNAME);
		count++;
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  %d NPCs connected", count);
}