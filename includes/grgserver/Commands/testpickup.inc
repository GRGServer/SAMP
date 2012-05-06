PCMD:testpickup[MAPPER](playerID, params[], 0)
{
	new modelID;
	if (sscanf(params, "d", modelID))
	{
		CmdUsageMsg(playerID, "testpickup", "ModelID");
		return COMMAND_USAGE;
	}
	if (modelID)
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		GetPlayerPos(playerID, posX, posY, posZ);
		if (testPickup[playerID])
		{
			DestroyPickup(testPickup[playerID]);
		}
		testPickup[playerID] = CreatePickup(modelID, 23, posX, posY, posZ, -1);
		SendClientMessage(playerID, COLOR_INFO, "Pickup created");
		return COMMAND_OK;
	}
	return COMMAND_ERROR;
}