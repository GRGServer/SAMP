AddJobData(missionID, name[], value[])
{
	MySQLQuery("INSERT INTO `missiondata` (`missionId`, `name`, `value`) VALUES ('%d', '%s', '%s')", missionID, MySQLEscapeString(name), MySQLEscapeString(value));
}