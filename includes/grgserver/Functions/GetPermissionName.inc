GetPermissionName(permission)
{
	new string[16];
	switch (permission)
	{
		case PERMISSION_ADMIN:
			string = "Admin";
		case PERMISSION_MAPPER:
			string = "Mapper";
		case PERMISSION_MODERATOR:
			string = "Moderator";
		case PERMISSION_NAVI:
			string = "Navi";
		case PERMISSION_NPCADMIN:
			string = "NPCAdmin";
		case PERMISSION_SERVERADMIN:
			string = "ServerAdmin";
		case PERMISSION_SPAWNVEHICLE:
			string = "SpawnVehicle";
		case PERMISSION_TELEPORT:
			string = "Teleport";
	}
	return string;
}