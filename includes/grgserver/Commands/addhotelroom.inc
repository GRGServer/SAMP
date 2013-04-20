/**
 * <summary>
 *	Add a room to the current property.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which called the command.
 * </param>
 *
 * <param name="params">
 *	<title>The parameters passed to this command.</title>
 *	<item>The price for the room</item>
 * </param>
 *
 * <returns>
 *	<item>COMMAND_ERROR</item>
 *	<item>COMMAND_OK</item>
 *	<item>COMMAND_USAGE</item>
 * </returns>
 */

PCMD:addhotelroom[MAPPER](playerID, params[], 323)
{
	new validHotel;
	if (PVar:playerID[CURRENTPROPERTYID])
	{
		MySQLQuery("SELECT * FROM `properties` LEFT JOIN `pickups` ON `properties`.`pickupId` = `pickups`.`id` WHERE `properties`.`id` = '%d'", PVar:playerID[CURRENTPROPERTYID]);
		mysql_store_result();
		validHotel = !strcmp(GetMySQLField("type"), "HOTEL", true);
		mysql_free_result();
	}
	if (!validHotel)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, "324");
		return COMMAND_ERROR;
	}
	new Float:price;
	if (sscanf(params, "f", price))
	{
		CmdUsageMsg(playerID, "addhotelroom", LanguageString(playerID, "298"));
		return COMMAND_USAGE;
	}
	MySQLQuery("SELECT IFNULL(MAX(roomId), 0) AS `highestRoomId` FROM `hotelrooms` WHERE `propertyId` = '%d'", PVar:playerID[CURRENTPROPERTYID]);
	mysql_store_result();
	new roomID = strval(GetMySQLField("highestRoomId")) + 1;
	mysql_free_result();
	MySQLQuery("INSERT INTO `hotelrooms` (`propertyId`, `roomId`, `price`) VALUES('%d', '%d', '%f')", PVar:playerID[CURRENTPROPERTYID], roomID, price);
	SendClientMessageEx(playerID, COLOR_INFO, "325", roomID);
	return COMMAND_OK;
}