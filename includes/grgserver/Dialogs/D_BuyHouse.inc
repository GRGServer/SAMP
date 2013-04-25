ShowDialog:BuyHouse(playerID, Float:price)
{
	FormatNew:title[64](LanguageString(playerID, StringID:236("Buy house - %s")), GetMySQLValue("properties", "name", "id", val2str(PVar:playerID[DIALOGPROPERTYID])));
	FormatNew:string[100](LanguageString(playerID, StringID:235("This house can be bought.\n\nPrice: $%s")), FormatMoney(price));
	CreateDialog(playerID, "BuyHouse", DIALOG_STYLE_MSGBOX, title, string, LanguageString(playerID, StringID:237("Buy")), LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:BuyHouse(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new buildingID = PVar:playerID[DIALOGPROPERTYID];
		new Float:price = floatstr(GetMySQLValue("properties", "price", "id", val2str(buildingID)));
		new Float:bankMoney = GetBankMoney(playerID);
		if (price <= bankMoney)
		{
			TogglePlayerControllable(playerID, false);
			PlayAudio(playerID, "mission_complete2.ogg");
			MySQLQuery("SELECT * FROM `properties` LEFT JOIN `pickups` ON `properties`.`pickupId` = `pickups`.`id` WHERE `properties`.`id` = '%d'", buildingID);
			mysql_store_result();
			SetPlayerCameraPos(playerID, floatstr(GetMySQLField("cameraPosX")), floatstr(GetMySQLField("cameraPosY")), floatstr(GetMySQLField("cameraPosZ")));
			SetPlayerCameraLookAt(playerID, floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ")));
			mysql_free_result();
			GameTextForPlayer(playerID, LanguageString(playerID, StringID:28("Property bought")), 8000, 1);
			MySQLQuery("UPDATE `properties` SET `ownerUserId` = '%d' WHERE `id` = '%d'", PVar:playerID[USERID], buildingID);
			SetPlayerMoney(playerID, MONEY_BANK, -price, true);
			ReloadPickup(strval(GetMySQLValue("properties", "pickupId", "id", val2str(buildingID))));
			SetTimerEx("Timer_ScreenFader", 8000, false, "ddddddd", playerID, 0, 0, 0, 5, 0, FADE_PROPERTYBOUGHT, 0);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:29("Camera position saved"), price, bankMoney);
		}
	}
}