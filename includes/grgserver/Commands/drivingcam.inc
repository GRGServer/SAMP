CMD:drivingcam(playerID, params[], 0)
{
	new Float: offsetX; 
	new Float: offsetY;
	new Float: offsetZ;
	sscanf(params, "fff", offsetX, offsetY, offsetZ);
	new object = CreateObject(playerID, 19300, offsetX, offsetY, offsetZ, 0.0, 0.0, 0.0);
	AttachObjectToPlayer(object, playerID, offsetX, offsetY, offsetZ, 0.0, 0.0, 0.0);
	AttachCameraToObject(playerID, object);
	return COMMAND_OK;
}