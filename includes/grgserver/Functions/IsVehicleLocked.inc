/**
 * <summary>
 *	Check the locked state of a vehicle
 * </summary>
 *
 * <param name="vehicleID">
 *	The ID of the vehicle to check
 * </param>
 *
 * <returns>
 *	<item>true if the vehicle is locked</item>
 *	<item>false if the vehicle is not locked</item>
 * </returns>
 */

IsVehicleLocked(vehicleID)
{
	new engine;
	new lights;
	new alarm;
	new doors;
	new bonnet;
	new boot;
	new objective;
	GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
	return doors;
}