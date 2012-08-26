/**
 * <summary>
 *	Spawn a player at the saved position
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 */

Timer:SpawnPlayer(playerID)
{
	SpawnPlayer(playerID);
	MySQLQuery("SELECT * FROM `users` WHERE `id` = '%d'", PVar:playerID[USERID]);
	mysql_store_result();
	SetPlayerPosEx(playerID, floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ")), strval(GetMySQLField("interior")));
	SetPlayerFacingAngle(playerID, floatstr(GetMySQLField("angle")));
	mysql_free_result();
}