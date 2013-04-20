PCMD:addproperty[MAPPER](playerID, params[], 95)
{
	new Float:price;
	if (sscanf(params, "f", price))
	{
		CmdUsageMsg(playerID, "addproperty", LanguageString(playerID, "298"));
		return COMMAND_USAGE;
	}
	PVar:playerID[ADDPROPERTY_PRICE] = price;
	ShowDialog:AddProperty_Type(playerID);
	return COMMAND_OK;
}