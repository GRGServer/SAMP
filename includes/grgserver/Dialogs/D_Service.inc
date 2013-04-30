ShowDialog:Service(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:176("Police")));// Item 1
	AddLine(options, "ADAC");// Item 2
	AddLine(options, "Taxi");// Item 3
	AddLine(options, LanguageString(playerID, StringID:221("Ambulance")));// Item 4
	CreateDialog(playerID, "Service", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:577("Service")), options, LanguageString(playerID, StringID:164("Accept")), LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:Service(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:
			{
				new modelID;
				SendClientMessageEx(playerID, COLOR_INFO, StringID:578("Your request has been sent"));
				new missionID = CreateJob(playerID, JOB_POLICE, modelID);
				if (missionID)
				{
					AddJobData(missionID, "Type", "GetOrderPolice");
					AddJobData(missionID, "PlayerID", val2str(playerID));
				}
			}
			case 1:
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:578("Your request has been sent"));
				new modelID;
				new missionID = CreateJob(playerID, JOB_ADAC, modelID);
				if (missionID)
				{
					AddJobData(missionID, "Type", "GetOrderADAC");
					AddJobData(missionID, "PlayerID", val2str(playerID));
				}
			}
			case 2:
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:578("Your request has been sent"));
				new modelID;
				new missionID = CreateJob(playerID, JOB_TAXI, modelID);
				if (missionID)
				{
					AddJobData(missionID, "Type", "GetOrderTaxi");
					AddJobData(missionID, "PlayerID", val2str(playerID));
				}
			}
			case 3: 
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:578("Your request has been sent"));
				new modelID;
				new missionID = CreateJob(playerID, JOB_PARAMEDIC, modelID);
				if (missionID)
				{
					AddJobData(missionID, "Type", "GetOrderPolice");
					AddJobData(missionID, "PlayerID", val2str(playerID));
				}
			}
		}
	}
}