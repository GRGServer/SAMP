IsValidPickupType(type[])
{
	new functionName[MAX_FUNCTION_NAME];
	Format:functionName("PUE_%s", type);// PUE = PickUpEvent
	if (funcidx(functionName) == -1)
	{
		return false;
	}
	Format:functionName("PUMID_%s", type);// PUMID = PickUpModelID
	if (funcidx(functionName) == -1)
	{
		return false;
	}
	return true;
}