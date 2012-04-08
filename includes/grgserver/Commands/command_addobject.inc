PCMD:addobject[MAPPER](playerID, params[], 202)
{
	new modelID;
	if (sscanf(params, "d", modelID))
	{
		new modelName[100];
		if (sscanf(params, "s", modelName))
		{
			CmdUsageMsg(playerID, "addobject", "modelID/ModelName");
			return COMMAND_USAGE;
		}
		MySQLQuery("SELECT * FROM `objectmodels` WHERE `Name` LIKE '%s' LIMIT 50", str_replace("*", "%%", MySQLEscapeString(modelName)));
		mysql_store_result();
		if (!mysql_num_rows() && strfind(modelName, "*") == -1)
		{
			mysql_free_result();
			MySQLQuery("SELECT * FROM `objectmodels` WHERE `Name` LIKE '%%%s%%' LIMIT 50", MySQLEscapeString(modelName));
			mysql_store_result();
		}
		if (mysql_num_rows() > 1)
		{
			new objectList[2048];
			while (FetchMySQLRow())
			{
				if (strlen(objectList))
				{
					strcat(objectList, "\n");
				}
				Format:objectList("%s%s:%s", objectList, GetMySQLField("ID"), GetMySQLField("Name"));
			}
			ShowPlayerDialog(playerID, DIALOG_ADDOBJECT, DIALOG_STYLE_LIST, LanguageString(playerID, 202), objectList, LanguageString(playerID, 170), LanguageString(playerID, 165));
			modelID = -1;
		}
		else
		{
			modelID = strval(GetMySQLField("ID"));
		}
		mysql_free_result();
	}
	if (modelID)
	{
		if (modelID == -1)
		{
			return COMMAND_OK;
		}
		AddObject(playerID, modelID);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_ERROR;
	}
}