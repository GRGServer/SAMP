ShowMessage(playerID, messageID, waitTime = 3000)
{
	new languageStringID;
	switch (messageID)
	{
		case 1:
		{
			languageStringID = StringID:276("");
		}
		case 2:
		{
			languageStringID = StringID:277("");
		}
		case 3:
		{
			languageStringID = StringID:278("");
		}
		case 4:
		{
			languageStringID = StringID:279("");
		}
		case 5:
		{
			languageStringID = StringID:280("");
		}
		case 6:
		{
			languageStringID = StringID:292("");
		}
		case 7:
		{
			languageStringID = StringID:293("");
		}
		case 8:
		{
			languageStringID = StringID:294("");
		}
		case 9:
		{
			languageStringID = StringID:564("");
		}
		case 10:
		{
			languageStringID = StringID:565("");
		}
		case 11:
		{
			languageStringID = StringID:566("");
		}
		case 12:
		{
			languageStringID = StringID:567("");
		}
		case 13:
		{
			languageStringID = StringID:568("");
		}
		case 14:
		{
			languageStringID = StringID:281("");
		}
		case 15:
		{
			languageStringID = StringID:569("");
		}
		case 16:
		{
			languageStringID = StringID:570("");
		}
		case 17:
		{
			languageStringID = StringID:574("");
		}
		case 18:
		{
			languageStringID = StringID:575("");
		}
		case 19:
		{
			languageStringID = StringID:590("");
		}
		case 20:
		{
			languageStringID = StringID:591("");
		}
		case 21:
		{
			languageStringID = StringID:594("");
		}
		case 22:
		{
			languageStringID = StringID:595("");
		}
		case 23:
		{
			languageStringID = StringID:596("");
		}
		case 24:
		{
			languageStringID = StringID:597("");
		}
		case 25:
		{
			languageStringID = StringID:598("");
		}
		case 26:
		{
			languageStringID = StringID:601("");
		}
		case 27:
		{
			languageStringID = StringID:602("");
		}
		case 28:
		{
			switch (PVar:playerID[DRIVINGSCHOOL_TYPE])
			{
				case DRIVINGSCHOOL_BIKE:
				{
					languageStringID = StringID:604("");
				}
				case DRIVINGSCHOOL_CAR:
				{
					languageStringID = StringID:603("");
				}
				case DRIVINGSCHOOL_TRUCK:
				{
					languageStringID = StringID:605("");
				}
			}
		}
		case 29:
		{
			languageStringID = StringID:607("");
		}
		case 30:
		{
			languageStringID = StringID:608("");
		}
		case 31:
		{
			languageStringID = StringID:616("");
		}
		case 32:
		{
			languageStringID = StringID:618("");
		}
	}
	if (languageStringID)
	{
		ShowSubtitle(playerID, LanguageString(playerID, languageStringID));
		SetTimerEx("OnMessageShown", waitTime, false, "dd", playerID, messageID);
	}
}