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

	PVar:playerID[NEEDS_BLADDER] = 100;
	PVar:playerID[NEEDS_ENERGY] = 100;
	PVar:playerID[NEEDS_HUNGER] = 100;
	PVar:playerID[NEEDS_THIRST] = 100;

	PVar:playerID[RECORDNPCFORPLAYER] = INVALID_PLAYER_ID;
	PVar:playerID[SHOWINTERIOR_OLDINTERIOR] = -1;
	PVar:playerID[SPAWNAFTERDEATH] = -1;
	PVar:playerID[ZONE] = -1;
}