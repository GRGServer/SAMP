public OnPlayerEnterCheckpoint(playerid)
{
	switch (PVar:playerid[CURRENTCHECKPOINT])
	{
		case CHECKPOINT_DRVSCHOOL_VEHICLE:
		{
			DisablePlayerCheckpoint(playerid);
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			new type[STRINGLENGTH_VEHICLETYPE];
			new missionID;
			GetPlayerPos(playerid, posX, posY, posZ);
			switch (PVar:playerid[DRIVINGSCHOOL_TYPE])
			{
				case DRIVINGSCHOOL_BIKE:
				{
					strcat(type, "Bike");
					missionID = GetCheckpointMissionByName("DrivingSchool_Bike_%", true);
				}
				case DRIVINGSCHOOL_CAR:
				{
					strcat(type, "Car");
					missionID = GetCheckpointMissionByName("DrivingSchool_Car_%", true);
				}
				case DRIVINGSCHOOL_TRUCK:
				{
					strcat(type, "Truck");
					missionID = GetCheckpointMissionByName("DrivingSchool_Truck_%", true);
				}
			}
			if (missionID)
			{
				new vehicleID = GetClosestVehicleInRange(posX, posY, posZ, 50, 0, true, JOB_SCHOOLDRIVER, type);
				if (vehicleID)
				{
					VehicleProperty:vehicleID[ALLOWDRIVEPLAYERID] = playerid;
					RepairVehicle(vehicleID);
					VehicleProperty:vehicleID[CURRENTFUEL] = vehicleModels[GetVehicleModel(vehicleID) - 400][VEHICLEMODEL_MAXFUEL];
					PutPlayerInVehicle(playerid, vehicleID, 0);
					StartCheckpointMission(playerid, missionID, vehicleID);
				}
				else
				{
					ShowMessage(playerid, 30, 3000);
				}
			}
			else
			{
				ShowMessage(playerid, 31, 3000);
			}
		}
		case CHECKPOINT_INPLANE_EXIT:
		{
			DisablePlayerCheckpoint(playerid);
			StartScreenFader(playerid, 0, 0, 0, 5, 0, FADE_START_PLANEEXIT, 0);
			TogglePlayerControllable(playerid, false);
		}
		case CHECKPOINT_NAVITARGET:
		{
			DisablePlayerCheckpoint(playerid);
			SendClientMessageEx(playerid, COLOR_INFO, 344);
			PlaySound(playerid, SOUND_NAVITARGETREACHED);
		}
		case CHECKPOINT_TUTORIAL_BANK:
		{
			DisablePlayerCheckpoint(playerid);
			StartScreenFader(playerid, 0, 0, 0, 5, 0, FADE_TUTORIAL_BANK_START, 0);
			TogglePlayerControllable(playerid, false);
		}
		case CHECKPOINT_TUTORIAL_BUS1:
		{
			DisablePlayerCheckpoint(playerid);
			ShowMessage(playerid, 15, 3000);
			SetPlayerCheckpointEx(playerid, CHECKPOINT_TUTORIAL_BUS1_EXIT, 1077.860839, 1199.208374, 10.820312, 1.5);
		}
		case CHECKPOINT_TUTORIAL_BUS1_EXIT:
		{
			DisablePlayerCheckpoint(playerid);
			ShowMessage(playerid, 16, 3000);
			SetPlayerCheckpointEx(playerid, CHECKPOINT_TUTORIAL_BANK, 1047.7939, 1025.5156, 11.0, 1.5);
		}
		case CHECKPOINT_TUTORIAL_BUS2:
		{
			DisablePlayerCheckpoint(playerid);
			ShowMessage(playerid, 10, 3000);
		}
		case CHECKPOINT_TUTORIAL_BUS3:
		{
			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpointEx(playerid, CHECKPOINT_TUTORIAL_TRAIN1, 2859.574218, 1290.556030, 11.390625, 1.5);
			ShowMessage(playerid, 12, 3000);
		}
		case CHECKPOINT_TUTORIAL_BUS4:
		{
			DisablePlayerCheckpoint(playerid);
			ShowMessage(playerid, 18, 3000);
			SetPlayerCheckpointEx(playerid, CHECKPOINT_TUTORIAL_BUS4_EXIT, -2090.970947, -77.046791, 35.320312, 1.5);
		}
		case CHECKPOINT_TUTORIAL_BUS4_EXIT:
		{
			DisablePlayerCheckpoint(playerid);
			PlayAudio(playerid, "mission_complete2.ogg");
			GameTextForPlayer(playerid, LanguageString(playerid, 576), 5000, 3);
			SetPlayerCameraPos(playerid, -2084.015136, -70.748046, 34.384109);
			SetPlayerCameraLookAt(playerid, -2092.510986, -77.142700, 36.228786);
			TogglePlayerControllable(playerid, false);
			SetTimerEx("Timer_ScreenFader", 5000, false, "ddddddd", playerid, 0, 0, 0, 5, 0, FADE_TUTORIAL_END1, 0);
		}
		case CHECKPOINT_TUTORIAL_SPEAKER1:
		{
			DisablePlayerCheckpoint(playerid);
			StartScreenFader(playerid, 0, 0, 0, 5, 0, FADE_TUTORIAL_S1_START, 0);
			TogglePlayerControllable(playerid, false);
		}
		case CHECKPOINT_TUTORIAL_TRAIN1:
		{
			DisablePlayerCheckpoint(playerid);
			ShowMessage(playerid, 13, 3000);
			SetPlayerCheckpointEx(playerid, CHECKPOINT_TUTORIAL_TRAIN1_EXIT, -1952.286376, 137.548049, 26.281250, 1.5);
		}
		case CHECKPOINT_TUTORIAL_TRAIN1_EXIT:
		{
			DisablePlayerCheckpoint(playerid);
			ShowMessage(playerid, 17, 3000);
			SetPlayerCheckpointEx(playerid, CHECKPOINT_TUTORIAL_BUS4, -1986.010742, 149.384109, 27.687500, 1.5);
		}
		case CHECKPOINT_TRAILER1:
		{
			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpointEx(playerid, CHECKPOINT_ORDEREND1, -1106.5825, -1620.9615, 75.9425, 10.0);
		}
		case CHECKPOINT_TRAILER2:
		{
			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpointEx(playerid, CHECKPOINT_ORDEREND2, 597.9862, 871.9865, -43.4022, 10.0);
		}
		case CHECKPOINT_TRAILER3:
		{
			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpointEx(playerid, CHECKPOINT_ORDEREND3, 2648.7891, 2732.5945, 10.8203, 10.0);
		}
		case CHECKPOINT_TRAILER4:
		{
			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpointEx(playerid, CHECKPOINT_ORDEREND4, -64.0349, 41.7692, 3.1103, 10.0);
		}
		case CHECKPOINT_ORDEREND1:
		{
			DisablePlayerCheckpoint(playerid);
			new Float:bank = 300.00;
			SendClientMessageEx(playerid, COLOR_INFO, 551, bank);
			SendClientMessageEx(playerid, COLOR_INFO, 552);
			GivePlayerMoneyEx(playerid, MONEY_BANK, bank);
		}
		case CHECKPOINT_ORDEREND2:
		{
			DisablePlayerCheckpoint(playerid);
			new Float:bank2 = 600.00;
			SendClientMessageEx(playerid, COLOR_INFO, 551, bank2);
			SendClientMessageEx(playerid, COLOR_INFO, 552);
			GivePlayerMoneyEx(playerid, MONEY_BANK, bank2);
		}
		case CHECKPOINT_ORDEREND3:
		{
			DisablePlayerCheckpoint(playerid);
			new Float:bank3 = 1200.00;
			SendClientMessageEx(playerid, COLOR_INFO, 551, bank3);
			SendClientMessageEx(playerid, COLOR_INFO, 552);
			GivePlayerMoneyEx(playerid, MONEY_BANK, bank3);
		}
		case CHECKPOINT_ORDEREND4:
		{
			DisablePlayerCheckpoint(playerid);
			new Float:bank4 = 900.00;
			SendClientMessageEx(playerid, COLOR_INFO, 551, bank4);
			SendClientMessageEx(playerid, COLOR_INFO, 552);
			GivePlayerMoneyEx(playerid, MONEY_BANK, bank4);
		}
		case CHECKPOINT_VEHICLEMARKER:
		{
			// Does nothing (Also does *NOT* remove the checkpoint!)
		}
	}
}