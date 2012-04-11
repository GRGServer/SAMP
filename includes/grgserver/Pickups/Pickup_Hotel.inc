PickupEvent:HOTEL(playerID, pickupID)
{
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new buildingID = strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
	new ownerUserID = strval(GetMySQLValue("buildings", "OwnerUserID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
	GetPlayerPos(playerID, posX, posY, posZ);
	PVar:playerID[HOTEL_PREVIOUSPOSITION_X] = posX;
	PVar:playerID[HOTEL_PREVIOUSPOSITION_Y] = posY;
	PVar:playerID[HOTEL_PREVIOUSPOSITION_Z] = posZ;
	SetPlayerPosEx(playerID, HOTEL_RECEPTION_POSX, HOTEL_RECEPTION_POSY, HOTEL_RECEPTION_POSZ);
	SetPlayerFacingAngle(playerID, HOTEL_RECEPTION_ANGLE);
	SetPlayerInterior(playerID, HOTEL_RECEPTION_INTERIOR);
	SetPlayerVirtualWorld(playerID, buildingID);
	if (ownerUserID)
	{
		if (ownerUserID == PVar:playerID[USERID])
		{
			PVar:playerID[DIALOGBUILDINGID] = buildingID;
			ShowDialog(playerID, DIALOG_HOTEL_MAIN_OWNER);
		}
		else
		{
			ShowDialog(playerID, DIALOG_HOTEL_MAIN_BOUGHT);
		}
	}
	else
	{
		ShowDialog(playerID, DIALOG_HOTEL_MAIN_AVAILABLE);
	}
}

PickupModelID:HOTEL(pickupID)
{
	return 1239;
}