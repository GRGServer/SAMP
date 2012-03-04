Timer:SpawnPlayer(playerID)
{
	SpawnPlayer(playerID);
	SetPlayerPos(playerID, floatstr(GetUserDBValue(playerID, "PosX")), floatstr(GetUserDBValue(playerID, "PosY")), floatstr(GetUserDBValue(playerID, "PosZ")));
}