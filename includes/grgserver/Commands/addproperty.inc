PCMD:addproperty[MAPPER](playerID, params[], StringID:95("Create a property"))
{
	new Float:price;
	if (sscanf(params, "f", price))
	{
		CmdUsageMsg(playerID, "addproperty", LanguageString(playerID, StringID:298("Price")));
		return COMMAND_USAGE;
	}
	PVar:playerID[ADDPROPERTY_PRICE] = price;
	ShowDialog:AddProperty_Type(playerID);
	return COMMAND_OK;
}