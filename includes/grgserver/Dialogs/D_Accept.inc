ShowDialog:Accept(playerID)
{
	new missionList[2048];
	MySQLQuery("SELECT * FROM `missions` WHERE `missionjobId` = '%d' AND `acceptUserId` = '0' ORDER BY `id` ASC", PVar:playerID[JOBID]);
	mysql_store_result();
	printf("ID: %d", GetMySQLField("id"));
	while (FetchMySQLRow())
	{
		if (strlen(missionList))
		{
			Format:missionList("%s\n", missionList);
		}
		Format:missionList("%s%s: %s", missionList, GetMySQLField("id"), LanguageString(playerID, GetMissionName(strval(GetMySQLField("id")))));
	}
	mysql_free_result();
	if (strlen(missionList))
	{
		CreateDialog(playerID, "Accept", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:163("Accept order")), missionList, LanguageString(playerID, StringID:164("Accept")), LanguageString(playerID, StringID:165("Cancel")));
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:134("There are currently no orders available for your job!"));
	}
}

DialogResponse:Accept(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new missionID;
		new text[100];
		new value;
		sscanf(inputText, "p<:>ds[100]", missionID, text);
		if (strval(GetMySQLValue("missions", "acceptUserId", "id", val2str(missionID))))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:12("This job has been already accepted by another player!"));
		}
		else
		{
			MySQLQuery("UPDATE `missions` SET `acceptUserId` = '%d' WHERE `id` = '%d'", PVar:playerID[USERID], missionID);
			SendClientMessageEx(playerID, COLOR_INFO, StringID:15("You have accepted the job"));
			SendClientMessageEx(GetPlayerByUserID(strval(GetMySQLValue("missions", "creatorUserId", "id", val2str(missionID)))), COLOR_INFO, StringID:1("%p has accepted your job (Order ID: %d)"), playerID, missionID);
			MySQLQuery("SELECT `missionId`, `value` = '%d' FROM `missiondata` WHERE 1", value);
			mysql_store_result();
			CreateVehicle(value, -1665.6422, 1323.6527, 7.1792, 310.3344, 20, 5,-1);
			mysql_free_result();
		}
	}
}