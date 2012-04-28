PickupEvent:HOUSE(playerID, pickupID)
{
	new ownerUserID = strval(GetMySQLValue("buildings", "OwnerUserID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
	if (ownerUserID)
	{
		if (ownerUserID == PVar:playerID[USERID])
		{
			PVar:playerID[DIALOGBUILDINGID] = strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
			ShowDialog(playerID, DIALOG_HOUSE);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 141, GetMySQLValue("users", "Username", "ID", val2str(ownerUserID)));
		}
	}
	else
	{
		new Float:price = floatstr(GetMySQLValue("buildings", "Price", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
		if (price <= PVar:playerID[BANKMONEY])
		{
			PVar:playerID[DIALOGBUILDINGID] = strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
			ShowDialog(playerID, DIALOG_BUYHOUSE, FormatMoney(price));
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 22, price, PVar:playerID[BANKMONEY]);
		}
	}
}

PickupModelID:HOUSE(pickupID)
{
	if (strval(GetMySQLValue("buildings", "OwnerUserID", "PickupID", val2str(pickupID))))
	{
		return 1272;// Bought
	}
	else
	{
		return 1273;// Available
	}
}