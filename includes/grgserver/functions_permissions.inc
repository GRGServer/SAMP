GetPermissionByName(permissionName[])
{
	if (!strcmp(permissionName, "Admin", true))
	{
		return PERMISSION_ADMIN;
	}
	if (!strcmp(permissionName, "Mapper", true))
	{
		return PERMISSION_MAPPER;
	}
	if (!strcmp(permissionName, "Moderator", true))
	{
		return PERMISSION_MODERATOR;
	}
	if (!strcmp(permissionName, "NPCAdmin", true))
	{
		return PERMISSION_NPCADMIN;
	}
	if (!strcmp(permissionName, "ServerAdmin", true))
	{
		return PERMISSION_SERVERADMIN;
	}
	if (!strcmp(permissionName, "Teleport", true))
	{
		return PERMISSION_TELEPORT;
	}
	return -1;
}

GetPermissionName(permission)
{
	new string[16];
	switch (permission)
	{
		case PERMISSION_ADMIN:
			Format:string("Admin");
		case PERMISSION_MAPPER:
			Format:string("Mapper");
		case PERMISSION_MODERATOR:
			Format:string("Moderator");
		case PERMISSION_NPCADMIN:
			Format:string("NPCAdmin");
		case PERMISSION_SERVERADMIN:
			Format:string("ServerAdmin");
		case PERMISSION_TELEPORT:
			Format:string("Teleport");
	}
	return string;
}

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
			foreach (playerID in MAX_PLAYERS)
			{
				if (GetUserID(playerID) == userID)
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