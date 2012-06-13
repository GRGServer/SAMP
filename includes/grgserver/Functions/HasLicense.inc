/**
 * <summary>
 *	Check if a players owns a license.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player you want to check
 * </param>
 *
 * <param name="type">
 *	The license type string
 * </param>
 *
 * <returns>
 *	<item>true if the player owns the license</item>
 *	<item>false if the player does not own the license</item>
 * </returns>
 */

HasLicense(playerID, type[])
{
	MySQLQuery("SELECT `userId` FROM `licenses` WHERE `userId` = '%d' AND `type` = '%s'", PVar:playerID[USERID], MySQLEscapeString(type));
	mysql_store_result();
	new rows = mysql_num_rows();
	mysql_free_result();
	return rows;
}