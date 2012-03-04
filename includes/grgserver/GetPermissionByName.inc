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