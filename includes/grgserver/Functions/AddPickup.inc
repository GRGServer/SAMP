/**
 * <summary>
 *	Spawns a pickup
 * </summary>
 *
 * <param name="pickupID">
 *	ID from pickups table in database
 * </param>
 *
 * <param name="type">
 *	Type of the pickup as string (See  for details)
 * </param>
 *
 * <param name="posX">
 *	The X position as float
 * </param>
 *
 * <param name="posY">
 *	The Y position as float
 * </param>
 *
 * <param name="posZ">
 *	The Z position as float
 * </param>
 *
 * <returns>
 *	<item>true if the pickup has been spawned</item>
 *	<item>false if the pickup could not be spawned (e.g. model ID not assigned in PickupModelID function)</item>
 * </returns>
 */

AddPickup(pickupID, type[], Float:posX, Float:posY, Float:posZ)
{
	new modelID;
	new pickup;
	FormatNew:functionName[MAX_FUNCTION_NAME]("PUMID_%s", type);// PUMID = PickUpModelID
	modelID = CallLocalFunction(functionName, "d", pickupID);
	if (!modelID)
	{
		return false;
	}
	pickup = CreatePickup(modelID, 23, posX, posY, posZ, -1);
	pickups[pickup][PICKUP_ID] = pickupID;
	pickups[pickup][PICKUP_POSX] = posX;
	pickups[pickup][PICKUP_POSY] = posY;
	pickups[pickup][PICKUP_POSZ] = posZ;
	format(pickups[pickup][PICKUP_TYPE], STRINGLENGTH_PICKUPTYPE, type);
	return true;
}