public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
	switch (success)
	{
		case COMMAND_ERROR:
			SendClientMessageEx(playerid, COLOR_ERROR, 143);
		case COMMAND_USAGE:
			return true;// Command usage message displayed -> Nothing to do yet
		case COMMAND_OK:
			return true;// Command executed successfully -> Do nothing
		case COMMAND_TELEPORTED:
			SendClientMessageEx(playerid, COLOR_INFO, 144);
		case COMMAND_NPC_ONLY:
			SendClientMessageEx(playerid, COLOR_ERROR, 145);
		case COMMAND_NOT_IN_VEHICLE:
			SendClientMessageEx(playerid, COLOR_ERROR, 146);
		case COMMAND_PLAYER_NOT_FOUND:
			SendClientMessageEx(playerid, COLOR_ERROR, 147);
		case COMMAND_PERMISSION_DENIED:
		{
			SendClientMessageEx(playerid, COLOR_ERROR, 148);
			printf("%s tried to execute %s but has not the required permission!", GetPlayerNameEx(playerid), cmdtext);
		}
		case COMMAND_NOT_FOUND:
			return false;
		default:
		{
			printf("Unknown command return code from %s", cmdtext);
			return false;
		}
	}
	return true;
}