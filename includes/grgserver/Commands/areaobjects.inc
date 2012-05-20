PCMD:areaobjects[MAPPER](playerID, params[], 459)
{
	new Float:distance;
	if (sscanf(params, "f", distance))
	{
		CmdUsageMsg(playerID, "areaobjects", "Distance");
		return COMMAND_USAGE;
	}
	new objectsFound;
	MySQLQuery("SELECT `objects`.`ID`, `objects`.`PosX`, `objects`.`PosY`, `objects`.`PosZ`, `objectmodels`.`Name` FROM `objects` LEFT JOIN `objectmodels` ON `objectmodels`.`ID` = `objects`.`ModelID`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		if (GetPlayerDistanceFromPoint(playerID, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ"))) <= distance)
		{
			Format:clientMessageString("%s: %s", GetMySQLField("ID"), GetMySQLField("Name"));
			SendClientMessage(playerID, COLOR_INFO, clientMessageString);
			objectsFound++;
		}
	}
	SendClientMessageEx(playerID, COLOR_INFO, 458, objectsFound);
	return COMMAND_OK;
}