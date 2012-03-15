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
		format(vehicleModels[index][VEHICLEMODEL_TYPE], 16, GetMySQLField("Type"));
	}
	mysql_free_result();
}