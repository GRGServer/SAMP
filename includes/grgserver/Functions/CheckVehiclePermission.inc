/**
 * <summary>
 *	Checks if the player has the permission to use the vehicle.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player.
 * </param>
 *
 * <param name="vehicleID">
 *	The ID of the vehicle.
 * </param>
 *
 * <param name="showBuyDialog">
 *	<item name="true">Show the buy dialog if the player has not bought the vehicle yet and can buy it</item>
 *	<item name="false">Do not show the buy dialog</item>
 * </param>
 *
 * <returns>
 *	<item name="true">The player has the permission to use the vehicle</item>
 *	<item name="false">The player has not the permission to use the vehicle</item>
 * </returns>
 *
 * <remarks>
 *	<title>The following is checked:</title>
 *	<item>Is the vehicle not a saved vehicle and the player has the permission "Mapper"?</item>
 *	<item>Does the job ID of the player match the job ID of the vehicle?</item>
 *	<item>Does the vehicle have a price?</item>
 *	<item>Is the vehicle already owned and is the player the owner of the vehicle?</item>
 * </remarks>
 */

CheckVehiclePermission(playerID, vehicleID, showBuyDialog)
{
	if (!VehicleProperty:vehicleID[SAVEID])
	{
		if (permissions[playerID][PERMISSION_MAPPER])
		{
			return true;
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 129, GetPermissionName(PERMISSION_MAPPER));
			return false;
		}
	}
	if (VehicleProperty:vehicleID[JOBID])
	{
		if (PVar:playerID[JOBID] == VehicleProperty:vehicleID[JOBID])
		{
			return true;
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 327);
			return false;
		}
	}
	if (VehicleProperty:vehicleID[OWNERUSERID])
	{
		if (VehicleProperty:vehicleID[OWNERUSERID] == PVar:playerID[USERID])
		{
			return true;
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 130);
			return false;
		}
	}
	if (VehicleProperty:vehicleID[PRICE])
	{
		if (showBuyDialog)
		{
			ShowDialog:BuyVehicle(playerID, VehicleProperty:vehicleID[PRICE]);
		}
		return false;
	}
	if (permissions[playerID][PERMISSION_MAPPER])
	{
		return true;
	}
	SendClientMessageEx(playerID, COLOR_ERROR, 129, GetPermissionName(PERMISSION_MAPPER));
	return false;
}