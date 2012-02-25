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
	new string[256];
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