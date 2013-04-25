PCMD:nocamproperty[MAPPER](playerID, params[], StringID:350("Teleport you to the next property without camera position"))
{
	MySQLQuery("SELECT * FROM `properties` LEFT JOIN `pickups` ON `properties`.`pickupId` = `pickups`.`id` WHERE `cameraPosX` = '0' AND `cameraPosY` = '0' AND `cameraPosZ` = '0'");
	mysql_store_result();
	new rows = mysql_num_rows();
	if (rows)
	{
		SetPlayerPos(playerID, floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ")));
		SendClientMessageEx(playerID, COLOR_INFO, StringID:351("You got teleported to the next property (%s). There are %d properties without a camera position."), GetMySQLField("name"), rows);
	}
	mysql_free_result();
	if (rows)
	{
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:352("There are no more properties without camera position!"));
		return COMMAND_ERROR;
	}
}