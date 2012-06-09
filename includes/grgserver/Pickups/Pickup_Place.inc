PickupEvent:PLACE(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			SendClientMessage(playerID, COLOR_SYSTEM, "This is a pickup used for open places which can be bought");// TODO: Change code
			return true;
		}
	}
	return false;
}

PickupModelID:PLACE(pickupID)
{
	return 1280;
}