PCMD:addhotelroom[MAPPER](playerID, params[], 323)
{
	new validHotel;
	if (PVar:playerID[CURRENTPROPERTYID])
	{
		MySQLQuery("SELECT * FROM `properties` LEFT JOIN `pickups` ON `properties`.`PickupID` = `pickups`.`ID` WHERE `properties`.`ID` = '%d'", PVar:playerID[CURRENTPROPERTYID]);
		mysql_store_result();
		validHotel = !strcmp(GetMySQLField("Type"), "HOTEL", true);
		mysql_free_result();
	}
	if (!validHotel)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 324);
		return COMMAND_ERROR;
	}
	new Float:price;
	if (sscanf(params, "f", price))
	{
		CmdUsageMsg(playerID, "addhotelroom", LanguageString(playerID, 298));
		return COMMAND_USAGE;
	}
	MySQLQuery("SELECT IFNULL(MAX(RoomID), 0) AS `HighestRoomID` FROM `hotelrooms` WHERE `PropertyID` = '%d'", PVar:playerID[CURRENTPROPERTYID]);
	mysql_store_result();
	new roomID = strval(GetMySQLField("HighestRoomID")) + 1;
	mysql_free_result();
	MySQLQuery("INSERT INTO `hotelrooms` (`PropertyID`, `RoomID`, `Price`) VALUES('%d', '%d', '%f')", PVar:playerID[CURRENTPROPERTYID], roomID, price);
	SendClientMessageEx(playerID, COLOR_INFO, 325, roomID);
	return COMMAND_OK;
}