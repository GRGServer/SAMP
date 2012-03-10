WriteChatToDatabase(playerID, text[])
{
	MySQLQuery("INSERT INTO `chatlog` (`UserID`, `Time`, `Text`) VALUES('%d', NOW(), '%s')", PVar:playerID[USERID], MySQLEscapeString(text));
}