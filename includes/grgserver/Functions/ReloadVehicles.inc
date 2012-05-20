ReloadVehicles(isStatic, playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Destroying vehicles...");
	Count1(vehicleID, MAX_VEHICLES)
	{
		new modelID = GetVehicleModel(vehicleID);
		if (modelID)
		{
			if (isStatic || (modelID != 537 && modelID != 538))// We are unable to respawn Freight and Streak using CreateVehicle... so only remove them if isStatic is true
			{
				DestroyVehicle(vehicleID);
			}
		}
		VehicleProperty:vehicleID[CURRENTFUEL] = 0;
		VehicleProperty:vehicleID[JOBID] = 0;
		VehicleProperty:vehicleID[SAVEID] = 0;
	}
	AdminPrint(playerID, COLOR_INFO, "* Loading vehicles...");
	new count;
	mysql_query("SELECT * FROM `vehicles`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new vehicleID = CreateVehicleEx(strval(GetMySQLField("ModelID")), floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), floatstr(GetMySQLField("Angle")), strval(GetMySQLField("Color1")), strval(GetMySQLField("Color2")), -1, isStatic);
		if (vehicleID)
		{
			VehicleProperty:vehicleID[ALLOWSAVE] = true;
			VehicleProperty:vehicleID[CURRENTFUEL] = floatstr(GetMySQLField("CurrentFuel"));
			VehicleProperty:vehicleID[FRONTLIGHTID] = strval(GetMySQLField("FrontLightID"));
			VehicleProperty:vehicleID[HASNAVI] = strval(GetMySQLField("HasNavi"));
			VehicleProperty:vehicleID[JOBID] = strval(GetMySQLField("JobID"));
			VehicleProperty:vehicleID[MILEAGE] = floatstr(GetMySQLField("MileAge"));
			VehicleProperty:vehicleID[NEONLIGHTID] = strval(GetMySQLField("NeonLightID"));
			format(VehicleProperty:vehicleID[NUMBERPLATE], STRINGLENGTH_NUMBERPLATE, GetMySQLField("Numberplate"));
			VehicleProperty:vehicleID[RADIOSTATION] = strval(GetMySQLField("LastRadioStation"));
			VehicleProperty:vehicleID[SAVEID] = strval(GetMySQLField("ID"));
			LinkVehicleToInterior(vehicleID, strval(GetMySQLField("Interior")));
			ChangeVehiclePaintjob(vehicleID, strval(GetMySQLField("PaintjobID")));
			SetVehicleHealth(vehicleID, floatstr(GetMySQLField("Health")));
			SetVehicleNumberPlate(vehicleID, VehicleProperty:vehicleID[NUMBERPLATE]);
			if (!strval(GetMySQLField("OwnerUserID")))
			{
				VehicleProperty:vehicleID[ALLOWDESTROY] = false;
			}
			count++;
		}
		else
		{
			AdminPrint(playerID, COLOR_ERROR, "  Can not create vehicle!");
		}
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  %d vehicles loaded", count);
	count = 0;
	AdminPrint(playerID, COLOR_INFO, "* Adding vehicle components...");
	mysql_query("SELECT * FROM `vehiclecomponents`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new foundVehicle;
		Count1(vehicleID, MAX_VEHICLES)
		{
			if (VehicleProperty:vehicleID[SAVEID] == strval(GetMySQLField("VehicleID")))
			{
				AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component")));
				count++;
				foundVehicle = true;
				break;
			}
		}
		if (!foundVehicle)
		{
			AdminPrint(playerID, COLOR_ERROR, "  Vehicle not found: %d", strval(GetMySQLField("VehicleID")));
		}
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  %d vehicle components added", count);
	count = 0;
	AdminPrint(playerID, COLOR_INFO, "* Put NPCs in vehicles...");
	mysql_query("SELECT * FROM `npcs` WHERE `VehicleID` != '0'");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new vehicleID = GetVehicleBySaveID(strval(GetMySQLField("VehicleID")));
		if (vehicleID)
		{
			VehicleProperty:vehicleID[ALLOWDESTROY] = false;
			VehicleProperty:vehicleID[ALLOWSAVE] = false;
			new npcPlayerID;
			FormatNew:npcName[MAX_PLAYER_NAME]("NPC_%s", GetMySQLField("Name"));
			sscanf(npcName, "u", npcPlayerID);
			if (npcPlayerID != INVALID_PLAYER_ID)
			{
				PutPlayerInVehicle(npcPlayerID, vehicleID, 0);
				count++;
			}
		}
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  %d NPCs put in vehicles", count);
}