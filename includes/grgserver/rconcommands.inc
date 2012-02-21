RCMD:reloadpermissions(params[])
{
	print("Reloading permissions...");
	mysql_query("SELECT * FROM `permissions`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new playerID = strval(GetMySQLField("UserID"));
		if (playerID)
		{
			LoadPermission:ADMIN(playerID, "Admin");
			LoadPermission:MAPPER(playerID, "Mapper");
			LoadPermission:MODERATOR(playerID, "Moderator");
			LoadPermission:NPCADMIN(playerID, "NPCAdmin");
			LoadPermission:SERVERADMIN(playerID, "ServerAdmin");
			LoadPermission:TELEPORT(playerID, "Teleport");
		}
	}
	mysql_free_result();
	print("Done");
	return true;
}

RCMD:reloadpickups(params[])
{
	print("Reloading pickups...");
	ReloadPickups();
	print("Done");
	return true;
}

RCMD:showmysqlinfo(params[])
{
	printf("Number of warnings: %d", mysql_warning_count());
	return true;
}