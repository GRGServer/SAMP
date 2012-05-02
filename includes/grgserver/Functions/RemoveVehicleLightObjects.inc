RemoveVehicleLightObjects(vehicleID)
{
	Count(slotID, _:enum_neonType)
	{
		Count(colorID, LIGHTOBJECT_MAXCOLORS)
		{
			if (vehicleLightObjects[vehicleID][enum_neonType:slotID][colorID])
			{
				DestroyDynamicObject(vehicleLightObjects[vehicleID][enum_neonType:slotID][colorID]);
			}
		}
	}
}