/**
 * <summary>
 *	Spawn a pickup
 *	Adds the pickup to the database if saveToDB is true
 * </summary>
 *
 * <param name="pickupID">
 *	ID from pickups table in database (Only required if saveToDB is false)
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
 * <param name="saveToDB">
 *	Adds the pickup to the database if true (Used to create new pickup)
 * </param>
 *
 * <returns>
 *	<item name="-1">Invalid pickup type</item>
 *	<item name="-2">Spawned without adding to pickups table</item>
 *	<item name="ID">The ID of the new pickup in the pickups table</item>
 * </returns>
 */

AddPickup(pickupID, type[], Float:posX, Float:posY, Float:posZ, saveToDB)
{
	new modelID;
	new pickup;
	FormatNew:functionName[MAX_FUNCTION_NAME]("PUMID_%s", type);// PUMID = PickUpModelID
	modelID = CallLocalFunction(functionName, "d", pickupID);
	if (modelID)
	{
		pickup = CreatePickup(modelID, 23, posX, posY, posZ, -1);
		pickups[pickup][PICKUP_POSX] = posX;
		pickups[pickup][PICKUP_POSY] = posY;
		pickups[pickup][PICKUP_POSZ] = posZ;
		format(pickups[pickup][PICKUP_TYPE], STRINGLENGTH_PICKUPTYPE, type);
		if (saveToDB)
		{
			MySQLQuery("INSERT INTO `pickups` (`posX`, `posY`, `posZ`, `type`) VALUES('%f', '%f', '%f', '%s')", posX, posY, posZ, type);
			pickups[pickup][PICKUP_ID] = mysql_insert_id();
			return pickups[pickup][PICKUP_ID];
		}
		else
		{
			pickups[pickup][PICKUP_ID] = pickupID;
			return -2;
		}
	}
	else
	{
		return -1;
	}
}