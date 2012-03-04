IsLoggedIn(playerID)
{
	return (IsPlayerConnected(playerID) && !IsPlayerNPC(playerID) && GetPVar:playerID[USERID]);
}