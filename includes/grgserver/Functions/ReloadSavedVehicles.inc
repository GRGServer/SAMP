ReloadSavedVehicles(playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Destroying vehicles...");
	for (new vehicleID = 0; vehicleID < MAX_VEHICLES; vehicleID++)
	{
		DestroyVehicle(vehicleID);
		VehicleProperty:vehicleID[CURRENTFUEL] = 0;
		VehicleProperty:vehicleID[JOBID] = 0;
		VehicleProperty:vehicleID[SAVEID] = 0;
	}
	AdminPrint(playerID, COLOR_INFO, "* Loading saved vehicles...");
	new count;
	mysql_query("SELECT * FROM `savedvehicles`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new vehicleID = CreateVehicleEx(strval(GetMySQLField("ModelID")), floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), floatstr(GetMySQLField("Angle")), strval(GetMySQLField("Color1")), strval(GetMySQLField("Color2")), -1);
		VehicleProperty:vehicleID[CURRENTFUEL] = floatstr(GetMySQLField("CurrentFuel"));
		VehicleProperty:vehicleID[HASNAVI] = strval(GetMySQLField("HasNavi"));
		VehicleProperty:vehicleID[JOBID] = strval(GetMySQLField("JobID"));
		VehicleProperty:vehicleID[MILEAGE] = floatstr(GetMySQLField("MileAge"));
		VehicleProperty:vehicleID[NEONLIGHTID] = strval(GetMySQLField("NeonLightID"));
		VehicleProperty:vehicleID[NUMBERPLATE] = strval(GetMySQLField("NumberPlateID"));
		VehicleProperty:vehicleID[RADIOSTATION] = strval(GetMySQLField("LastRadioStation"));
		VehicleProperty:vehicleID[SAVEID] = strval(GetMySQLField("ID"));
		LinkVehicleToInterior(vehicleID, strval(GetMySQLField("Interior")));
		ChangeVehiclePaintjob(vehicleID, strval(GetMySQLField("PaintjobID")));
		SetVehicleHealth(vehicleID, floatstr(GetMySQLField("Health")));
		if (VehicleProperty:vehicleID[NEONLIGHTID])
		{
			AddNeonLight(vehicleID, VehicleProperty:vehicleID[NEONLIGHTID] - 1);
		}
		count++;
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  %d saved vehicles loaded", count);
	count = 0;
	AdminPrint(playerID, COLOR_INFO, "* Adding vehicle components...");
	mysql_query("SELECT * FROM `vehiclecomponents`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		for (new vehicleID = 0; vehicleID < MAX_VEHICLES; vehicleID++)
		{
			if (vehicles[vehicleID][VEHICLE_SAVEID] == strval(GetMySQLField("VehicleID")))
			{
				AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component")));
				count++;
				break;
			}
		}
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  %d vehicle components added", count);
	count = 0;
	AdminPrint(playerID, COLOR_INFO, "* Adding number plates...");
	mysql_query("SELECT * FROM `numberplates`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new numberPlateID = strval(GetMySQLField("ID"));
		Count(vehicleID, MAX_VEHICLES)
		{
			if (vehicles[vehicleID][VEHICLE_NUMBERPLATE] == numberPlateID)
			{
				FormatNew:numberPlateText[16]("%s %s %d", GetMySQLField("Content1"), GetMySQLField("Content2"), strval(GetMySQLField("Content3")));
				SetVehicleNumberPlate(vehicleID, numberPlateText);
				count++;
				break;
			}
		}
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  %d number plates added", count);
}