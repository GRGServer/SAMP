PickupEvent:UPGRADEVEHICLE(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			if (IsPlayerInAnyVehicle(playerID))
			{
				if (GetPlayerVehicleSeat(playerID) == 0)
				{
					ShowDialog:UpgradeVehicle(playerID);
				}
				else
				{
					SendClientMessageEx(playerID, COLOR_ERROR, StringID:52(""));
				}
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:146(""));
			}
			return true;
		}
	}
	return false;
}

PickupModelID:UPGRADEVEHICLE(pickupID)
{
	return 19130;
}