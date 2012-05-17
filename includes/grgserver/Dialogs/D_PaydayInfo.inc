ShowDialog:PaydayInfo(playerID)
{
	new difference = GetOnlineTime(playerID) - PVar:playerID[LASTPAYDAY];
	MySQLQuery("SELECT * FROM `moneytransactions` WHERE `UserID` = '%d' AND `Type` = '%s'", PVar:playerID[USERID], CASHTRANS_PAYDAY);
	mysql_store_result();
	new Float:amount = floatstr(GetMySQLField("Amount"));
	mysql_free_result();
	new string[256];
	AddLine:string(LanguageString(playerID, 420), FormatMoney(amount));
	AddLine:string(LanguageString(playerID, 421), FormatTime(difference));
	AddLine:string(LanguageString(playerID, 422), FormatTime(PAYDAY_INTERVAL - difference));
	CreateDialog(playerID, "PaydayInfo", DIALOG_STYLE_MSGBOX, LanguageString(playerID, 423), string, "OK", "");
}

DialogResponse:PaydayInfo(playerID, response, listItem, inputText[])
{
	// Nothing to do here
}