ReloadSavedVehicles()
{
	print("* Destroying vehicles...");
	for (new vehicleID = 0; vehicleID < MAX_VEHICLES; vehicleID++)
	{
		DestroyVehicle(vehicleID);
		vehicles[vehicleID][VEHICLE_CURRENTFUEL] = 0;
		vehicles[vehicleID][VEHICLE_JOBID] = 0;
		vehicles[vehicleID][VEHICLE_SAVEID] = 0;
	}
	print("* Loading saved vehicles...");
	mysql_query("SELECT * FROM `savedvehicles`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new vehicleID = CreateVehicleEx(strval(GetMySQLField("ModelID")), floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), floatstr(GetMySQLField("Angle")), strval(GetMySQLField("Color1")), strval(GetMySQLField("Color2")), -1, floatstr(GetMySQLField("CurrentFuel")), strval(GetMySQLField("ID")), strval(GetMySQLField("JobID")));
		LinkVehicleToInterior(vehicleID, strval(GetMySQLField("Interior")));
		ChangeVehiclePaintjob(vehicleID, strval(GetMySQLField("PaintjobID")));
	}
	mysql_free_result();
	print("* Adding vehicle components...");
	mysql_query("SELECT * FROM `vehiclecomponents`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		for (new vehicleID = 0; vehicleID < MAX_VEHICLES; vehicleID++)
		{
			if (vehicles[vehicleID][VEHICLE_SAVEID] == strval(GetMySQLField("VehicleID")))
			{
				AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component")));
				break;
			}
		}
	}
	mysql_free_result();
}