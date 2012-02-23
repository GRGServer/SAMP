AddVehicleComponentEx(vehicleID, componentID)
{
	if (componentID)
	{
		AddVehicleComponent(vehicleID, componentID);
	}
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
	for (new vehicleID = 0; vehicleID < MAX_VEHICLES; vehicleID++)
	{
		DestroyVehicle(vehicleID);
		vehicles[vehicleID][VEHICLE_SAVEID] = 0;
		vehicles[vehicleID][VEHICLE_CURRENTFUEL] = 0;
	}
	mysql_query("SELECT * FROM `savedvehicles`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new vehicleID = CreateVehicle(strval(GetMySQLField("ModelID")), floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), floatstr(GetMySQLField("Angle")), strval(GetMySQLField("Color1")), strval(GetMySQLField("Color2")), -1);
		vehicles[vehicleID][VEHICLE_SAVEID] = strval(GetMySQLField("ID"));
		vehicles[vehicleID][VEHICLE_CURRENTFUEL] = floatstr(GetMySQLField("CurrentFuel"));
		LinkVehicleToInterior(vehicleID, strval(GetMySQLField("Interior")));
		ChangeVehicleColor(vehicleID, strval(GetMySQLField("Color1")), strval(GetMySQLField("Color2")));
		ChangeVehiclePaintjob(vehicleID, strval(GetMySQLField("PaintjobID")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_Spoiler")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_Hood")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_Roof")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_Sideskirt")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_Lamps")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_Nitro")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_Exhaust")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_Wheels")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_Stereo")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_Hydraulics")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_FrontBumper")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_RearBumper")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_VentRight")));
		AddVehicleComponentEx(vehicleID, strval(GetMySQLField("Component_VentLeft")));
	}
	mysql_free_result();
}

ReloadVehicleModels()
{
	mysql_query("SELECT * FROM `vehiclemodels`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new index = strval(GetMySQLField("ModelID")) - 400;
		vehicleModels[index][VEHICLEMODEL_FUELUSAGE] = floatstr(GetMySQLField("FuelUsage"));
		vehicleModels[index][VEHICLEMODEL_MAXFUEL] = floatstr(GetMySQLField("MaxFuel"));
	}
	mysql_free_result();
}

SaveVehicle(vehicleID, interior)
{
	if (vehicles[vehicleID][VEHICLE_SAVEID])
	{
		new query[512];
		new Float:posX; 
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetVehiclePos(vehicleID, posX, posY, posZ);
		GetVehicleZAngle(vehicleID, angle);
		format(query, sizeof(query), "UPDATE `savedvehicles` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f', `Interior` = '%d', `Color1` = '%d', `Color2` = '%d', `PaintjobID` = '%d', `CurrentFuel` = '%f' WHERE `ID` = '%d'", posX, posY, posZ, angle, interior, vehicles[vehicleID][VEHICLE_COLOR1], vehicles[vehicleID][VEHICLE_COLOR2], vehicles[vehicleID][VEHICLE_PAINTJOB], vehicles[vehicleID][VEHICLE_CURRENTFUEL], vehicles[vehicleID][VEHICLE_SAVEID]);
		mysql_query(query);
		format(query, sizeof(query), "UPDATE `savedvehicles` SET `Component_Spoiler` = '%d', `Component_Hood` = '%d', `Component_Roof` = '%d', `Component_Sideskirt` = '%d' WHERE `ID` = '%d'", GetVehicleComponentInSlot(vehicleID, CARMODTYPE_SPOILER), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_HOOD), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_ROOF), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_SIDESKIRT), vehicles[vehicleID][VEHICLE_SAVEID]);
		mysql_query(query);
		format(query, sizeof(query), "UPDATE `savedvehicles` SET `Component_Lamps` = '%d', `Component_Nitro` = '%d', `Component_Exhaust` = '%d', `Component_Wheels` = '%d' WHERE `ID` = '%d'", GetVehicleComponentInSlot(vehicleID, CARMODTYPE_LAMPS), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_NITRO), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_EXHAUST), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_WHEELS), vehicles[vehicleID][VEHICLE_SAVEID]);
		mysql_query(query);
		format(query, sizeof(query), "UPDATE `savedvehicles` SET `Component_Stereo` = '%d', `Component_Hydraulics` = '%d', `Component_FrontBumper` = '%d', `Component_RearBumper` = '%d' WHERE `ID` = '%d'", GetVehicleComponentInSlot(vehicleID, CARMODTYPE_STEREO), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_HYDRAULICS), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_FRONT_BUMPER), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_REAR_BUMPER), vehicles[vehicleID][VEHICLE_SAVEID]);
		mysql_query(query);
		format(query, sizeof(query), "UPDATE `savedvehicles` SET `Component_VentRight` = '%d', `Component_VentLeft` = '%d' WHERE `ID` = '%d'", GetVehicleComponentInSlot(vehicleID, CARMODTYPE_VENT_RIGHT), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_VENT_LEFT), vehicles[vehicleID][VEHICLE_SAVEID]);
		mysql_query(query);
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