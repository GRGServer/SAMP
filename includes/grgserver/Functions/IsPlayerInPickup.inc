IsPlayerInPickup(playerID)
{
	Count(pickupID, MAX_PICKUPS)
	{
		if (GetPlayerDistanceFromPoint(playerID, pickups[pickupID][PICKUP_POSX], pickups[pickupID][PICKUP_POSY], pickups[pickupID][PICKUP_POSZ]) <= 1)
		{
			return pickupID;
		}
	}
	return 0;
}