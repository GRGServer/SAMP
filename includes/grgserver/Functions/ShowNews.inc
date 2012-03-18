ShowNews(playerID, lastID)
{
	MySQLQuery("SELECT * FROM `news` WHERE `ID` > '%d' ORDER BY `Date` DESC LIMIT %d", lastID, NEWS_MAXIMUM);// TODO: Use player language
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
		}
		Format:string("[%s] %s", FormatDate(GetMySQLField("Date"), false), string);
		SendClientMessage(playerID, COLOR_INFO, string);
	}
	mysql_free_result();
	PVar:playerID[LASTNEWSID] = lastID;
	SendClientMessageEx(playerID, COLOR_INFO, 135);
}