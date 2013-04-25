ShowDialog:OrderVehicle(playerID)
{
	new vehicleList[2048];
	mysql_query("SELECT `name` FROM `vehiclemodels` ORDER BY `name` ASC");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		if (strlen(vehicleList))
		{
			Format:vehicleList("%s\n", vehicleList);
		}
		Format:vehicleList("%s%s", vehicleList, GetMySQLField("name"));
	}
	mysql_free_result();
	CreateDialog(playerID, "OrderVehicle", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:113("Order a vehicle")), vehicleList, LanguageString(playerID, StringID:413("Order")), LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:OrderVehicle(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new modelID = strval(GetMySQLValue("vehiclemodels", "id", "name", inputText));
		if (modelID)
		{
			new missionID = CreateJob(playerID, JOB_VEHICLEDEALER);
			if (missionID)
			{
				AddJobData(missionID, "Type", "GetOrderedVehicle");
				AddJobData(missionID, "VehicleModelID", val2str(modelID));
				SendClientMessageEx(playerID, COLOR_INFO, StringID:38("Job created (Order number: %d)"), missionID);
				CreateVehicleEx(modelID, -1557.4092, 114.7485, 3.0939, 136.5509, 12, 41, false);// TODO: Multiple vehicles at the same position
			}
		}
	}
}