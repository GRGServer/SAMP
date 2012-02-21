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

SaveVehicle(vehicleID, interior)
{
	if (vehicles[vehicleID][VEHICLE_SAVEID])
	{
		printf("Saving vehicle %d", vehicleID);
		new query[512];
		new Float:posX; 
		new Float:posY;
		new Float:posZ;
		GetVehiclePos(vehicleID, posX, posY, posZ);
		format(query, sizeof(query), "UPDATE `savedvehicles` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Interior` = '%d', `Color1` = '%d', `Color2` = '%d', `PaintjobID` = '%d', `CurrentFuel` = '%f' WHERE `ID` = '%d'", posX, posY, posZ, interior, vehicles[vehicleID][VEHICLE_COLOR1], vehicles[vehicleID][VEHICLE_COLOR2], vehicles[vehicleID][VEHICLE_PAINTJOB], vehicles[vehicleID][VEHICLE_CURRENTFUEL], vehicles[vehicleID][VEHICLE_SAVEID]);
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