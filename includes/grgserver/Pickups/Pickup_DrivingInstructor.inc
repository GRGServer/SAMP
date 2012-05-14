PickupEvent:DRIVINGINSTRUCTOR(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			ShowDialog:SCHOOLDRIVER(playerID);
			return true;
		}
	}
	return false;
}

PickupModelID:DRIVINGINSTRUCTOR(pickupID)
{
	return 1239;
}