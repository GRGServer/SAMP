forward timer_fast();
public timer_fast()// FIXME
{
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerConnected(playerID))
		{
			if (!IsPlayerNPC(playerID) && IsPlayerInAnyVehicle(playerID))
			{
				// Requires fix (Will *not* work!)
				/* new Float:vehiclePosX[MAX_PLAYERS];
				new Float:vehiclePosY[MAX_PLAYERS];
				new Float:vehiclePosZ[MAX_PLAYERS];
				GetVehicleVelocty(GetPlayerVehicleID(playerID), vehiclePosX[playerID], vehiclePosY[playerID], vehiclePosZ[playerID]);
				new distance[MAX_PLAYER_ID] = floatsqroot(((vehiclePosX[playerID]*vehiclePosX[playerID])+(vehiclePosY[playerID]*vehiclePosY[playerID])+(vehiclePosZ[playerID]*vehiclePosZ[playerID])))*100;
				new speed[MAX_PLAYER_ID] = floatsqroot(distance[playerID],floatround_round);
				format(speedo,sizeof(speedo),"%iKM\h", speed[playerID]);
				TextDrawSetString(vehicledisplay[playerID],speed[playerID]);*/
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
