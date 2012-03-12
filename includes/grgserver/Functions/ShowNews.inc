ShowNews(playerID, lastID)
{
	new truncated;
	MySQLQuery("SELECT * FROM `news` WHERE `ID` > '%d' ORDER BY `Date` DESC LIMIT %d", lastID, NEWS_MAXIMUM);
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new id = strval(GetMySQLField("ID"));
		if (id > lastID)
		{
			lastID = id;
		}
		FormatNew:string[NEWS_LINELENGTH + 30](GetMySQLField("Text"));
		if (strlen(string) > NEWS_LINELENGTH + 3)
		{
			strmid(string, string, 0, NEWS_LINELENGTH, sizeof(string));
			Format:string("%s...", string);
			truncated = true;
		}
		Format:string("[%s] %s", FormatDate(GetMySQLField("Date"), false), string);
		SendClientMessage(playerID, COLOR_INFO, string);
	}
	mysql_free_result();
	PVar:playerID[LASTNEWSID] = lastID;
	if (truncated)
	{
		SendClientMessage(playerID, COLOR_INFO, "Hinweis: Einige News wurden aufgrund der Länge nicht vollständig angezeigt!");
		SendClientMessage(playerID, COLOR_INFO, "Sehe dir die vollständigen News auf grgserver.net an.");
	}
}