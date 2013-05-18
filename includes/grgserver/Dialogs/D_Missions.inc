ShowDialog:Missions(playerID)
{
	new missionList[2048];

	MySQLQuery("SELECT `id`, `type`, `data` FROM `missions` WHERE `jobId` = '%d' AND `acceptUserId` = '0' ORDER BY `id` ASC", PVar:playerID[JOBID]);
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new missionTitle[100];
		new type[100];
		new missionData[20][2][32];
		new validType;
		new missionID = strval(GetMySQLField("id"));
		strcat(type, GetMySQLField("type"));
		GetMissionData(GetMySQLField("data"), missionData);

		if (IsStr(type, "GetOrderedCar"))
		{
			new modelID;
			Foreach(arrayIndex, missionData)
			{
				if (IsStr(missionData[arrayIndex][0], "modelId"))
				{
					modelID = strval(missionData[arrayIndex][1]);
				}
			}
			if (modelID >= 400 && modelID <= 611)
			{
				if (IsStr(vehicleModels[modelID - 400][VEHICLEMODEL_TYPE], "Car"))
				{
					Format:missionTitle(LanguageString(playerID, StringID:586("Pickup an ordered car (%s)")), vehicleModels[modelID - 400][VEHICLEMODEL_NAME]);
				}
				else
				{
					printf("WARNING: %s is not a car!", vehicleModels[modelID - 400][VEHICLEMODEL_NAME]);
				}
			}
			else
			{
				printf("WARNING: Invalid vehicle model ID (%d) for mission %d!", modelID, missionID);
			}
			validType = true;
		}

		if (validType)
		{
			AddLine:missionList("%d\t%s", missionID, missionTitle);
		}
		else
		{
			printf("Invalid mission type '%s' for mission %d", type, missionID);
		}
	}
	mysql_free_result();

	if (strlen(missionList))
	{
		CreateDialog(playerID, "Missions", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:163("Accept order")), missionList, LanguageString(playerID, StringID:164("Accept")), LanguageString(playerID, StringID:165("Cancel")));
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:134("There are currently no missions available for your job!"));
	}
}

DialogResponse:Missions(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new accepted;
		new missionID;
		new text[100];
		sscanf(inputText, "p<\t>ds[100]", missionID, text);
		MySQLQuery("SELECT `creatorUserId`, `acceptUserId`, `type`, `data` FROM `missions` WHERE `id` = '%d'", missionID);
		mysql_store_result();
		if (strval(GetMySQLField("acceptUserId")))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:12("This job has been already accepted by another player!"));
		}
		else
		{
			new type[100];
			new missionData[20][2][32];

			strcat(type, GetMySQLField("type"));
			GetMissionData(GetMySQLField("data"), missionData);

			if (IsStr(type, "GetOrderedCar"))
			{
				new modelID;
				Foreach(arrayIndex, missionData)
				{
					if (IsStr(missionData[arrayIndex][0], "modelId"))
					{
						modelID = strval(missionData[arrayIndex][1]);
					}
				}
				if (modelID >= 400 && modelID <= 611)
				{
					if (IsStr(vehicleModels[modelID - 400][VEHICLEMODEL_TYPE], "Car"))
					{
						if (GetClosestVehicleInRange(ORDER_CAR_SPAWN_POSX, ORDER_CAR_SPAWN_POSY, ORDER_CAR_SPAWN_POSZ, ORDER_CAR_MINDISTANCE))
						{
							SendClientMessageEx(playerID, COLOR_ERROR, StringID:46("Another vehicle has been already spawned!"));
							SendClientMessageEx(playerID, COLOR_ERROR, StringID:47("Please try again later"));
						}
						else
						{
							new vehicleID = CreateVehicleEx(modelID, ORDER_CAR_SPAWN_POSX, ORDER_CAR_SPAWN_POSY, ORDER_CAR_SPAWN_POSZ, ORDER_CAR_SPAWN_ANGLE, -1, -1, false);
							SetVehicleParamsForPlayer(vehicleID, playerID, true, false);
							accepted = true;
						}
					}
					else
					{
						printf("WARNING: %s is not a car!", vehicleModels[modelID - 400][VEHICLEMODEL_NAME]);
					}
				}
				else
				{
					printf("WARNING: Invalid vehicle model ID (%d) for mission %d!", modelID, missionID);
				}
			}
		}
		mysql_free_result();

		if (accepted)
		{
			SendClientMessageEx(playerID, COLOR_INFO, StringID:15("You have accepted the job"));
			SendClientMessageEx(GetPlayerByUserID(strval(GetMySQLField("creatorUserId"))), COLOR_INFO, StringID:1("%p has accepted your job (Order ID: %d)"), playerID, missionID);
			MySQLQuery("UPDATE `missions` SET `acceptUserId` = '%d', `acceptTime` = NOW() WHERE `id` = '%d'", PVar:playerID[USERID], missionID);
		}
	}
}