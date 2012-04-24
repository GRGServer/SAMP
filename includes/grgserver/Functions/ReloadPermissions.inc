ReloadPermissions(playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Reloading permissions...");
	mysql_query("SELECT * FROM `permissions`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new userID = strval(GetMySQLField("UserID"));
		if (userID)
		{
			PlayerLoop(currentPlayerID)
			{
				if (PVar:currentPlayerID[USERID] == userID)
				{
					LoadPermission:ADMIN(currentPlayerID, "Admin");
					LoadPermission:MAPPER(currentPlayerID, "Mapper");
					LoadPermission:MODERATOR(currentPlayerID, "Moderator");
					LoadPermission:NPCADMIN(currentPlayerID, "NPCAdmin");
					LoadPermission:SERVERADMIN(currentPlayerID, "ServerAdmin");
					LoadPermission:TELEPORT(currentPlayerID, "Teleport");
				}
			}
		}
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  done");
}