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

RCMD:showmysqinfo(params[])
{
	new info[256];
	new stat[256];
	new serverVersion[256];
	new hostInfo[256];
	mysql_info(info);
	mysql_stat(stat);
	mysql_get_server_info(serverVersion);
	mysql_get_host_info(hostInfo);
	printf("Number of warnings: %d", mysql_warning_count());
	printf("Info: %s", info);
	printf("Status: %s", stat);
	printf("Server version: %s", serverVersion);
	printf("Host: %s", hostInfo);
	return true;
}