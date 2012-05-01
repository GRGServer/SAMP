PickupEvent:UPGRADEVEHICLE(playerID, pickupID)
{
	if (IsPlayerInAnyVehicle(playerID))
	{
		if (GetPlayerVehicleSeat(playerID) == 0)
		{
			ShowDialog(playerID, DIALOG_UPGRADEVEHICLE);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 52);
		}
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 146);
	}
}

PickupModelID:UPGRADEVEHICLE(pickupID)
{
	return 1318;
}