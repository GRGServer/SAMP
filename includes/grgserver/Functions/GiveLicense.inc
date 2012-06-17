/**
 * <summary>
 *	Give or revoke a license
 * </summary>
 *
 * <param name="giverPlayerID">
 *	The ID of the player wich gives the license
 * </param>
 *
 * <param name="playerID">
 *	The ID of the player you want to give or revoke the license
 * </param>
 *
 * <param name="type">
 *	The license type string
 * </param>
 *
 * <param name="newState">
 *	<title>The new state</title>
 *	<item name="true">Give the license</item>
 *	<item name="false">Revoke the license</item>
 * </param>
 *
 * <returns>
 *	<item>true if successful</item>
 *	<item>false if failed</item>
 * </returns>
 *
 * <remarks>
 *	<title>This function returns false if you try to...</title>
 *	<item>...give a license to a player which already owns the license</item>
 *	<item>...revoke a license from a player which does not own the license</item>
 * </remarks>
 */

GiveLicense(giverPlayerID, playerID, type[], newState)
{
	new currentState = HasLicense(playerID, type);
	if (newState && !currentState)
	{
		MySQLQuery("INSERT INTO `licenses` (`giverUserId`, `userId`, `type`, `date`) VALUES('%d', '%d', '%s', NOW())", PVar:giverPlayerID[USERID], PVar:playerID[USERID], MySQLEscapeString(type));
		return true;
	}
	if (!newState && currentState)
	{
		MySQLQuery("DELETE FROM `licenses` WHERE `userId` = '%d' AND `type` = '%s'", PVar:playerID[USERID], MySQLEscapeString(type));
		return true;
	}
	return false;
}