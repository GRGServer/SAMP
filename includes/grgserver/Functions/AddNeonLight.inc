AddNeonLight(vehicleID, neonID)
{
	new slot[NEONLIGHT_MAXSLOTS][NEONLIGHT_MAXSUBSLOTS];
	new Float:slotOffset[NEONLIGHT_MAXSLOTS][3] = 
	{
		{0.8, 0.0, -0.70},
		{-0.8, 0.0, -0.70}
	};
	new Float:slotRotation[NEONLIGHT_MAXSLOTS][3] = 
	{
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0}
	};
	VehicleProperty:vehicleID[NEONLIGHTID] = neonID + 1;
	switch (neonID)
	{
		case NEON_DARKBLUE:
		{
			slot[0][0] = 18648;
			slot[1][0] = 18648;
		}
		case NEON_GOLD:
		{
			slot[0][0] = 18652;
			slot[0][1] = 18650;
			slot[1][0] = 18652;
			slot[1][1] = 18650;
		}
		case NEON_GREEN:
		{
			slot[0][0] = 18649;
			slot[1][0] = 18649;
		}
		case NEON_LIGHTBLUE:
		{
			slot[0][0] = 18648;
			slot[0][1] = 18652;
			slot[1][0] = 18648;
			slot[1][1] = 18652;
		}
		case NEON_LIGHTGREEN:
		{
			slot[0][0] = 18649;
			slot[0][1] = 18652;
			slot[1][0] = 18649;
			slot[1][1] = 18652;
		}
		case NEON_ORANGE:
		{
			slot[0][0] = 18647;
			slot[0][1] = 18650;
			slot[1][0] = 18647;
			slot[1][1] = 18650;
		}
		case NEON_PINK:
		{
			slot[0][0] = 18647;
			slot[0][1] = 18652;
			slot[1][0] = 18647;
			slot[1][1] = 18652;
		}
		case NEON_PURPLE:
		{
			slot[0][0] = 18651;
			slot[1][0] = 18651;
		}
		case NEON_RED:
		{
			slot[0][0] = 18647;
			slot[1][0] = 18647;
		}
		case NEON_TURQUOISE:
		{
			slot[0][0] = 18648;
			slot[0][1] = 18649;
			slot[1][0] = 18648;
			slot[1][1] = 18649;
		}
		case NEON_WHITE:
		{
			slot[0][0] = 18652;
			slot[1][0] = 18652;
		}
		case NEON_YELLOW:
		{
			slot[0][0] = 18650;
			slot[1][0] = 18650;
		}
	}
	Count(slotID, NEONLIGHT_MAXSLOTS)
	{
		Count(subSlotID, NEONLIGHT_MAXSUBSLOTS)
		{
			DestroyDynamicObject(vehicleNeonLightObjects[vehicleID][slotID][subSlotID]);
			if (slot[slotID][subSlotID])
			{
				new objectID = CreateDynamicObject(slot[slotID][subSlotID], 0, 0, 0, 0, 0, 0);
				AttachDynamicObjectToVehicle(objectID, vehicleID, slotOffset[slotID][0], slotOffset[slotID][1], slotOffset[slotID][2], slotRotation[slotID][0], slotRotation[slotID][1], slotRotation[slotID][2]);
				Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID, OBJECTTYPE_NEONLIGHT);
				vehicleNeonLightObjects[vehicleID][slotID][subSlotID] = objectID;
			}
		}
	}
}