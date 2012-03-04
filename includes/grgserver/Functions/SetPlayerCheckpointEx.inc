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
			size = 0.5;
		}
		case CHECKPOINT_WALKTOSEAT:
		{
			posX = 0.6138;
			posY = 25.7723;
			posZ = 1199.5938;
			size = 0.5;
		}
		case CHECKPOINT_SPEAKER:
		{
			posX = 1717.1071;
			posY = 1615.0365;
			posZ = 10.1408;
			size = 0.8;
		}
	}
	SetPlayerCheckpoint(playerID, posX, posY, posZ, size);
	SetPVar:playerID[CURRENTCHECKPOINT](checkpointID);
}