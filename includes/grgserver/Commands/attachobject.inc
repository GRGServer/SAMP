PCMD:attachobject[ADMIN](playerID, params[], 393)
{
	new slot;
	new modelID;
	new Float:offsetX;
	new Float:offsetY;
	new Float:offsetZ;
	new Float:rotationX;
	new Float:rotationY;
	new Float:rotationZ;
	if (sscanf(params, "ddffffff", slot, modelID, offsetX, offsetY, offsetZ, rotationX, rotationY, rotationZ))
	{
		CmdUsageMsg(playerID, "attachobject", "slot[0-9]", "modelID", "offsetX", "offsetY", "offsetZ", "rotationX", "rotationY", "rotationZ");
		return COMMAND_USAGE;
	}
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (!modelID)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 390);
		return COMMAND_ERROR;
	}
	if (slot < 0 || slot > VEHICLE_MAXATTACHEDOBJECTS - 1)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 389);
		return COMMAND_ERROR;
	}
	if (attachedObjects[playerID][slot])
	{
		DestroyDynamicObject(attachedObjects[playerID][slot]);
	}
	new objectID = CreateDynamicObject(modelID, 0, 0, 0, 0, 0, 0);
	AttachDynamicObjectToVehicle(objectID, vehicleID, offsetX, offsetY, offsetZ, rotationX, rotationY, rotationZ);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID, -1000);
	attachedObjects[playerID][slot] = objectID;
	SendClientMessageEx(playerID, COLOR_INFO, 392);
	return COMMAND_OK;
}