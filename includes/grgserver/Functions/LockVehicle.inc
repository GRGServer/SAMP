/**
 * <summary>
 *	Lock or unlock a vehicle
 * </summary>
 *
 * <param name="vehicleID">
 *	The ID of the vehicle to lock or unlock
 * </param>
 *
 * <param name="newState">
 *	<title>The lock state</title>
 *	<item name="true">Locks the vehicle</item>
 *	<item name="false">Unlocks the vehicle</item>
 * </param>
 */

LockVehicle(vehicleID, newState)
{
	new engine;
	new lights;
	new alarm;
	new doors;
	new bonnet;
	new boot;
	new objective;
	GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
	if (doors != newState)
	{
		SetVehicleParamsEx(vehicleID, engine, lights, alarm, newState, bonnet, boot, objective);
	}
}