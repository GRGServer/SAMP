CreateJob(playerID, jobID)
{
	MySQLQuery("INSERT INTO `missions` (`jobId`, `creatorUserId`, `creationTime`) VALUES ('%d', '%d', NOW())", jobID, PVar:playerID[USERID]);
	return mysql_insert_id();
}