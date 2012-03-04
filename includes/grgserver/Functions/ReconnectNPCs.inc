ReconnectNPCs()
{
	print("* Kicking NPCs...");
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerNPC(playerID))
		{
			Kick(playerID);
		}
	}
	printf("* Connecting NPCs...");
	mysql_query("SELECT * FROM `npcs` WHERE `AutoConnect` = '1'");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		FormatNew:npcName[MAX_PLAYER_NAME]("NPC_%s", GetMySQLField("Name"));
		ConnectNPC(npcName, NPC_SCRIPTNAME);
	}
	mysql_free_result();
}