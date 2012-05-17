PickupEvent:HOUSE(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			new ownerUserID = strval(GetMySQLValue("properties", "OwnerUserID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
			if (ownerUserID)
			{
				if (ownerUserID == PVar:playerID[USERID])
				{
					PVar:playerID[DIALOGPROPERTYID] = strval(GetMySQLValue("properties", "ID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
					ShowDialog:House(playerID);
				}
				else
				{
					SendClientMessageEx(playerID, COLOR_ERROR, 141, GetMySQLValue("users", "Username", "ID", val2str(ownerUserID)));
				}
			}
			else
			{
				new Float:price = floatstr(GetMySQLValue("properties", "Price", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
				if (price <= PVar:playerID[BANKMONEY])
				{
					PVar:playerID[DIALOGPROPERTYID] = strval(GetMySQLValue("properties", "ID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
					ShowDialog:BuyHouse(playerID, price);
				}
				else
				{
					SendClientMessageEx(playerID, COLOR_ERROR, 22, price, PVar:playerID[BANKMONEY]);
				}
			}
			return true;
		}
		case PICKUPEVENT_PICKUP:
		{
			if (permissions[playerID][PERMISSION_MAPPER])
			{
				SendClientMessageEx(playerID, COLOR_INFO, 338);
			}
			return false;
		}
	}
	return false;
}

PickupModelID:HOUSE(pickupID)
{
	if (strval(GetMySQLValue("properties", "OwnerUserID", "PickupID", val2str(pickupID))))
	{
		return 1272;// Bought
	}
	else
	{
		return 1273;// Available
	}
}