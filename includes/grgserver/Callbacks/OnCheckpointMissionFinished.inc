/**
 * <summary>
 *	This callback gets triggered as soon as the player has finished a checkpoint mission (Entered the last checkpoint).
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 */

OnCheckpointMissionFinished(playerID)
{
	new missionName[STRINGLENGTH_CPMISSION];
	strcat(missionName, GetCheckpointMissionNameByID(PVar:playerID[CPMISSION_ID]));
	if (strfind(missionName, "DrivingSchool", true, 0) == 0)// Check if the mission was a driving school mission
	{
		new separator1 = strfind(missionName, "_");
		new separator2 = strfind(missionName, "_", false, separator1 + 1);
		if (separator1 != -1 && separator2 != -1)
		{
			new drivingSchoolType[STRINGLENGTH_CPMISSION];
			strmid(drivingSchoolType, missionName, separator1 + 1, separator2);
			MySQLQuery("INSERT INTO `licenses` (`giverUserId`, `userId`, `type`, `date`) VALUES('0', '%d', '%s', NOW())", PVar:playerID[USERID], MySQLEscapeString(drivingSchoolType));
			StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_DRVSCHOOL_END1, 0);
		}
	}
	else
	{
		PVar:playerID[CPMISSION_ID] = 0;
	}
}