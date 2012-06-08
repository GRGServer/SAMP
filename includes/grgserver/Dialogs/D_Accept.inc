ShowDialog:Accept(playerID)
{
	new missionList[2048];
	MySQLQuery("SELECT * FROM `missions` WHERE `JobID` = '%d' AND `AcceptUserID` = '0' ORDER BY `Name` ASC", PVar:playerID[JOBID]);
	mysql_store_result();
	while (FetchMySQLRow())
	{
		if (strlen(missionList))
		{
			Format:missionList("%s\n", missionList);
		}
		Format:missionList("%s%s: %s", missionList, GetMySQLField("ID"), GetMySQLField("Name"));
	}
	mysql_free_result();
	if (strlen(missionList))
	{
		CreateDialog(playerID, "Accept", DIALOG_STYLE_LIST, LanguageString(playerID, 163), missionList, LanguageString(playerID, 164), LanguageString(playerID, 165));
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 134);
	}
}

DialogResponse:Accept(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new missionID;
		new text[100];
		sscanf(inputText, "p:ds", missionID, text);
		if (strval(GetMySQLValue("missions", "AcceptUserID", "ID", val2str(missionID))))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 12);
		}
		else
		{
			SetMySQLValue("missions", "AcceptUserID", val2str(PVar:playerID[USERID]), "ID", val2str(missionID));
			SendClientMessageEx(playerID, COLOR_INFO, 15);
			SendClientMessageEx(GetPlayerByUserID(strval(GetMySQLValue("missions", "CreatorUserID", "ID", val2str(missionID)))), COLOR_INFO, 1, playerID, missionID);
			MySQLQuery("SELECT * FROM `missiondata` WHERE `MissionID` = '%d' AND `Name` = 'VehicleModelID'", missionID);
			mysql_store_result();
			mysql_free_result();
		}
	}
}