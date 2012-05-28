CMD:drivingcam(playerID, params[], 0)
{
	new Float:offsetX; 
	new Float:offsetY;
	new Float:offsetZ;
	new objectID = CreateObject(playerID, 19300, 2.0, 2.0, 2.0, 0.0, 0.0, 0.0);
	sscanf(params, "fff", offsetX, offsetY, offsetZ);
	if (IsPlayerInAnyVehicle(playerID))
	{
		AttachObjectToVehicle(objectID, playerID, offsetX, offsetY, offsetZ, 0.0, 0.0, 0.0);
	}
	else
	{
		AttachObjectToPlayer(objectID, playerID, offsetX, offsetY, offsetZ, 0.0, 0.0, 0.0);
	}
	AttachCameraToObject(playerID, objectID);
	return COMMAND_OK;
}