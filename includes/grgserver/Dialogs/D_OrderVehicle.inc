ShowDialog:OrderVehicle(playerID)
{
	new vehicleList[2048];
	Foreach(arrayIndex, vehicleModels)
	{
		AddLine(vehicleList, vehicleModels[arrayIndex][VEHICLEMODEL_NAME]);
	}
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
			}
		}
	}
}