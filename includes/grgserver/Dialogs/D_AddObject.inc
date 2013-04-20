// Dialog is created at another location

DialogResponse:AddObject(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new modelID;
		new name[STRINGLENGTH_OBJECTMODELNAME];
		if (!sscanf(inputText, "p<:>ds[" #STRINGLENGTH_OBJECTMODELNAME "]", modelID, name))
		{
			if (modelID)
			{
				AddObject(playerID, modelID, PVar:playerID[OBJEDITOR_FILENAME]);
			}
		}
	}
}