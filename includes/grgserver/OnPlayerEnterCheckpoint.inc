public OnPlayerEnterCheckpoint(playerid)
{
	switch (GetPVar:playerid[CURRENTCHECKPOINT])
	{
		case CHECKPOINT_WALKTOPLANEEXIT:
		{
			// TODO: Fade to black
			// TeleportTo(playerid, posX, posY, posZ, angle, 0, 0);
		}
		case CHECKPOINT_WALKTOSEAT:
		{
			TogglePlayerControllable(playerid, false);
			// TODO: Sit down (Animation)
			SetTimerEx("Timer_FlyWithPlane", 5000, false, "ii", playerid, 1);
		}
		case CHECKPOINT_SPEAKER:
		{
			new Speaker[MAX_PLAYERS] = 0;
			new playerName[MAX_PLAYER_NAME];
			if(Speaker[playerid] == 0)
			{
				TogglePlayerControllable(playerid, false);
				FormatNew:string[30]("%s: Em... Hallo", playerName);
				SendClientMessage(playerid, COLOR_INFO, string);
				SendClientMessage(playerid, COLOR_INFO, "Anahme Leiter: Was ist denn?");
				Speaker[playerid] = 1;
				if(Speaker[playerid] == 1)
				{
					FormatNew:string1[40]("%s: Ich bin Neu hier....", playerName);
					SendClientMessage(playerid, COLOR_INFO, string1);
					SendClientMessage(playerid, COLOR_INFO, "Annahme Leiter: Schön und jetzt?");
					Speaker[playerid] = 2;
					if(Speaker[playerid] == 2)
					{
						FormatNew:string2[40]("%s: Was soll ich jetzt Machen?", playerName);
						SendClientMessage(playerid, COLOR_INFO, string2);
						SendClientMessage(playerid, COLOR_INFO, "Annahme Leiter: Jetzt Pass mal auf hier!");
						Speaker[playerid] = 3;
						if(Speaker[playerid] == 3)
						{
							SendClientMessage(playerid, COLOR_INFO, "Annahme Leiter: Ich erklär dir hier jetzt mal, wie das so läuft!");
							SendClientMessage(playerid, COLOR_INFO, "Annahme Leiter: 1. Es wird nicht gecheatet!");
							SendClientMessage(playerid, COLOR_INFO, "Annahme Leiter: 2. Beleidigungen kannst du gleich abhacken, denn dann wirst du Gemutet!");
							SendClientMessage(playerid, COLOR_INFO, "Annahme Leiter: 3. Einfach Reallife Spielen und Spass haben!");
							Speaker[playerid] = 4;
							if(Speaker[playerid] == 4)
							{
								SendClientMessage(playerid, COLOR_INFO, "Annahme Leiter: Alles verstanden?");
								FormatNew:string3[50]("%s: Eh... Ja... Schon....");
								SendClientMessage(playerid, COLOR_INFO, string3);
								Speaker[playerid] = 5;
								if(Speaker[playerid] == 5)
								{
									SendClientMessage(playerid, COLOR_INFO, "Annahme Leiter: Gut dann geh mir Jetzt nicht weiter auf die Nerven! -.-");
									SendClientMessage(playerid, COLOR_INFO, "Annahme Leiter: und steig bei Winfred ins Auto der wird dir weiterhelfen!");
									FormatNew:string4[50]("Ok, ok, ok...");
									SendClientMessage(playerid, COLOR_INFO, string4);
									TogglePlayerControllable(playerid, true);
								}
							}
						}
					}
				}
			}
		}
	}
}