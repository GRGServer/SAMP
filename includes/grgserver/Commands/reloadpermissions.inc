PCMD:reloadpermissions[SERVERADMIN](playerID, params[], StringID:151("Reload all permissions from database"))
{
	ReloadPermissions(playerID);
	return COMMAND_OK;
}