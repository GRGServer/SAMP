GetClosestPickup(playerID, type[], &Float:distance = 0.0)
{
	new pickupID;
	distance = 6000.0;
	Count(checkPickupID, MAX_PICKUPS)
	{
		if (!strcmp(pickups[checkPickupID][PICKUP_TYPE], type, true))
		{
			new Float:checkDistance = GetPlayerDistanceFromPoint(playerID, pickups[checkPickupID][PICKUP_POSX], pickups[checkPickupID][PICKUP_POSY], pickups[checkPickupID][PICKUP_POSZ]);
			if (checkDistance < distance)
			{
				distance = checkDistance;
				pickupID = checkPickupID;
			}
		}
	}
	return pickupID;
}