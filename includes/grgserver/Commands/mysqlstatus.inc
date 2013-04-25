PCMD:mysqlstatus[SERVERADMIN](playerID, params[], StringID:0("Undefined language string ID!"))
{
	new string[256];
	mysql_error(string);
	Format:string("Error: %s", string);
	SendClientMessage(playerID, COLOR_INFO, string);
	Format:string("Error No: %d", mysql_errno());
	SendClientMessage(playerID, COLOR_INFO, string);
	return COMMAND_OK;
}