Timer:SpawnPlayer(playerID)
{
	SpawnPlayer(playerID);
	SetPlayerPosEx(playerID, floatstr(GetUserDBValue(playerID, "PosX")), floatstr(GetUserDBValue(playerID, "PosY")), floatstr(GetUserDBValue(playerID, "PosZ")));
}