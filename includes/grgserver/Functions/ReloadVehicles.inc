/**
 * <summary>
 *	Destroyes all vehicles, creates the vehicles saved in the database, adds vehicle components and puts the NPCs in the vehicles if the ID of the vehicle is linked to a NPC.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which executes a command which reloads the vehicles (Optional).
 * </param>
 *
 * <remarks>
 *	Vehicles with model ID 537 (Freight) and 538 (Streak) are only destroyed if isStatic is set to true!
 * </remarks>
 */

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
		new vehicleID = CreateVehicleEx(strval(GetMySQLField("modelId")), floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ")), floatstr(GetMySQLField("angle")), strval(GetMySQLField("color1")), strval(GetMySQLField("color2")), -1, isStatic);
		if (vehicleID)
		{
			VehicleProperty:vehicleID[CURRENTFUEL] = floatstr(GetMySQLField("currentFuel"));
			VehicleProperty:vehicleID[FRONTLIGHTID] = strval(GetMySQLField("frontLightId"));
			VehicleProperty:vehicleID[HASNAVI] = strval(GetMySQLField("hasNavi"));
			VehicleProperty:vehicleID[JOBID] = strval(GetMySQLField("jobId"));
			VehicleProperty:vehicleID[MILEAGE] = floatstr(GetMySQLField("mileAge"));
			VehicleProperty:vehicleID[NEONLIGHTID] = strval(GetMySQLField("neonLightId"));
			format(VehicleProperty:vehicleID[NUMBERPLATE], STRINGLENGTH_NUMBERPLATE, GetMySQLField("numberplate"));
			VehicleProperty:vehicleID[RADIOSTATION] = strval(GetMySQLField("lastRadioStation"));
			VehicleProperty:vehicleID[SAVEID] = strval(GetMySQLField("id"));
			LockVehicle(vehicleID, strval(GetMySQLField("locked")));
			LinkVehicleToInterior(vehicleID, strval(GetMySQLField("interior")));
			ChangeVehiclePaintjob(vehicleID, strval(GetMySQLField("paintjobId")));
			SetVehicleHealth(vehicleID, floatstr(GetMySQLField("health")));
			SetVehicleNumberPlate(vehicleID, VehicleProperty:vehicleID[NUMBERPLATE]);
			if (strval(GetMySQLField("ownerUserId")))
			{
				VehicleProperty:vehicleID[ALLOWPOSSAVE] = true;
			}
			else
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
			if (VehicleProperty:vehicleID[SAVEID] == strval(GetMySQLField("vehicleId")))
			{
				AddVehicleComponentEx(vehicleID, strval(GetMySQLField("component")));
				count++;
				foundVehicle = true;
				break;
			}
		}
		if (!foundVehicle)
		{
			AdminPrint(playerID, COLOR_ERROR, "  Vehicle not found: %d", strval(GetMySQLField("vehicleId")));
		}
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  %d vehicle components added", count);
	count = 0;
	AdminPrint(playerID, COLOR_INFO, "* Put NPCs in vehicles...");
	mysql_query("SELECT * FROM `npcs` WHERE `vehicleId`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new vehicleID = GetVehicleBySaveID(strval(GetMySQLField("vehicleId")));
		if (vehicleID)
		{
			VehicleProperty:vehicleID[ALLOWDESTROY] = false;
			VehicleProperty:vehicleID[ALLOWPOSSAVE] = false;
			new npcPlayerID = GetPlayerID(GetMySQLField("name"));
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