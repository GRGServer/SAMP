ShowDialog:NaviTarget_HouseList(playerID, searchString[])
{
	new list[2048];
	MySQLQuery("SELECT * FROM `properties` LEFT JOIN `pickups` ON `properties`.`PickupID` = `pickups`.`ID` WHERE `Name` LIKE '%%%s%%'", MySQLEscapeString(searchString));
	mysql_store_result();
	while (FetchMySQLRow())
	{
		AddLine(list, GetMySQLField("Name"));
	}
	mysql_free_result();
	CreateDialog(playerID, "NaviTarget_HouseList", DIALOG_STYLE_LIST, LanguageString(playerID, 419), list, "OK", LanguageString(playerID, 171));
}

DialogResponse:NaviTarget_HouseList(playerID, response, listItem, inputText[])
{
	if (response)
	{
		MySQLQuery("SELECT * FROM `properties` LEFT JOIN `pickups` ON `properties`.`PickupID` = `pickups`.`ID` WHERE `Name` = '%s'", MySQLEscapeString(inputText));
		mysql_store_result();
		if (mysql_num_rows())
		{
			if (CalculateRoute(playerID, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ"))))
			{
				SendClientMessageEx(playerID, COLOR_INFO, 414);
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 415);
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 343);
		}
		mysql_free_result();
	}
	else
	{
		ShowDialog:NaviTarget_HouseName(playerID);
	}
}