GetVehicleWithinDistance( playerid, Float:x1, Float:y1, Float:z1, Float:dist, &veh)
{
	for(new i = 1; i < MAX_VEHICLES; i++)
	{
		if(GetVehicleModel(i) > 0)
		{
			if(GetPlayerVehicleID(playerid) != i )
			{
				new Float:x, Float:y, Float:z;
				new Float:x2, Float:y2, Float:z2;
				GetVehiclePos(i, x, y, z);
				x2 = x1 - x; y2 = y1 - y; z2 = z1 - z;
				new Float:vDist = (x2*x2+y2*y2+z2*z2);
				if( vDist < dist)
				{
					veh = i;
					dist = vDist;
				}
			}
		}
	}
}