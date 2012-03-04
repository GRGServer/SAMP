public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
	switch (success)
	{
		case COMMAND_ERROR:
			SendClientMessage(playerid, COLOR_ERROR, "Fehler bei der Befehlsausführung!");
		case COMMAND_USAGE:
			return true;// Command usage message displayed -> Nothing to do yet
		case COMMAND_OK:
			return true;// Command executed successfully -> Do nothing
		case COMMAND_TELEPORTED:
			SendClientMessage(playerid, COLOR_INFO, "Du wurdest teleportiert!");
		case COMMAND_NPC_ONLY:
			SendClientMessage(playerid, COLOR_ERROR, "Diese Befehl ist nur für NPCs verfügbar!");
		case COMMAND_NOT_IN_VEHICLE:
			SendClientMessage(playerid, COLOR_ERROR, "Du bist nicht in einem Fahrzeug!");
		case COMMAND_PLAYER_NOT_FOUND:
			SendClientMessage(playerid, COLOR_ERROR, "Spieler nicht gefunden!");
		case COMMAND_PERMISSION_DENIED:
		{
			SendClientMessage(playerid, COLOR_ERROR, "Du hast nicht die nötigen Rechte um diesen Befehl zu verwenden!");
			printf("%s tried to execute %s but has not the required permission!", GetPlayerNameEx(playerid), cmdtext);
		}
		case COMMAND_NOT_FOUND:
			return false;
		default:
			printf("Unknown command return code from %s", cmdtext);
	}
	return true;
}