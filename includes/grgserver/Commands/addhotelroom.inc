PCMD:addhotelroom[MAPPER](playerID, params[], 323)
{
	new validHotel;
	if (PVar:playerID[CURRENTBUILDINGID])
	{
		MySQLQuery("SELECT * FROM `buildings` LEFT JOIN `pickups` ON `buildings`.`PickupID` = `pickups`.`ID` WHERE `buildings`.`ID` = '%d'", PVar:playerID[CURRENTBUILDINGID]);
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
	MySQLQuery("SELECT IFNULL(MAX(RoomID), 0) AS `HighestRoomID` FROM `hotelrooms` WHERE `BuildingID` = '%d'", PVar:playerID[CURRENTBUILDINGID]);
	mysql_store_result();
	new roomID = strval(GetMySQLField("HighestRoomID")) + 1;
	mysql_free_result();
	MySQLQuery("INSERT INTO `hotelrooms` (`BuildingID`, `RoomID`, `Price`) VALUES('%d', '%d', '%f')", PVar:playerID[CURRENTBUILDINGID], roomID, price);
	SendClientMessageEx(playerID, COLOR_INFO, 325, roomID);
	return COMMAND_OK;
}