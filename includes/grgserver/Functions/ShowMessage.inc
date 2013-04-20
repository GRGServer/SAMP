ShowMessage(playerID, messageID, waitTime = 3000)
{
	new languageStringName[100];
	switch (messageID)
	{
		case 1:
		{
			languageStringName = "276:";
		}
		case 2:
		{
			languageStringName = "277";
		}
		case 3:
		{
			languageStringName = "278";
		}
		case 4:
		{
			languageStringName = "279";
		}
		case 5:
		{
			languageStringName = "280";
		}
		case 6:
		{
			languageStringName = "292";
		}
		case 7:
		{
			languageStringName = "293";
		}
		case 8:
		{
			languageStringName = "294";
		}
		case 9:
		{
			languageStringName = "564";
		}
		case 10:
		{
			languageStringName = "565";
		}
		case 11:
		{
			languageStringName = "566";
		}
		case 12:
		{
			languageStringName = "567";
		}
		case 13:
		{
			languageStringName = "568";
		}
		case 14:
		{
			languageStringName = "281";
		}
		case 15:
		{
			languageStringName = "569";
		}
		case 16:
		{
			languageStringName = "570";
		}
		case 17:
		{
			languageStringName = "574";
		}
		case 18:
		{
			languageStringName = "575";
		}
		case 19:
		{
			languageStringName = "590";
		}
		case 20:
		{
			languageStringName = "591";
		}
		case 21:
		{
			languageStringName = "594";
		}
		case 22:
		{
			languageStringName = "595";
		}
		case 23:
		{
			languageStringName = "596";
		}
		case 24:
		{
			languageStringName = "597";
		}
		case 25:
		{
			languageStringName = "598";
		}
		case 26:
		{
			languageStringName = "601";
		}
		case 27:
		{
			languageStringName = "602";
		}
		case 28:
		{
			switch (PVar:playerID[DRIVINGSCHOOL_TYPE])
			{
				case DRIVINGSCHOOL_BIKE:
				{
					languageStringName = "604";
				}
				case DRIVINGSCHOOL_CAR:
				{
					languageStringName = "603";
				}
				case DRIVINGSCHOOL_TRUCK:
				{
					languageStringName = "605";
				}
			}
		}
		case 29:
		{
			languageStringName = "607";
		}
		case 30:
		{
			languageStringName = "608";
		}
		case 31:
		{
			languageStringName = "616";
		}
		case 32:
		{
			languageStringName = "618";
		}
	}
	if (StrNotNull(languageStringName))
	{
		ShowSubtitle(playerID, LanguageString(playerID, languageStringName));
		SetTimerEx("OnMessageShown", waitTime, false, "dd", playerID, messageID);
	}
}