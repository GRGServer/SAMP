ReloadVehicleModels(playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Unloading vehicle model colors...");
	Foreach(arrayIndex, vehicleColors)
	{
		Count(colorIndex, MAX_VEHICLE_COLORS)
		{
			vehicleColors[arrayIndex][colorIndex] = {-1, -1};
		}
	}

	AdminPrint(playerID, COLOR_INFO, "* Loading vehicle models...");
	new count;
	new XMLNode:xml = XML_LoadDocument(FILE_VEHICLEMODELS);
	xml = XML_GetFirstChild(xml, "vehiclemodels");
	new XMLNode:modelNode = XML_GetFirstChild(xml, "model");
	while (modelNode)
	{
		new value[100];
		XML_GetAttribute(modelNode, "id", value);
		new modelID = strval(value);

		if (modelID >= 400 && modelID <= 611)
		{
			new arrayIndex = modelID - 400;// First array element starts with 0, vehicle models are starting with 400 (400 - 400 = 0, 401 - 400 = 1, ...)

			XML_GetAttribute(modelNode, "name", vehicleModels[arrayIndex][VEHICLEMODEL_NAME], STRINGLENGTH_VEHICLENAME);
			XML_GetAttribute(modelNode, "type", vehicleModels[arrayIndex][VEHICLEMODEL_TYPE], STRINGLENGTH_VEHICLETYPE);

			XML_GetAttribute(modelNode, "fuelUsage", value);
			vehicleModels[arrayIndex][VEHICLEMODEL_FUELUSAGE] = floatstr(value);

			XML_GetAttribute(modelNode, "maxFuel", value);
			vehicleModels[arrayIndex][VEHICLEMODEL_MAXFUEL] = floatstr(value);

			new colorIndex = 0;
			new XMLNode:colorNode = XML_GetFirstChild(modelNode, "color");
			if (colorNode)
			{
				while (colorNode)
				{
					if (colorIndex >= MAX_VEHICLE_COLORS)
					{
						printf("Vehicle model ID %d reached maximum number of colors (%d)", modelID, MAX_VEHICLE_COLORS);
						break;
					}

					XML_GetAttribute(colorNode, "color1", value);
					vehicleColors[arrayIndex][colorIndex][0] = strval(value);

					XML_GetAttribute(colorNode, "color2", value);
					vehicleColors[arrayIndex][colorIndex][1] = strval(value);

					colorNode = XML_GetNextSibling(colorNode, "color");

					colorIndex++;
				}
			}
			else
			{
				printf("Missing color elements for vehicle model ID %d", modelID);
			}

			count++;
		}
		else
		{
			printf("Invalid vehicle model ID: %d", modelID);
		}

		modelNode = XML_GetNextSibling(modelNode, "model");
	}
	AdminPrint(playerID, COLOR_INFO, "  %d vehicle models loaded", count);
}