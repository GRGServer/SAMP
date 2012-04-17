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
		case CHECKPOINT_TUTORIAL_BANK:
		{
			posX = -2757.0632;
			posY = 375.7754;
			posZ = 4.3342;
			size = 1.5;
		}
		case CHECKPOINT_TUTORIAL_SPEAKER1:
		{
			posX = 1715.0739;
			posY = 1616.4000;
			posZ = 10.0717;
			size = 1.0;
		}
	}
	SetPlayerCheckpoint(playerID, posX, posY, posZ, size);
	PVar:playerID[CURRENTCHECKPOINT] = checkpointID;
}