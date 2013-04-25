ShowNews(playerID, lastID)
{
	MySQLQuery("SELECT `id`, `date`, LEFT(`text_%s`, 255) AS `text` FROM `news` WHERE `id` > '%d' ORDER BY `date` DESC LIMIT %d", GetLanguageName(PVar:playerID[LANGUAGE]), lastID, NEWS_MAXIMUM);
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new id = strval(GetMySQLField("id"));
		if (id > lastID)
		{
			lastID = id;
		}
		FormatNew:string[NEWS_LINELENGTH + 30](GetMySQLField("text"));
		if (strlen(string) > NEWS_LINELENGTH + 3)
		{
			strmid(string, string, 0, NEWS_LINELENGTH, sizeof(string));
			Format:string("%s...", string);
		}
		Format:string("[%s] %s", FormatDate(GetMySQLField("date"), false), string);
		SendClientMessage(playerID, COLOR_INFO, string);
	}
	mysql_free_result();
	PVar:playerID[LASTNEWSID] = lastID;
	SendClientMessageEx(playerID, COLOR_INFO, StringID:135("See all news on grgserver.net."));
}