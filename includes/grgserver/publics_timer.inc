forward timer_fast();
public timer_fast()
{
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerConnected(playerID) && !IsPlayerNPC(playerID))
		{
			if (IsPlayerInAnyVehicle(playerID))
			{
				new Float:velocityX;
				new Float:velocityY;
				new Float:velocityZ;
				new Float:health;
				new string[256];
				new healthColor;
				new speed;
				new healthPercentage;
				new vehicleID = GetPlayerVehicleID(playerID);
				GetVehicleVelocity(vehicleID, velocityX, velocityY, velocityZ);
				GetVehicleHealth(vehicleID, health);
				speed = floatround(floatsqroot(floatabs(floatpower(velocityX + velocityY + velocityZ, 2))) * 100 * 1.61);
				healthPercentage = floatround(health /10);
				if (healthPercentage > 65)
				{
					healthColor = 'g';
				}
				else
				{
					if (healthPercentage > 40)
					{
						healthColor = 'y';
					}
					else
					{
						healthColor = 'r';
					}
				}
				format(string, sizeof(string), "Geschwindigkeit: %d Km/h~n~Zustand: ~%c~%d%%~w~", speed, healthColor, healthPercentage);
				TextDrawSetString(textDrawSpeedo[playerID], string);
				TextDrawShowForPlayer(playerID, textDrawSpeedo[playerID]);
			}
			else
			{
				TextDrawHideForPlayer(playerID, textDrawSpeedo[playerID]);
			}
		}
	}
}

forward timer_slow();
public timer_slow()
{
	new hour;
	new minute;
	new second;
	gettime(hour, minute, second);
	SetWorldTime(hour);
	mysql_ping();
}
