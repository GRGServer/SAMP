ResetPlayerVariables(playerID)
{
	Count(playerVariable, sizeof(playerVariables[]))
	{
		playerVariables[playerID][enum_playerVariable:playerVariable] = 0;
	}
	SetPVar:playerID[RECORDNPCFORPLAYER](INVALID_PLAYER_ID);
	SetPVar:playerID[SHOWINTERIOR_OLDINTERIOR](-1);
}