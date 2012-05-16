ResetPlayerVariables(playerID)
{
	Count(permission, sizeof(permissions[]))
	{
		permissions[playerID][enum_permission:permission] = false;
	}
	Count(playerVariable, sizeof(playerVariables[]))
	{
		playerVariables[playerID][enum_playerVariable:playerVariable] = 0;
	}
	PVar:playerID[GPS_ID] = -1;
	PVar:playerID[RECORDNPCFORPLAYER] = INVALID_PLAYER_ID;
	PVar:playerID[SHOWINTERIOR_OLDINTERIOR] = -1;
}