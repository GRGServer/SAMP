GetPickupInfoByType(pickupID, type[], &typeID, &modelID)
{
	if (!strcmp(type, "BANK", true))
	{
		typeID = PICKUPTYPE_BANK;
		modelID = PICKUP_BANK;
		return true;
	}
	if (!strcmp(type, "GASSTATION", true))
	{
		typeID = PICKUPTYPE_GASSTATION;
		modelID = PICKUP_GASSTATION;
		return true;
	}
	if (!strcmp(type, "HOUSE", true))
	{
		typeID = PICKUPTYPE_HOUSE;
		if (strval(GetMySQLValue("buildings", "OwnerUserID", "PickupID", val2str(pickupID))))
		{
			modelID = PICKUP_HOUSEBOUGHT;
		}
		else
		{
			modelID = PICKUP_HOUSEAVAILABLE;
		}
		return true;
	}
	if (!strcmp(type, "HOTEL", true))
	{
		typeID = PICKUPTYPE_HOTEL;
		modelID = PICKUP_HOTEL;
		return true;
	}
	if (!strcmp(type, "INBANK", true))
	{
		typeID = PICKUPTYPE_INBANK;
		modelID = PICKUP_INBANK;
		return true;
	}
	if (!strcmp(type, "INPOLICE", true))
	{
		typeID = PICKUPTYPE_INPOLICE;
		modelID = PICKUP_INPOLICE;
		return true;
	}
	if (!strcmp(type, "POLICE", true))
	{
		typeID = PICKUPTYPE_POLICE;
		modelID = PICKUP_POLICE;
		return true;
	}
	if (!strcmp(type, "TRUCKER", true))
	{
		typeID = PICKUPTYPE_TRUCKER;
		modelID = PICKUP_TRUCKER;
		return true;
	}
	if (!strcmp(type, "VEHICLEDEALER", true))
	{
		typeID = PICKUPTYPE_VEHICLEDEALER;
		modelID = PICKUP_VEHICLEDEALER;
		return true;
	}
	return false;
}