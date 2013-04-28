PCMD:addobject[MAPPER](playerID, params[], StringID:202("Add a new object"))
{
	new modelID;
	new filename[STRINGLENGTH_OBJECTFILENAME];
	if (!sscanf(params, "ds[" #STRINGLENGTH_OBJECTFILENAME "]", modelID, filename))
	{
		if (modelID >= 0 && modelID < sizeof(objectModels) && StrNotNull(objectModels[modelID]))
		{
			AddObject(playerID, modelID, filename);
			return COMMAND_OK;
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:427("Object not found!"));
			return COMMAND_ERROR;
		}
	}

	new modelName[100];
	if (sscanf(params, "s[100]s[" #STRINGLENGTH_OBJECTFILENAME "]", modelName, filename))
	{
		CmdUsageMsg(playerID, "addobject", "modelID/ModelName", "Filename");
		return COMMAND_USAGE;
	}

	new count;
	new objectList[2048];
	Foreach(currentModelID, objectModels)
	{
		if (strfind(objectModels[currentModelID], modelName, true) != -1)
		{
			if (strlen(objectList))
			{
				strcat(objectList, "\n");
			}
			Format:objectList("%s%d\t%s", objectList, currentModelID, objectModels[currentModelID]);
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
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:427("Object not found!"));
		return COMMAND_ERROR;
	}

	if (count > 1)
	{
		format(PVar:playerID[OBJEDITOR_FILENAME], PVAR_OBJEDITOR_FILENAME, "%s", filename);
		CreateDialog(playerID, "AddObject", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:202("Add a new object")), objectList, LanguageString(playerID, StringID:170("Create")), LanguageString(playerID, StringID:165("Cancel")));
	}
	else
	{
		AddObject(playerID, modelID, filename);
	}

	return COMMAND_OK;
}