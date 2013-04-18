PCMD:addobject[MAPPER](playerID, params[], 202)
{
	new modelID;
	new filename[STRINGLENGTH_OBJECTFILENAME];
	if (!sscanf(params, "ds", modelID, filename))
	{
		if (modelID >= 0 && modelID < sizeof(objectModels) && StrNotNull(objectModels[modelID]))
		{
			AddObject(playerID, modelID, filename);
			return COMMAND_OK;
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 427);
			return COMMAND_ERROR;
		}
	}

	new modelName[100];
	if (sscanf(params, "ss", modelName, filename))
	{
		CmdUsageMsg(playerID, "addobject", "modelID/ModelName", "Filename");
		return COMMAND_USAGE;
	}

	new count;
	new objectList[2048];
	Foreach(currentModelID, objectModels)
	{
		if (strfind(objectModels[currentModelID], modelName, false) != -1)
		{
			if (strlen(objectList))
			{
				strcat(objectList, "\n");
			}
			Format:objectList("%s%s:%s", objectList, currentModelID, objectModels[currentModelID]);
			modelID = currentModelID;

			count++;
			if (count >= 50)// Only show max 50 objects
			{
				break;
			}
		}
	}

	if (!count)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 427);
		return COMMAND_ERROR;
	}

	if (count > 1)
	{
		format(PVar:playerID[OBJEDITOR_FILENAME], PVAR_OBJEDITOR_FILENAME, "%s", filename);
		CreateDialog(playerID, "AddObject", DIALOG_STYLE_LIST, LanguageString(playerID, 202), objectList, LanguageString(playerID, 170), LanguageString(playerID, 165));
	}
	else
	{
		AddObject(playerID, modelID, filename);
	}

	return COMMAND_OK;
}