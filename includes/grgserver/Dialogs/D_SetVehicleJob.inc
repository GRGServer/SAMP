ShowDialog:SetVehicleJob(playerID)
{
	new jobs[2048];
	MySQLQuery("SELECT `id`, `name` FROM `jobs` ORDER BY `name` ASC");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		AddLine:jobs("%s\t%s", GetMySQLField("id"), GetMySQLField("name"));
	}
	mysql_free_result();
	CreateDialog(playerID, "SetVehicleJob", DIALOG_STYLE_LIST, LanguageString(playerID, "610"), jobs, "OK", LanguageString(playerID, "165"));
}

DialogResponse:SetVehicleJob(playerID, response, listItem, inputText[])
{
	if (!response)
	{
		return true;
	}
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, "146");
		return true;
	}
	new jobID;
	new jobName[STRINGLENGTH_JOBNAME];
	sscanf(inputText, "%d\t%s", jobID, jobName);
	VehicleProperty:vehicleID[JOBID] = jobID;
	return true;
}