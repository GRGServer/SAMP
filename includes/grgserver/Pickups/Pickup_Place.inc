PickupEvent:PLACE(playerID, pickupID)
{
	SendClientMessage(playerID, COLOR_SYSTEM, "This is a pickup used for open places which can be bought");
}

PickupModelID:PLACE(pickupID)
{
	return 1280;
}