/**
 * <summary>
 *	Get the name of a checkpoint mission ID.
 * </summary>
 *
 * <param name="ID">
 *	The mission ID
 * </param>
 *
 * <returns>
 *	The name of the mission or an empty string if the mission does not exist
 * </returns>
 */

GetCheckpointMissionNameByID(missionID)
{
	new name[STRINGLENGTH_CPMISSION];
	MySQLQuery("SELECT `name` FROM `missioncheckpointgroups` WHERE `id` = '%d'", missionID);
	mysql_store_result();
	if (mysql_num_rows())
	{
		strcat(name, GetMySQLField("name"));
	}
	mysql_free_result();
	return name;
}