SetPlayerPosEx(playerID, Float:posX, Float:posY, Float:posZ, interior = -1)
{
	SetPlayerPos(playerID, posX, posY, posZ);
	if (interior == -1)
	{
		interior = GetPlayerInterior(playerID);
	}
	else
	{
		SetPlayerInterior(playerID, interior);
	}
	Streamer_UpdateEx(playerID, posX, posY, posZ, -1, interior);
}