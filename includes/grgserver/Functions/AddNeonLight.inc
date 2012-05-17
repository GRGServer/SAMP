AddNeonLight(vehicleID, type, neonID)
{
	new color[LIGHTOBJECT_MAXCOLORS];
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:rotX;
	new Float:rotY;
	new Float:rotZ;
	switch (type)
	{
		case NEONTYPE_FRONT_LEFT:
		{
			posX = -1.0;
			posY = 7.0;
			posZ = -0.6;
		}
		case NEONTYPE_FRONT_RIGHT:
		{
			posX = 1.0;
			posY = 7.0;
			posZ = -0.6;
		}
		case NEONTYPE_LEFT:
		{
			posX = -0.8;
			posZ = -1.0;
		}
		case NEONTYPE_RIGHT:
		{
			posX = 0.8;
			posZ = -1.0;
		}
		default:
		{
			printf("Invalid neon light type: %d", type);
			return false;
		}
	}
	switch (neonID)
	{
		case NEON_DARKBLUE:
		{
			color[0] = 18648;
		}
		case NEON_GOLD:
		{
			color[0] = 18652;
			color[1] = 18650;
		}
		case NEON_GREEN:
		{
			color[0] = 18649;
		}
		case NEON_LIGHTBLUE:
		{
			color[0] = 18648;
			color[1] = 18652;
		}
		case NEON_LIGHTGREEN:
		{
			color[0] = 18649;
			color[1] = 18652;
		}
		case NEON_ORANGE:
		{
			color[0] = 18647;
			color[1] = 18650;
		}
		case NEON_PINK:
		{
			color[0] = 18647;
			color[1] = 18652;
		}
		case NEON_PURPLE:
		{
			color[0] = 18651;
		}
		case NEON_RED:
		{
			color[0] = 18647;
		}
		case NEON_TURQUOISE:
		{
			color[0] = 18648;
			color[1] = 18649;
		}
		case NEON_WHITE:
		{
			color[0] = 18652;
		}
		case NEON_YELLOW:
		{
			color[0] = 18650;
		}
	}
	Count(colorID, LIGHTOBJECT_MAXCOLORS)
	{
		if (vehicleLightObjects[vehicleID][enum_neonType:type][colorID])
		{
			DestroyDynamicObject(vehicleLightObjects[vehicleID][enum_neonType:type][colorID]);
			vehicleLightObjects[vehicleID][enum_neonType:type][colorID] = 0;
		}
		if (color[colorID])
		{
			new objectID = CreateDynamicObject(color[colorID], 0, 0, 0, 0, 0, 0, -1, -1, -1, STREAMER_OBJECTDISTANCE);
			AttachDynamicObjectToVehicle(objectID, vehicleID, posX, posY, posZ, rotX, rotY, rotZ);
			Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID, OBJECTTYPE_NEONLIGHT);
			vehicleLightObjects[vehicleID][enum_neonType:type][colorID] = objectID;
		}
	}
	UpdateObjectsForAllPlayers();
	return true;
}