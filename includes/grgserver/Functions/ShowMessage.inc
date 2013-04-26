ShowMessage(playerID, messageID, waitTime = 3000)
{
	new languageStringID;
	switch (messageID)
	{
		case 1:
		{
			languageStringID = StringID:276("Halt!!! If you once again try to steal the cucumbers of my sandwich, your head makes a city tour!");
		}
		case 2:
		{
			languageStringID = StringID:277("What? I'm new in this city!");
		}
		case 3:
		{
			languageStringID = StringID:278("Yeah yeah, everyone who steals my cucumbers say that!");
		}
		case 4:
		{
			languageStringID = StringID:279("Ehm... I just want to know what I should do now...");
		}
		case 5:
		{
			languageStringID = StringID:280("You are asking what you should do??? Get out of my face before I change my mind with the city tour!");
		}
		case 6:
		{
			languageStringID = StringID:292("This is one of the banks in San Andreas");
		}
		case 7:
		{
			languageStringID = StringID:293("Here you can create bank accounts which are for example required to get paid at the payday or to buy vehicles and houses");
		}
		case 8:
		{
			languageStringID = StringID:294("You can enter a bank by going into the bank pickup and press ~k~~CONVERSATION_YES~ to pick up the pickup");
		}
		case 9:
		{
			languageStringID = StringID:564("Now take the next bus and drive to the train station");
		}
		case 14:
		{
			languageStringID = StringID:281("Go to the bus stop and wait for the next bus");
		}
		case 19:
		{
			languageStringID = StringID:590("You should now get a driving license. But you can also get it later.");
		}
		case 20:
		{
			languageStringID = StringID:591("After that you can buy a car at the junk yard");
		}
		case 21:
		{
			languageStringID = StringID:594("So you want to get a driving license?");
		}
		case 22:
		{
			languageStringID = StringID:595("First I will explain you the rules.");
		}
		case 23:
		{
			languageStringID = StringID:596("In the city you can drive up to 50 km/h.");
		}
		case 24:
		{
			languageStringID = StringID:597("Outside of the city there is a speed limit of 100 km/h.");
		}
		case 25:
		{
			languageStringID = StringID:598("On the highways there are no speed limits.");
		}
		case 26:
		{
			languageStringID = StringID:601("OK, then we will start with your first driving lesson.");
		}
		case 27:
		{
			languageStringID = StringID:602("Come back later if you are ready to drive.");
		}
		case 28:
		{
			switch (PVar:playerID[DRIVINGSCHOOL_TYPE])
			{
				case DRIVINGSCHOOL_BIKE:
				{
					languageStringID = StringID:604("Get on a bike");
				}
				case DRIVINGSCHOOL_CAR:
				{
					languageStringID = StringID:603("Enter a car");
				}
				case DRIVINGSCHOOL_TRUCK:
				{
					languageStringID = StringID:605("Enter a truck");
				}
			}
		}
		case 32:
		{
			languageStringID = StringID:618("You already have a driving license, so I will skip the common basics.");
		}
	}
	if (languageStringID)
	{
		ShowSubtitle(playerID, LanguageString(playerID, languageStringID));
		SetTimerEx("OnMessageShown", waitTime, false, "dd", playerID, messageID);
	}
}