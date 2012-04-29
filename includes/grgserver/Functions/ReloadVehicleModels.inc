ReloadVehicleModels(playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Loading vehicle models...");
	new count;
	mysql_query("SELECT * FROM `vehiclemodels`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new index = strval(GetMySQLField("ID")) - 400;
		if (index > 0 && index <= sizeof(vehicleModels))
		{
			vehicleModels[index][VEHICLEMODEL_FUELUSAGE] = floatstr(GetMySQLField("FuelUsage"));
			vehicleModels[index][VEHICLEMODEL_MAXFUEL] = floatstr(GetMySQLField("MaxFuel"));
			format(vehicleModels[index][VEHICLEMODEL_NAME], STRINGLENGTH_VEHICLENAME, GetMySQLField("Name"));
			format(vehicleModels[index][VEHICLEMODEL_TYPE], STRINGLENGTH_VEHICLETYPE, GetMySQLField("Type"));
			count++;
		}
		else
		{
			printf("Invalid ModelID: %s", GetMySQLField("ID"));
		}
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  %d vehicle models loaded", count);
}