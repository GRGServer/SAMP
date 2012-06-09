PCMD:areaobjects[MAPPER](playerID, params[], 459)
{
	new Float:distance;
	if (sscanf(params, "f", distance))
	{
		CmdUsageMsg(playerID, "areaobjects", "Distance");
		return COMMAND_USAGE;
	}
	new objectsFound;
	MySQLQuery("SELECT `objects`.`id`, `objects`.`posX`, `objects`.`posY`, `objects`.`posZ`, `objectmodels`.`name` FROM `objects` LEFT JOIN `objectmodels` ON `objectmodels`.`id` = `objects`.`modelId`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		if (GetPlayerDistanceFromPoint(playerID, floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ"))) <= distance)
		{
			Format:clientMessageString("%s: %s", GetMySQLField("id"), GetMySQLField("name"));
			SendClientMessage(playerID, COLOR_INFO, clientMessageString);
			objectsFound++;
		}
	}
	SendClientMessageEx(playerID, COLOR_INFO, 458, objectsFound);
	return COMMAND_OK;
}