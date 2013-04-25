PCMD:selectproperty[MAPPER](playerID, params[], StringID:335("Select a property to set various properties like the 'Property bought' camera position"))
{
	if (PVar:playerID[CURRENTPROPERTYID])
	{
		PVar:playerID[SELECTEDPROPERTYID] = PVar:playerID[CURRENTPROPERTYID];
		SendClientMessageEx(playerID, COLOR_INFO, StringID:142("Property '%s' selected"), GetMySQLValue("properties", "name", "id", val2str(PVar:playerID[CURRENTPROPERTYID])));
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:61("You are not in a building!"));
		return COMMAND_ERROR;
	}
}