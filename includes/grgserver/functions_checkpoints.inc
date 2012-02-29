SetPlayerCheckpointEx(playerID, checkpointID)
{
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:size;
	switch (checkpointID)
	{
		case CHECKPOINT_WALKTOPLANEEXIT:
		{
			posX = 1.7176;
			posY = 32.3707;
			posZ = 1199.5938;
			size = 10;
		}
		case CHECKPOINT_WALKTOSEAT:
		{
			posX = 0.6138;
			posY = 25.7723;
			posZ = 1199.5938;
			size = 10;
		}
	}
	SetPlayerCheckpoint(playerID, posX, posY, posZ, size);
	SetPVarInt(playerID, "CurrentCheckpoint", checkpointID);
}