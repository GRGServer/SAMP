RCMD:reloadpermissions(params[], "Reload all permissions from database")
{
	Exec:ReloadPermissions();
	return true;
}