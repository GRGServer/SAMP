ReloadPermissions()
{
	print("* Reloading permissions...");
	mysql_query("SELECT * FROM `permissions`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new userID = strval(GetMySQLField("UserID"));
		if (userID)
		{
			Count(playerID, MAX_PLAYERS)
			{
				if (PVar:playerID[USERID] == userID)
				{
					LoadPermission:ADMIN(playerID, "Admin");
					LoadPermission:MAPPER(playerID, "Mapper");
					LoadPermission:MODERATOR(playerID, "Moderator");
					LoadPermission:NPCADMIN(playerID, "NPCAdmin");
					LoadPermission:SERVERADMIN(playerID, "ServerAdmin");
					LoadPermission:TELEPORT(playerID, "Teleport");
				}
			}
		}
	}
	mysql_free_result();
}