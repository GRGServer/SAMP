AddPickup(pickupID, type[], Float:posX, Float:posY, Float:posZ, saveToDB)
{
	new pickupTypeID = -1;
	new modelID;
	new spawnType;
	new pickup;
	if (!strcmp(type, "BANK", true))
	{
		pickupTypeID = PICKUPTYPE_BANK;
		modelID = PICKUP_BANK;
		spawnType = 23;
	}
	if (!strcmp(type, "GASSTATION", true))
	{
		pickupTypeID = PICKUPTYPE_GASSTATION;
		modelID = PICKUP_GASSTATION;
		spawnType = 14;
	}
	if (!strcmp(type, "HOUSE", true))
	{
		pickupTypeID = PICKUPTYPE_HOUSE;
		if (strval(GetMySQLValue("buildings", "OwnerUserID", "PickupID", val2str(pickupID))))
		{
			modelID = PICKUP_HOUSEBOUGHT;
		}
		else
		{
			modelID = PICKUP_HOUSEAVAILABLE;
		}
		spawnType = 23;
	}
	if (pickupTypeID == -1)
	{
		return -1;
	}
	else
	{
		pickup = CreatePickup(modelID, spawnType, posX, posY, posZ);
		pickups[pickup][PICKUP_TYPE] = pickupTypeID;
		if (saveToDB)
		{
			new query[256];
			format(query, sizeof(query), "INSERT INTO `pickups` (`PosX`, `PosY`, `PosZ`, `Type`) VALUES('%f', '%f', '%f', '%s')", posX, posY, posZ, type);
			mysql_query(query);
			pickups[pickup][PICKUP_ID] = mysql_insert_id();
			return pickups[pickup][PICKUP_ID];
		}
		else
		{
			pickups[pickup][PICKUP_ID] = pickupID;
			return -2;
		}
	}
}

ReloadPickup(pickupID)
{
	for (new internalPickupID = 0; internalPickupID < MAX_PICKUPS; internalPickupID++)
	{
		if (pickups[internalPickupID][PICKUP_ID] == pickupID)
		{
			DestroyPickup(internalPickupID);
			pickups[internalPickupID][PICKUP_ID] = 0;
			pickups[internalPickupID][PICKUP_TYPE] = 0;
			break;
		}
	}
	new query[256];
	format(query, sizeof(query), "SELECT * FROM `pickups` WHERE `ID` = '%d'", pickupID);
	mysql_query(query);
	mysql_store_result();
	if (AddPickup(strval(GetMySQLField("ID")), GetMySQLField("Type"), floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), false) == -1)
	{
		printf("Invalid pickup type: %s", GetMySQLField("Type"));
	}
	mysql_free_result();
}

ReloadPickups()
{
	print("* Loading pickups...");
	mysql_query("SELECT * FROM `pickups`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new pickupID = strval(GetMySQLField("ID"));
		printf("Loading pickup %d from database", pickupID);
		format(pickupLoader[pickupID][PICKUPLOADER_TYPE], 256, GetMySQLField("Type"));
		pickupLoader[pickupID][PICKUPLOADER_POSX] = floatstr(GetMySQLField("PosX"));
		pickupLoader[pickupID][PICKUPLOADER_POSY] = floatstr(GetMySQLField("PosY"));
		pickupLoader[pickupID][PICKUPLOADER_POSZ] = floatstr(GetMySQLField("PosZ"));
	}
	mysql_free_result();
	print("* Creating pickups...");
	for (new pickupID = 0; pickupID < MAX_PICKUPS; pickupID++)
	{
		DestroyPickup(pickupID);
		if (strlen(pickupLoader[pickupID][PICKUPLOADER_TYPE]))
		{
			printf("Adding pickup %d (Type: %s)", pickupID, pickupLoader[pickupID][PICKUPLOADER_TYPE]);
			if (AddPickup(pickupID, pickupLoader[pickupID][PICKUPLOADER_TYPE], pickupLoader[pickupID][PICKUPLOADER_POSX], pickupLoader[pickupID][PICKUPLOADER_POSY], pickupLoader[pickupID][PICKUPLOADER_POSZ], false) == -1)
			{
				printf("Invalid pickup type: %s", pickupLoader[pickupID][PICKUPLOADER_TYPE]);
			}
		}
	}
}