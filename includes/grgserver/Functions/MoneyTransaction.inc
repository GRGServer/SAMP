MoneyTransaction(playerID, type[], from, to, Float:amount)
{
	MySQLQuery("INSERT INTO `moneytransactions` (`userId`, `date`, `type`, `from`, `to`, `amount`) VALUES('%d', NOW(), '%s', '%d', '%d', '%f')", PVar:playerID[USERID], type, from, to, amount);
	return mysql_insert_id();
}