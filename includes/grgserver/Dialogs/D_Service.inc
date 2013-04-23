ShowDialog:Service(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:176("")));// Item 1
	AddLine(options, "ADAC");// Item 2
	AddLine(options, "Taxi");// Item 3
	AddLine(options, LanguageString(playerID, StringID:221("")));// Item 4
	CreateDialog(playerID, "Service", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:577("")), options, LanguageString(playerID, StringID:164("")), LanguageString(playerID, StringID:165("")));
}

DialogResponse:Service(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:578(""));
				new missionID = CreateJob(playerID, JOB_POLICE);
				if (missionID)
				{
					AddJobData(missionID, "Type", "GetOrderPolice");
					AddJobData(missionID, "PlayerID", val2str(playerID));
				}
			}
			case 1:
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:578(""));
				new missionID = CreateJob(playerID, JOB_ADAC);
				if (missionID)
				{
					AddJobData(missionID, "Type", "GetOrderADAC");
					AddJobData(missionID, "PlayerID", val2str(playerID));
				}
			}
			case 2:
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:578(""));
				new missionID = CreateJob(playerID, JOB_TAXI);
				if (missionID)
				{
					AddJobData(missionID, "Type", "GetOrderTaxi");
					AddJobData(missionID, "PlayerID", val2str(playerID));
				}
			}
			case 3: 
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:578(""));
				new missionID = CreateJob(playerID, JOB_PARAMEDIC);
				if (missionID)
				{
					AddJobData(missionID, "Type", "GetOrderPolice");
					AddJobData(missionID, "PlayerID", val2str(playerID));
				}
			}
		}
	}
}