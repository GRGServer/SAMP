ShowDialog:NaviTarget_HouseName(playerID)
{
	CreateDialog(playerID, "NaviTarget_HouseName", DIALOG_STYLE_INPUT, LanguageString(playerID, 417), LanguageString(playerID, 418), "OK", LanguageString(playerID, 171));
}

DialogResponse:NaviTarget_HouseName(playerID, response, listItem, inputText[])
{
	if (response)
	{
		MySQLQuery("SELECT * FROM `properties` LEFT JOIN `pickups` ON `properties`.`PickupID` = `pickups`.`ID` WHERE `Name` LIKE '%%%s%%'", MySQLEscapeString(inputText));
		mysql_store_result();
		new rows = mysql_num_rows();
		if (rows)
		{
			if (rows == 1)
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
				ShowDialog:NaviTarget_HouseList(playerID, inputText);
			}
		}
		mysql_free_result();
	}
	else
	{
		ShowDialog:NaviTarget(playerID);
	}
}