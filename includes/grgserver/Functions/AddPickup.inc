/*
	Description:
		Spawn a pickup and add a 3D text label
		Adds the pickup to the database if saveToDB is true
	Parameters:
		pickupID: ID from pickups table in database (Only required if saveToDB is false)
		type: Type of the pickup as string (See GetPickupInfoByType for details)
		posX/Y/Z: Position as float
		saveToDB: Adds the pickup to the database if true (Used to create new pickup)
	Return:
		-1: Invalid pickup type
		-2: Spawned without adding to pickups table
		ID: The ID of the new pickup in the pickups table
*/
AddPickup(pickupID, type[], Float:posX, Float:posY, Float:posZ, saveToDB)
{
	new modelID;
	new pickup;
	FormatNew:functionName[MAX_FUNCTION_NAME]("PUMID_%s", type);// PUMID = PickUpModelID
	modelID = CallLocalFunction(functionName, "d", pickupID);
	if (modelID)
	{
		pickup = CreatePickup(modelID, 23, posX, posY, posZ);
		Create3DTextLabel("~k~~CONVERSATION_YES~", COLOR_TEXTLABEL, posX, posY, posZ, TEXTLABEL_DRAWDISTANCE, 0, true);
		pickups[pickup][PICKUP_POSX] = posX;
		pickups[pickup][PICKUP_POSY] = posY;
		pickups[pickup][PICKUP_POSZ] = posZ;
		format(pickups[pickup][PICKUP_TYPE], STRINGLENGTH_PICKUPTYPE, type);
		if (saveToDB)
		{
			MySQLQuery("INSERT INTO `pickups` (`PosX`, `PosY`, `PosZ`, `Type`) VALUES('%f', '%f', '%f', '%s')", posX, posY, posZ, type);
			pickups[pickup][PICKUP_ID] = mysql_insert_id();
			return pickups[pickup][PICKUP_ID];
		}
		else
		{
			pickups[pickup][PICKUP_ID] = pickupID;
			return -2;
		}
	}
	else
	{
		return -1;
	}
}