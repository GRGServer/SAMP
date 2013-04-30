CreateJob(playerID, jobID, modelID)
{
	MySQLQuery("INSERT INTO `missions` (`jobId`, `data`, `type`,`creatorUserId`, `creationTime`) VALUES ('%d', '%d','GetOrderedVehicle', '%d', NOW())", jobID, modelID, PVar:playerID[USERID]);
	return mysql_insert_id();
}