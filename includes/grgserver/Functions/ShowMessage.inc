ShowMessage(playerID, messageID, waitTime = 3000)
{
	new stringID;
	switch (messageID)
	{
		case 1:
		{
			stringID = 276;
		}
		case 2:
		{
			stringID = 277;
		}
		case 3:
		{
			stringID = 278;
		}
		case 4:
		{
			stringID = 279;
		}
		case 5:
		{
			stringID = 280;
		}
		case 6:
		{
			stringID = 292;
		}
		case 7:
		{
			stringID = 293;
		}
		case 8:
		{
			stringID = 294;
		}
		case 9:
		{
			stringID = 564;
		}
		case 10:
		{
			stringID = 565;
		}
		case 11:
		{
			stringID = 566;
		}
		case 12:
		{
			stringID = 567;
		}
		case 13:
		{
			stringID = 568;
		}
		case 14:
		{
			stringID = 281;
		}
		case 15:
		{
			stringID = 569;
		}
		case 16:
		{
			stringID = 570;
		}
		case 17:
		{
			stringID = 574;
		}
		case 18:
		{
			stringID = 575;
		}
		case 19:
		{
			stringID = 590;
		}
		case 20:
		{
			stringID = 591;
		}
		case 21:
		{
			stringID = 594;
		}
		case 22:
		{
			stringID = 595;
		}
		case 23:
		{
			stringID = 596;
		}
		case 24:
		{
			stringID = 597;
		}
		case 25:
		{
			stringID = 598;
		}
		case 26:
		{
			stringID = 601;
		}
		case 27:
		{
			stringID = 602;
		}
		case 28:
		{
			switch (PVar:playerID[DRIVINGSCHOOL_TYPE])
			{
				case DRIVINGSCHOOL_BIKE:
				{
					stringID = 604;
				}
				case DRIVINGSCHOOL_CAR:
				{
					stringID = 603;
				}
				case DRIVINGSCHOOL_TRUCK:
				{
					stringID = 605;
				}
			}
		}
		case 29:
		{
			stringID = 607;
		}
		case 30:
		{
			stringID = 608;
		}
		case 31:
		{
			stringID = 616;
		}
		case 32:
		{
			stringID = 618;
		}
	}
	if (stringID)
	{
		ShowSubtitle(playerID, LanguageString(playerID, stringID));
		SetTimerEx("OnMessageShown", waitTime, false, "dd", playerID, messageID);
	}
}