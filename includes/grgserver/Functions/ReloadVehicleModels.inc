ReloadVehicleModels(playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Loading vehicle models...");
	new count;
	mysql_query("SELECT * FROM `vehiclemodels`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new modelIndex = strval(GetMySQLField("id")) - 400;
		if (modelIndex >= 0 && modelIndex < sizeof(vehicleModels))
		{
			vehicleModels[modelIndex][VEHICLEMODEL_FUELUSAGE] = floatstr(GetMySQLField("fuelUsage"));
			vehicleModels[modelIndex][VEHICLEMODEL_MAXFUEL] = floatstr(GetMySQLField("maxFuel"));
			format(vehicleModels[modelIndex][VEHICLEMODEL_NAME], STRINGLENGTH_VEHICLENAME, GetMySQLField("name"));
			vehicleModels[modelIndex][VEHICLEMODEL_TAX] = floatstr(GetMySQLField("tax"));
			format(vehicleModels[modelIndex][VEHICLEMODEL_TYPE], STRINGLENGTH_VEHICLETYPE, GetMySQLField("type"));
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