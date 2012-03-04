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
	SetPVar:playerID[RECORDNPCFORPLAYER](INVALID_PLAYER_ID);
	SetPVar:playerID[SHOWINTERIOR_OLDINTERIOR](-1);
}