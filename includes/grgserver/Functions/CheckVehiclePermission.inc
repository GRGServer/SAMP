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

CheckVehiclePermission(playerID, vehicleID)
{
	if (!VehicleProperty:vehicleID[SAVEID])
	{
		if (!permissions[playerID][PERMISSION_MAPPER])
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 129, GetPermissionName(PERMISSION_MAPPER));
			return false;
		}
		else
		{
			return true;
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
	MySQLQuery("SELECT * FROM `vehicles` WHERE `ID` = '%d'", VehicleProperty:vehicleID[SAVEID]);
	mysql_store_result();
	new ownerUserID = strval(GetMySQLField("OwnerUserID"));
	new Float:price = floatstr(GetMySQLField("Price"));
	mysql_free_result();
	if (!ownerUserID && price)
	{
		ShowDialog:BuyVehicle(playerID, price);
		return false;
	}
	if (ownerUserID)
	{
		if (ownerUserID == PVar:playerID[USERID])
		{
			return true;
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 130);
			return false;
		}
	}
	if (!price && !permissions[playerID][PERMISSION_MAPPER])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 129, GetPermissionName(PERMISSION_MAPPER));
		return false;
	}
	return true;
}