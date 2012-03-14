MoneyTransaction(playerID, type[], from, to, Float:amount)
{
	MySQLQuery("INSERT INTO `moneytransactions` (`UserID`, `Date`, `Type`, `From`, `To`, `Amount`) VALUES('%d', NOW(), '%s', '%d', '%d', '%f')", PVar:playerID[USERID], type, from, to, amount);
	return mysql_insert_id();
}