AddVehicleComponentEx(vehicleID, componentID)
{
	if (componentID)
	{
		AddVehicleComponent(vehicleID, componentID);
	}
}

CheckVehiclePermission(playerID, vehicleID)
{
	if (!vehicles[vehicleID][VEHICLE_SAVEID] && !permissions[playerID][PERMISSION_MAPPER])
	{
		SendClientMessage(playerID, COLOR_ERROR, "Dieses Fahrzeug kann nur von der Gruppe 'Mapper' verwendet werden!");
		RemovePlayerFromVehicle(playerID);
		return false;
	}
	new ownerUserID = strval(GetMySQLValue("savedvehicles", "OwnerUserID", "ID", val2str(vehicles[vehicleID][VEHICLE_SAVEID])));
	if (!ownerUserID)
	{
		ShowDialog(playerID, DIALOG_BUYVEHICLE, FormatMoney(floatstr(GetMySQLValue("savedvehicles", "Price", "ID", val2str(vehicles[vehicleID][VEHICLE_SAVEID])))));
		return true;
	}
	if (ownerUserID != GetUserID(playerID))
	{
		SendClientMessage(playerID, COLOR_ERROR, "Dieses Fahrzeug besitzt bereits ein anderer Spieler");
		RemovePlayerFromVehicle(playerID);
		return false;
	}
	return true;
}

GetVehicleEngineState(vehicleID)
{
	new engine;
	new lights;
	new alarm;
	new doors;
	new bonnet;
	new boot;
	new objective;
	GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
	return engine;
}

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
		new vehicleID = CreateVehicle(strval(GetMySQLField("ModelID")), floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), floatstr(GetMySQLField("Angle")), strval(GetMySQLField("Color1")), strval(GetMySQLField("Color2")), -1);
		vehicles[vehicleID][VEHICLE_CURRENTFUEL] = floatstr(GetMySQLField("CurrentFuel"));
		vehicles[vehicleID][VEHICLE_SAVEID] = strval(GetMySQLField("ID"));
		vehicles[vehicleID][VEHICLE_JOBID] = strval(GetMySQLField("JobID"));
		LinkVehicleToInterior(vehicleID, strval(GetMySQLField("Interior")));
		ChangeVehicleColor(vehicleID, strval(GetMySQLField("Color1")), strval(GetMySQLField("Color2")));
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

ReloadVehicleModels()
{
	print("* Loading vehicle models...");
	mysql_query("SELECT * FROM `vehiclemodels`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new index = strval(GetMySQLField("ModelID")) - 400;
		vehicleModels[index][VEHICLEMODEL_FUELUSAGE] = floatstr(GetMySQLField("FuelUsage"));
		vehicleModels[index][VEHICLEMODEL_MAXFUEL] = floatstr(GetMySQLField("MaxFuel"));
		format(vehicleModels[index][VEHICLEMODEL_NAME], 20, GetMySQLField("Name"));
	}
	mysql_free_result();
}

SaveVehicle(vehicleID, interior)
{
	if (vehicles[vehicleID][VEHICLE_SAVEID])
	{
		new Float:posX; 
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetVehiclePos(vehicleID, posX, posY, posZ);
		GetVehicleZAngle(vehicleID, angle);
		MySQLQuery("UPDATE `savedvehicles` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f', `Interior` = '%d', `CurrentFuel` = '%f' WHERE `ID` = '%d'", posX, posY, posZ, angle, interior, vehicles[vehicleID][VEHICLE_CURRENTFUEL], vehicles[vehicleID][VEHICLE_SAVEID]);
	}
}

SetVehicleEngineState(vehicleID, newState)
{
	new engine;
	new lights;
	new alarm;
	new doors;
	new bonnet;
	new boot;
	new objective;
	GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
	if (engine != newState)
	{
		SetVehicleParamsEx(vehicleID, newState, lights, alarm, doors, bonnet, boot, objective);
	}
}