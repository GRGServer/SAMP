// Dialog is created at another location

DialogResponse:SpawnVehicle(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new modelID;
		new name[STRINGLENGTH_VEHICLENAME];
		if (!sscanf(inputText, "p:ds", modelID, name))
		{
			if (modelID)
			{
				SpawnVehicle(playerID, modelID, PVar:playerID[SPAWNVEHICLE_COLOR1], PVar:playerID[SPAWNVEHICLE_COLOR1], true);
			}
		}
	}
}