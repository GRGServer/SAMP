PickupEvent(playerID, pickupID, eventType)
{
	FormatNew:functionName[MAX_FUNCTION_NAME]("PUE_%s", pickups[pickupID][PICKUP_TYPE]);// PUE = PickUpEvent
	if (funcidx(functionName) == -1)
	{
		printf("Unknown pickup type: %s", pickups[pickupID][PICKUP_TYPE]);
		return false;
	}
	if (!CallLocalFunction(functionName, "ddd", playerID, pickupID, eventType))
	{
		return false;
	}
	PlaySound(playerID, SOUND_PICKUPEVENT);
	return true;
}