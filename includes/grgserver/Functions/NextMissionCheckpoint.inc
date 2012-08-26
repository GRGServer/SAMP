/**
 * <summary>
 *	Show the next checkpoint for the current mission.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 *
 * <param name="reuseCurrent">
 *	If set to true, do not search for the next checkpoint. Instead use the current checkpoint again.
 * </param>
 *
 * <remarks>
 *	OnCheckpointMissionFinished gets triggered as soon as there are no more checkpoints in the current mission.
 * </remarks>
 */

NextMissionCheckpoint(playerID, reuseCurrent = false)
{
	if (reuseCurrent)
	{
		MySQLQuery("SELECT * FROM `missioncheckpoints` WHERE `missionId` = '%d' AND `checkpointId` = '%d'", PVar:playerID[CPMISSION_ID], PVar:playerID[CPMISSION_CHECKPOINTID]);
	}
	else
	{
		MySQLQuery("SELECT * FROM `missioncheckpoints` WHERE `missionId` = '%d' AND `checkpointId` > '%d' LIMIT 1", PVar:playerID[CPMISSION_ID], PVar:playerID[CPMISSION_CHECKPOINTID]);
	}
	mysql_store_result();
	PVar:playerID[CPMISSION_CHECKPOINTID] = strval(GetMySQLField("checkpointId"));
	new rows = mysql_num_rows();
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:nextPosX;
	new Float:nextPosY;
	new Float:nextPosZ;
	if (rows)
	{
		posX = floatstr(GetMySQLField("posX"));
		posY = floatstr(GetMySQLField("posY"));
		posZ = floatstr(GetMySQLField("posZ"));
	}
	mysql_free_result();
	if (rows)
	{
		MySQLQuery("SELECT * FROM `missioncheckpoints` WHERE `missionId` = '%d' AND `checkpointId` > '%d' LIMIT 1", PVar:playerID[CPMISSION_ID], PVar:playerID[CPMISSION_CHECKPOINTID]);
		mysql_store_result();
		nextPosX = floatstr(GetMySQLField("posX"));
		nextPosY = floatstr(GetMySQLField("posY"));
		nextPosZ = floatstr(GetMySQLField("posZ"));
		mysql_free_result();
		SetPlayerRaceCheckpointEx(playerID, CHECKPOINT_MISSION, posX, posY, posZ, nextPosX, nextPosY, nextPosZ, 5);
	}
	else
	{
		OnCheckpointMissionFinished(playerID);
	}
}