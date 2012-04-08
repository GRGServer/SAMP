ReloadVehicleModels()
{
	print("* Loading vehicle models...");
	mysql_query("SELECT * FROM `vehiclemodels`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new index = strval(GetMySQLField("ID")) - 400;
		vehicleModels[index][VEHICLEMODEL_FUELUSAGE] = floatstr(GetMySQLField("FuelUsage"));
		vehicleModels[index][VEHICLEMODEL_MAXFUEL] = floatstr(GetMySQLField("MaxFuel"));
		format(vehicleModels[index][VEHICLEMODEL_NAME], STRINGLENGTH_VEHICLENAME, GetMySQLField("Name"));
		format(vehicleModels[index][VEHICLEMODEL_TYPE], STRINGLENGTH_VEHICLETYPE, GetMySQLField("Type"));
	}
	mysql_free_result();
}