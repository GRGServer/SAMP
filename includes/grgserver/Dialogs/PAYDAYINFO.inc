ShowDialog:PAYDAYINFO(playerID)
{
	new difference = GetOnlineTime(playerID) - PVar:playerID[LASTPAYDAY];
	MySQLQuery("SELECT * FROM `moneytransactions` WHERE `UserID` = '%d' AND `Type` = '%s'", PVar:playerID[USERID], CASHTRANS_PAYDAY);
	mysql_store_result();
	new Float:amount = floatstr(GetMySQLField("Amount"));
	mysql_free_result();
	FormatNew:string[160]("Letztes Nettoeinkommen:\t\t\t$%s", FormatMoney(amount));
	Format:string("%s\n\nVergangene Zeit seit dem letzten Zahltag:\t%s", string, FormatTime(difference));
	Format:string("%s\n\nZeit bis zum nächsten Zahltag:\t\t\t%s", string, FormatTime(PAYDAY_INTERVAL - difference));
	CreateDialog(playerID, "PAYDAYINFO", DIALOG_STYLE_MSGBOX, "Informationen über den Zahltag", string, "OK", "");
}