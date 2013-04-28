// Dialog is created at another location (e.g. PCMD:spawnvehicle)

DialogResponse:SpawnVehicle(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new modelID;
		new name[STRINGLENGTH_VEHICLENAME];
		if (!sscanf(inputText, "p<\t>ds[" #STRINGLENGTH_VEHICLENAME "]", modelID, name))
		{
			if (modelID)
			{
				SpawnVehicle(playerID, modelID, PVar:playerID[SPAWNVEHICLE_COLOR1], PVar:playerID[SPAWNVEHICLE_COLOR1], true);
			}
		}
	}
}