PCMD:nocamproperty[MAPPER](playerID, params[], StringID:350(""))
{
	MySQLQuery("SELECT * FROM `properties` LEFT JOIN `pickups` ON `properties`.`pickupId` = `pickups`.`id` WHERE `cameraPosX` = '0' AND `cameraPosY` = '0' AND `cameraPosZ` = '0'");
	mysql_store_result();
	new rows = mysql_num_rows();
	if (rows)
	{
		SetPlayerPos(playerID, floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ")));
		SendClientMessageEx(playerID, COLOR_INFO, StringID:351(""), GetMySQLField("name"), rows);
	}
	mysql_free_result();
	if (rows)
	{
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:352(""));
		return COMMAND_ERROR;
	}
}