CreateJob(playerID, jobID)
{
	MySQLQuery("INSERT INTO `missions` (`JobID`, `CreatorUserID`, `CreationTime`) VALUES ('%d', '%d', NOW())", jobID, PVar:playerID[USERID]);
	return mysql_insert_id();
}