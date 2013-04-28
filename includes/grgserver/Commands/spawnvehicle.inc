PCMD:spawnvehicle[SPAWNVEHICLE](playerID, params[], StringID:505("Spawn a vehicle"))
{
	new vehicleName[20];
	new modelID;
	new color1;
	new color2;
	if (sscanf(params, "ddd", modelID, color1, color2))
	{
		if (!sscanf(params, "d", modelID))
		{
			color1 = -1;
			color2 = -1;
		}
		else
		{
			if (sscanf(params, "s[20]dd", vehicleName, color1, color2))
			{
				if (sscanf(params, "s[20]", vehicleName))
				{
					CmdUsageMsg(playerID, "spawnvehicle", "ModelID/Name/t:Type", "[Color1]", "[Color2]");
					return COMMAND_USAGE;
				}
				else
				{
					color1 = -1;
					color2 = -1;
				}
			}
			new type;
			new parameter[16];
			new vehicleList[2048];
			new foundVehicles;
			if (sscanf(vehicleName, "p<:>cs[16]", type, parameter))
			{
				Foreach(arrayIndex, vehicleModels)
				{
					if (strfind(vehicleModels[arrayIndex][VEHICLEMODEL_NAME], vehicleName, true) != -1)
					{
						AddLine:vehicleList("%d\t%s", arrayIndex + 400, vehicleModels[arrayIndex][VEHICLEMODEL_NAME]);
						foundVehicles++;
						modelID = arrayIndex + 400;
					}
				}
			}
			else
			{
				switch (type)
				{
					case 't':
					{
						Foreach(arrayIndex, vehicleModels)
						{
							if (IsStr(vehicleModels[arrayIndex][VEHICLEMODEL_TYPE], parameter))
							{
								AddLine:vehicleList("%d\t%s", arrayIndex + 400, vehicleModels[arrayIndex][VEHICLEMODEL_NAME]);
								foundVehicles++;
								modelID = arrayIndex + 400;
							}
						}
					}
					default:
					{
						SendClientMessageEx(playerID, COLOR_ERROR, StringID:58("Invalid type!"));
						return COMMAND_ERROR;
					}
				}
			}
			if (foundVehicles > 1)
			{
				PVar:playerID[SPAWNVEHICLE_COLOR1] = color1;
				PVar:playerID[SPAWNVEHICLE_COLOR2] = color2;
				FormatNew:title[64](LanguageString(playerID, StringID:122("Spawn a vehicle [%s]")), vehicleName);
				CreateDialog(playerID, "SpawnVehicle", DIALOG_STYLE_LIST, title, vehicleList, LanguageString(playerID, StringID:205("Spawn")), LanguageString(playerID, StringID:165("Cancel")));
				modelID = -1;
			}
		}
	}
	if (modelID == -1)
	{
		return COMMAND_OK;
	}
	if (SpawnVehicle(playerID, modelID, color1, color2, true))
	{
		return COMMAND_OK;
	}
	return COMMAND_ERROR;
}