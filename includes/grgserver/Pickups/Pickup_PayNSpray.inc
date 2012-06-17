PickupEvent:PAYNSPRAY(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_KEYPRESS)
	{
		if (!IsPlayerInAnyVehicle(playerID))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 146);
			return true;
		}
		if (GetPlayerVehicleSeat(playerID) > 0)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 52);
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