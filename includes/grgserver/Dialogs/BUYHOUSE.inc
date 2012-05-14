ShowDialog:BUYHOUSE(playerID, Float:price)
{
	FormatNew:string[100](LanguageString(playerID, 235), FormatMoney(price));
	CreateDialog(playerID, "BUYHOUSE", DIALOG_STYLE_MSGBOX, LanguageString(playerID, 236), string, LanguageString(playerID, 237), LanguageString(playerID, 165));
}

DialogResponse:BUYHOUSE(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new buildingID = PVar:playerID[DIALOGPROPERTYID];
		new Float:price = floatstr(GetMySQLValue("properties", "Price", "ID", val2str(buildingID)));
		if (price <= PVar:playerID[BANKMONEY])
		{
			TogglePlayerControllable(playerID, false);
			PlayAudioStreamForPlayer(playerID, "http://audio.grgserver.net/mission_complete2.ogg");
			MySQLQuery("SELECT * FROM `properties` LEFT JOIN `pickups` ON `properties`.`PickupID` = `pickups`.`ID` WHERE `properties`.`ID` = '%d'", buildingID);
			mysql_store_result();
			SetPlayerCameraPos(playerID, floatstr(GetMySQLField("CameraPosX")), floatstr(GetMySQLField("CameraPosY")), floatstr(GetMySQLField("CameraPosZ")));
			SetPlayerCameraLookAt(playerID, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")));
			mysql_free_result();
			GameTextForPlayer(playerID, LanguageString(playerID, 28), 8000, 1);
			SetMySQLValue("properties", "OwnerUserID", val2str(PVar:playerID[USERID]), "ID", val2str(buildingID));
			GivePlayerMoneyEx(playerID, MONEY_BANK, -price);
			ReloadPickup(strval(GetMySQLValue("properties", "PickupID", "ID", val2str(buildingID))));
			SetTimerEx("Timer_ScreenFader", 8000, false, "ddddddd", playerID, 0, 0, 0, 5, 0, FADE_PROPERTYBOUGHT_BLACK);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 29, price, PVar:playerID[BANKMONEY]);
		}
	}
}