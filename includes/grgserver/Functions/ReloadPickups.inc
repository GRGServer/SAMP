ReloadPickups(playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Destroying pickups...");
	for (new pickupID = 0; pickupID < MAX_PICKUPS; pickupID++)
	{
		DestroyPickup(pickupID);
		pickups[pickupID][PICKUP_ID] = 0;
		pickups[pickupID][PICKUP_TYPE] = 0;
	}
	AdminPrint(playerID, COLOR_INFO, "* Loading pickups...");
	for (new pickupID = 0; pickupID < MAX_PICKUPS; pickupID++)
	{
		pickupLoader[pickupID][PICKUPLOADER_TYPE] = 0;
	}
	mysql_query("SELECT * FROM `pickups`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new pickupID = strval(GetMySQLField("id"));
		format(pickupLoader[pickupID][PICKUPLOADER_TYPE], STRINGLENGTH_PICKUPTYPE, GetMySQLField("type"));
		pickupLoader[pickupID][PICKUPLOADER_POSX] = floatstr(GetMySQLField("posX"));
		pickupLoader[pickupID][PICKUPLOADER_POSY] = floatstr(GetMySQLField("posY"));
		pickupLoader[pickupID][PICKUPLOADER_POSZ] = floatstr(GetMySQLField("posZ"));
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "* Creating pickups...");
	new count;
	for (new pickupID = 0; pickupID < MAX_PICKUPS; pickupID++)
	{
		if (strlen(pickupLoader[pickupID][PICKUPLOADER_TYPE]))
		{
			if (!AddPickup(pickupID, pickupLoader[pickupID][PICKUPLOADER_TYPE], pickupLoader[pickupID][PICKUPLOADER_POSX], pickupLoader[pickupID][PICKUPLOADER_POSY], pickupLoader[pickupID][PICKUPLOADER_POSZ]))
			{
				AdminPrint(playerID, COLOR_ERROR, "Invalid pickup type: %s", pickupLoader[pickupID][PICKUPLOADER_TYPE]);
			}
			else
			{
				count++;
			}
		}
	}
	AdminPrint(playerID, COLOR_INFO, "  %d pickups created", count);
}