PickupEvent:PAYNSPRAY(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_KEYPRESS)
	{
		if (!IsPlayerInAnyVehicle(playerID))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:146("You are not in a vehicle!"));
			return true;
		}
		if (GetPlayerVehicleSeat(playerID) > 0)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:52("You are not the driver of this vehicle!"));
			return true;
		}
		SendClientMessage(playerID, COLOR_SYSTEM, "To be continued...");
		return true;
	}
	return false;
}

PickupModelID:PAYNSPRAY(pickupID)
{
	return 365;
}