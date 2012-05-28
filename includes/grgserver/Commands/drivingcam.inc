CMD:drivingcam(playerID, params[], 0)
{
	new Float: offsetX; 
	new Float: offsetY;
	new Float: offsetZ;
	new pobject = CreateObject(playerID, 19300, 2.0, 2.0, 2.0, 0.0, 0.0, 0.0);
	sscanf(params, "fff", offsetX, offsetY, offsetZ);
	if(IsPlayerInAnyVehicle(playerID))
	{
		DestroyPlayerObject(playerID, pobject);
		new vobject = CreatePlayerObject(playerID, 19300, offsetX, offsetY, offsetZ, 0.0, 0.0, 0.0);
		AttachObjectToVehicle(vobject, playerID, offsetX, offsetY, offsetZ, 0.0, 0.0, 0.0);
		AttachCameraToObject(playerID, vobject);
	}
	else
	{		
		AttachObjectToPlayer(pobject, playerID, offsetX, offsetY, offsetZ, 0.0, 0.0, 0.0);
		AttachCameraToObject(playerID, pobject);
	}
	return COMMAND_OK;
}