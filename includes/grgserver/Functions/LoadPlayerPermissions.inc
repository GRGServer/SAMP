LoadPlayerPermissions(playerID)
{
	LoadPermission:ADMIN(playerID, "Admin");
	LoadPermission:MAPPER(playerID, "Mapper");
	LoadPermission:MODERATOR(playerID, "Moderator");
	LoadPermission:NAVI(playerID, "Navi");
	LoadPermission:NPCADMIN(playerID, "NPCAdmin");
	LoadPermission:SERVERADMIN(playerID, "ServerAdmin");
	LoadPermission:TELEPORT(playerID, "Teleport");
}