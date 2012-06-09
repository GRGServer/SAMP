ReloadVehicleModels(playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Loading vehicle models...");
	new count;
	mysql_query("SELECT * FROM `vehiclemodels`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new index = strval(GetMySQLField("id")) - 400;
		if (index >= 0 && index <= sizeof(vehicleModels))
		{
			vehicleModels[index][VEHICLEMODEL_FUELUSAGE] = floatstr(GetMySQLField("fuelUsage"));
			vehicleModels[index][VEHICLEMODEL_MAXFUEL] = floatstr(GetMySQLField("maxFuel"));
			format(vehicleModels[index][VEHICLEMODEL_NAME], STRINGLENGTH_VEHICLENAME, GetMySQLField("name"));
			format(vehicleModels[index][VEHICLEMODEL_TYPE], STRINGLENGTH_VEHICLETYPE, GetMySQLField("type"));
			count++;
		}
		else
		{
			printf("Invalid ModelID: %s", GetMySQLField("id"));
		}
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  %d vehicle models loaded", count);
}