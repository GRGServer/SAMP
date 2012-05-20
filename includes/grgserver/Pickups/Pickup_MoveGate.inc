PickupEvent:MOVEGATE(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			new objectID = strval(GetMySQLValue("gates", "ObjectID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
			if (objectID)
			{
				PVar:playerID[GATEOBJECTID] = objectID;
				TogglePlayerControllable(playerID, false);
				ShowMessage(playerID, 9, 4000);
			}
			else
			{
				AdminPrint(playerID, COLOR_ERROR, "Pickup %d of type MOVEGATE has no assigned object!", pickups[pickupID][PICKUP_ID]);
			}
			return true;
		}
	}
	return false;
}

PickupModelID:MOVEGATE(pickupID)
{
	return 19273;
}