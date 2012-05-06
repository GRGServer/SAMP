ReloadPickups(playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Destroying pickups...");
	for (new pickupID = 0; pickupID < MAX_PICKUPS; pickupID++)
	{
		DestroyPickup(pickupID);
	}
	AdminPrint(playerID, COLOR_INFO, "* Loading pickups...");
	for (new pickupID = 0; pickupID < MAX_PICKUPS; pickupID++)
	{
		if (strlen(pickupLoader[pickupID][PICKUPLOADER_TYPE]))
		{
			strdel(pickupLoader[pickupID][PICKUPLOADER_TYPE], 0, strlen(pickupLoader[pickupID][PICKUPLOADER_TYPE]));
		}
	}
	mysql_query("SELECT * FROM `pickups`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new pickupID = strval(GetMySQLField("ID"));
		format(pickupLoader[pickupID][PICKUPLOADER_TYPE], STRINGLENGTH_PICKUPTYPE, GetMySQLField("Type"));
		pickupLoader[pickupID][PICKUPLOADER_POSX] = floatstr(GetMySQLField("PosX"));
		pickupLoader[pickupID][PICKUPLOADER_POSY] = floatstr(GetMySQLField("PosY"));
		pickupLoader[pickupID][PICKUPLOADER_POSZ] = floatstr(GetMySQLField("PosZ"));
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "* Creating pickups...");
	new count;
	for (new pickupID = 0; pickupID < MAX_PICKUPS; pickupID++)
	{
		if (strlen(pickupLoader[pickupID][PICKUPLOADER_TYPE]))
		{
			if (AddPickup(pickupID, pickupLoader[pickupID][PICKUPLOADER_TYPE], pickupLoader[pickupID][PICKUPLOADER_POSX], pickupLoader[pickupID][PICKUPLOADER_POSY], pickupLoader[pickupID][PICKUPLOADER_POSZ], false) == -1)
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