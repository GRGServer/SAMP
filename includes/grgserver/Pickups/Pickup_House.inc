PickupEvent:HOUSE(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			new ownerUserID = strval(GetMySQLValue("properties", "ownerUserId", "pickupId", val2str(pickups[pickupID][PICKUP_ID])));
			if (ownerUserID)
			{
				if (ownerUserID == PVar:playerID[USERID])
				{
					PVar:playerID[DIALOGPROPERTYID] = strval(GetMySQLValue("properties", "id", "pickupId", val2str(pickups[pickupID][PICKUP_ID])));
					ShowDialog:House(playerID);
				}
				else
				{
					SendClientMessageEx(playerID, COLOR_ERROR, StringID:141("This house has been already bought by %s!"), GetMySQLValue("users", "username", "id", val2str(ownerUserID)));
				}
			}
			else
			{
				new Float:price = floatstr(GetMySQLValue("properties", "price", "pickupId", val2str(pickups[pickupID][PICKUP_ID])));
				new Float:bankMoney = GetBankMoney(playerID);
				if (price <= bankMoney)
				{
					PVar:playerID[DIALOGPROPERTYID] = strval(GetMySQLValue("properties", "id", "pickupId", val2str(pickups[pickupID][PICKUP_ID])));
					ShowDialog:BuyHouse(playerID, price);
				}
				else
				{
					SendClientMessageEx(playerID, COLOR_ERROR, StringID:22("You need %m to buy this property! But you only have %m at you bank account."), price, bankMoney);
				}
			}
			return true;
		}
		case PICKUPEVENT_PICKUP:
		{
			if (permissions[playerID][PERMISSION_MAPPER])
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:338("Press ~k~~SNEAK_ABOUT~ to select the property linked to this pickup"));
			}
			return false;
		}
	}
	return false;
}

PickupModelID:HOUSE(pickupID)
{
	if (strval(GetMySQLValue("properties", "ownerUserId", "pickupId", val2str(pickupID))))
	{
		return 1272;// Bought
	}
	else
	{
		return 1273;// Available
	}
}