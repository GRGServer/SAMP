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