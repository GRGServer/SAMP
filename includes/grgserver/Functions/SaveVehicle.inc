/**
 * <summary>
 *	Update all properties of the specified vehicle in the database.
 * </summary>
 *
 * <param name="vehicleID">
 *	The ID of the vehicle which should be saved.
 * </param>
 *
 * <param name="interior">
 *	The interior where the vehicle should be spawned on load.
 * </param>
 *
 * <param name="asOriginalVehicle">
 *	<item name="true">
 *		Save the vehicle in the originalvehicles table<br />
 *		<b>IMPORTANT: Only use on dev server and in permission controlled commands like /savevehicle!</b>
 *	</item>
 *	<item name="false">Save the vehicle in the vehicles table (This is the default value if not specified)</item>
 * </param>
 */

SaveVehicle(vehicleID, interior, asOriginalVehicle = false)
{
	if (VehicleProperty:vehicleID[SAVEID])
	{
		new preSQL[30];
		new Float:health;
		new Float:posX; 
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetVehicleHealth(vehicleID, health);
		GetVehiclePos(vehicleID, posX, posY, posZ);
		GetVehicleZAngle(vehicleID, angle);
		
		if (asOriginalVehicle)
		{
			strcat(preSQL, "UPDATE `originalvehicles`");
		}
		else
		{
			strcat(preSQL, "UPDATE `vehicles`");
		}
		
		// Position
		MySQLQuery("%s SET `posX` = '%f', `posY` = '%f', `posZ` = '%f', `angle` = '%f', `interior` = '%d' WHERE `id` = '%d'", preSQL, posX, posY, posZ, angle, interior, VehicleProperty:vehicleID[SAVEID]);
		
		// Visual
		MySQLQuery("%s SET `color1` = '%d', `color2` = '%d', `paintjobId` = '%d', `frontLightId` = '%d', `neonLightId` = '%d' WHERE `id` = '%d'", preSQL, VehicleProperty:vehicleID[COLOR1], VehicleProperty:vehicleID[COLOR2], VehicleProperty:vehicleID[PAINTJOBID], VehicleProperty:vehicleID[FRONTLIGHTID], VehicleProperty:vehicleID[NEONLIGHTID], VehicleProperty:vehicleID[SAVEID]);
		
		// Other common properties (originalvehicles and vehicles)
		MySQLQuery("%s SET `health` = '%f', `mileAge` = '%f', `hasNavi` = '%d', `locked` = '%d', `price` = '%f' WHERE `id` = '%d'", preSQL, health, VehicleProperty:vehicleID[MILEAGE], VehicleProperty:vehicleID[HASNAVI], IsVehicleLocked(vehicleID), VehicleProperty:vehicleID[PRICE], VehicleProperty:vehicleID[SAVEID]);
		
		// Saved vehicles properties (Properties not available for originalvehicles)
		if (!asOriginalVehicle)
		{
			MySQLQuery("%s SET `currentFuel` = '%f', `sellerUserId` = '%d', `ownerUserId` = '%d', `radioStationId` = '%d' WHERE `id` = '%d'", preSQL, VehicleProperty:vehicleID[CURRENTFUEL], VehicleProperty:vehicleID[SELLERUSERID], VehicleProperty:vehicleID[OWNERUSERID], VehicleProperty:vehicleID[RADIOSTATIONID], VehicleProperty:vehicleID[SAVEID]);
		}
	}
}