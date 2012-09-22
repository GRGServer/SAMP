LoadPlayerPermissions(playerID)
{
	LoadPermission:ADMIN(playerID, "admin");
	LoadPermission:MAPPER(playerID, "mapper");
	LoadPermission:MODERATOR(playerID, "moderator");
	LoadPermission:NAVI(playerID, "navi");
	LoadPermission:NPCADMIN(playerID, "npcAdmin");
	LoadPermission:SERVERADMIN(playerID, "serverAdmin");
	LoadPermission:SPAWNVEHICLE(playerID, "spawnVehicle");
	LoadPermission:TELEPORT(playerID, "teleport");
}