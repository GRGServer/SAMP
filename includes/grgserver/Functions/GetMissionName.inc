GetMissionName(missionID)
{
	new type[100];
	new languageStringName[100];
	languageStringName = "0";
	MySQLQuery("SELECT * FROM `missiondata` WHERE `missionId` = '%d' AND `name` = 'Type'", missionID);
	mysql_store_result();
	strcat(type, GetMySQLField("value"));
	mysql_free_result();
	if (IsStr(type, "GetOrderedVehicle"))
	{
		languageStringName = "586";
	}
	return languageStringName;
}