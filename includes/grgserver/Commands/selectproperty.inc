PCMD:selectproperty[MAPPER](playerID, params[], StringID:335(""))
{
	if (PVar:playerID[CURRENTPROPERTYID])
	{
		PVar:playerID[SELECTEDPROPERTYID] = PVar:playerID[CURRENTPROPERTYID];
		SendClientMessageEx(playerID, COLOR_INFO, StringID:142(""), GetMySQLValue("properties", "name", "id", val2str(PVar:playerID[CURRENTPROPERTYID])));
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:61(""));
		return COMMAND_ERROR;
	}
}