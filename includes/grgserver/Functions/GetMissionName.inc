GetMissionName(missionID)
{
	new type[100];
	MySQLQuery("SELECT * FROM `missiondata` WHERE `missionId` = '%d' AND `name` = 'Type'", missionID);
	mysql_store_result();
	strcat(type, GetMySQLField("value"));
	mysql_free_result();
	if (IsStr(type, "GetOrderedVehicle"))
	{
		return 586;
	}
	return 0;
}