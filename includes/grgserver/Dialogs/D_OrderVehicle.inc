ShowDialog:ORDERVEHICLE(playerID)
{
	new vehicleList[2048];
	mysql_query("SELECT * FROM `vehiclemodels` ORDER BY `Name` ASC");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		if (strlen(vehicleList))
		{
			Format:vehicleList("%s\n", vehicleList);
		}
		Format:vehicleList("%s%s", vehicleList, GetMySQLField("Name"));
	}
	mysql_free_result();
	CreateDialog(playerID, "ORDERVEHICLE", DIALOG_STYLE_LIST, LanguageString(playerID, 113), vehicleList, LanguageString(playerID, 413), LanguageString(playerID, 165));
}

DialogResponse:ORDERVEHICLE(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new modelID = strval(GetMySQLValue("vehiclemodels", "ID", "Name", inputText));
		if (modelID)
		{
			new missionID = CreateJob(playerID, JOB_VEHICLEDEALER);
			if (missionID)
			{
				AddJobData(missionID, "Type", "GetOrderedVehicle");
				AddJobData(missionID, "VehicleModelID", val2str(modelID));
				SendClientMessageEx(playerID, COLOR_INFO, 38, missionID);
			}
		}
	}
}