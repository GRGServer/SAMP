SetPlayerCheckpointEx(playerID, checkpointID)
{
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:size;
	switch (checkpointID)
	{
		case CHECKPOINT_INPLANE_EXIT:
		{
			posX = 2.6446;
			posY = 33.1288;
			posZ = 1199.5938;
			size = 0.8;
		}
		case CHECKPOINT_TUTORIAL_SPEAKER1:
		{
			posX = 1716.9218;
			posY = 1615.4843;
			posZ = 10.1052;
			size = 0.8;
		}
	}
	SetPlayerCheckpoint(playerID, posX, posY, posZ, size);
	PVar:playerID[CURRENTCHECKPOINT] = checkpointID;
}