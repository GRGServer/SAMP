PickupEvent:DRIVINGINSTRUCTOR(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			ShowDialog(playerID, DIALOG_SCHOOLDRIVER);
			return true;
		}
	}
	return false;
}

PickupModelID:DRIVINGINSTRUCTOR(pickupID)
{
	return 1239;
}