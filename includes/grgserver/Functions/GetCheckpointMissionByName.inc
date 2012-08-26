/**
 * <summary>
 *	Get the ID of a checkpoint mission.
 * </summary>
 *
 * <param name="name">
 *	The mission name
 * </param>
 *
 * <param name="randomLike">
 *	Use LIKE to search in the database and return a random ID from the result
 * </param>
 *
 * <returns>
 *	The ID of the mission or 0 if the mission does not exist
 * </returns>
 */

GetCheckpointMissionByName(name[], randomLike = false)
{
	new missionID;
	if (randomLike)
	{
		MySQLQuery("SELECT `id` FROM `missioncheckpointgroups` WHERE `name` LIKE '%s' ORDER BY RAND() LIMIT 1", MySQLEscapeString(name));
	}
	else
	{
		MySQLQuery("SELECT `id` FROM `missioncheckpointgroups` WHERE `name` = '%s'", MySQLEscapeString(name));
	}
	mysql_store_result();
	if (mysql_num_rows())
	{
		missionID = strval(GetMySQLField("id"));
	}
	mysql_free_result();
	return missionID;
}