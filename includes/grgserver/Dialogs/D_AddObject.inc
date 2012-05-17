// Dialog is created at another location

DialogResponse:AddObject(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new modelID;
		new name[STRINGLENGTH_OBJECTNAME];
		if (!sscanf(inputText, "p:ds", modelID, name))
		{
			if (modelID)
			{
				AddObject(playerID, modelID);
			}
		}
	}
}