PickupEvent:INTERIOREXIT(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_PICKUP:
		{
			if (PVar:playerID[CURRENTPROPERTYID])
			{
				TogglePlayerControllable(playerID, false);
				StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_LEAVEPROPERTY, 0);
			}
			return true;
		}
	}
	return false;
}

PickupModelID:INTERIOREXIT(pickupID)
{
	return 19198;
}