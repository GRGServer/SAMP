ShowDialog:PaydayInfo(playerID)
{
	new difference = GetOnlineTime(playerID) - PVar:playerID[LASTPAYDAY];
	MySQLQuery("SELECT `amount` FROM `moneytransactions` WHERE `userId` = '%d' AND `type` = '%s'", PVar:playerID[USERID], CASHTRANS_PAYDAY);
	mysql_store_result();
	new Float:amount = floatstr(GetMySQLField("amount"));
	mysql_free_result();
	new string[256];
	AddLine:string(LanguageString(playerID, StringID:420("")), FormatMoney(amount));
	AddLine:string(LanguageString(playerID, StringID:421("")), FormatTime(difference));
	AddLine:string(LanguageString(playerID, StringID:422("")), FormatTime(PAYDAY_INTERVAL - difference));
	CreateDialog(playerID, "PaydayInfo", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:423("")), string, "OK", "");
}

DialogResponse:PaydayInfo(playerID, response, listItem, inputText[])
{
	// Nothing to do here
}