/**
 * <summary>
 *	Get the amount of bank money of the given player.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player you want to get the amount of money from
 * </param>
 *
 * <returns>
 *	The amount of money
 * </returns>
 */

Float:GetBankMoney(playerID)
{
	MySQLQuery("SELECT `bankaccounts`.`money` FROM `bankaccounts` LEFT JOIN `users` ON `users`.`bankAccountId` = `bankaccounts`.`id` WHERE `users`.`id` = '%d'", PVar:playerID[USERID]);
	mysql_store_result();
	new Float:bankMoney = floatstr(GetMySQLField("money"));
	mysql_free_result();
	return bankMoney;
}