WriteChatToDatabase(playerID, text[])
{
	MySQLQuery("INSERT INTO `chatlog` (`UserID`, `Time`, `Text`) VALUES('%d', NOW(), '%s')", GetPVar:playerID[USERID], MySQLEscapeString(text));
}