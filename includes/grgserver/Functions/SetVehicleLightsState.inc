SetVehicleLightsState(vehicleID, newState)
{
	new engine;
	new lights;
	new alarm;
	new doors;
	new bonnet;
	new boot;
	new objective;
	GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
	if (lights != newState)
	{
		SetVehicleParamsEx(vehicleID, engine, newState, alarm, doors, bonnet, boot, objective);
	}
}