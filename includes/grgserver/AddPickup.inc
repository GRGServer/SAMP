AddPickup(pickupID, type[], Float:posX, Float:posY, Float:posZ, saveToDB)
{
	new pickupTypeID;
	new modelID;
	new pickup;
	if (GetPickupInfoByType(pickupID, type, pickupTypeID, modelID))
	{
		pickup = CreatePickup(modelID, 23, posX, posY, posZ);
		Create3DTextLabel("Drücke ~k~~CONVERSATION_YES~", COLOR_TEXTLABEL, posX, posY, posZ, TEXTLABEL_DRAWDISTANCE, 0, true);
		pickups[pickup][PICKUP_POSX] = posX;
		pickups[pickup][PICKUP_POSY] = posY;
		pickups[pickup][PICKUP_POSZ] = posZ;
		pickups[pickup][PICKUP_TYPE] = pickupTypeID;
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