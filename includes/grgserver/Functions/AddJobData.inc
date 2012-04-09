AddJobData(missionID, name[], value[])
{
	MySQLQuery("INSERT INTO `missiondata` (`MissionID`, `Name`, `Value`) VALUES ('%d', '%s', '%s')", missionID, MySQLEscapeString(name), MySQLEscapeString(value));
}