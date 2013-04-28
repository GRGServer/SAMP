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
 */

SaveVehicle(vehicleID, interior)
{
	if (VehicleProperty:vehicleID[SAVEID])
	{
		new Float:health;
		new Float:posX; 
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetVehicleHealth(vehicleID, health);
		GetVehiclePos(vehicleID, posX, posY, posZ);
		GetVehicleZAngle(vehicleID, angle);

		Format:sqlQuery("UPDATE `vehicles` SET");

		// Position
		Format:sqlQuery("%s `posX` = '%f', `posY` = '%f', `posZ` = '%f', `angle` = '%f', `interior` = '%d',", sqlQuery, posX, posY, posZ, angle, interior);

		// Visual
		Format:sqlQuery("%s `color1` = '%d', `color2` = '%d', `paintjobId` = '%d', `frontLightId` = '%d', `neonLightId` = '%d',", sqlQuery, VehicleProperty:vehicleID[COLOR1], VehicleProperty:vehicleID[COLOR2], VehicleProperty:vehicleID[PAINTJOBID], VehicleProperty:vehicleID[FRONTLIGHTID], VehicleProperty:vehicleID[NEONLIGHTID]);

		// Other properties
		Format:sqlQuery("%s `health` = '%f', `mileAge` = '%f', `hasNavi` = '%d', `locked` = '%d', `price` = '%f',", sqlQuery, health, VehicleProperty:vehicleID[MILEAGE], VehicleProperty:vehicleID[HASNAVI], IsVehicleLocked(vehicleID), VehicleProperty:vehicleID[PRICE]);
		Format:sqlQuery("%s `currentFuel` = '%f', `sellerUserId` = '%d', `ownerUserId` = '%d', `radioStationId` = '%d'", sqlQuery, VehicleProperty:vehicleID[CURRENTFUEL], VehicleProperty:vehicleID[SELLERUSERID], VehicleProperty:vehicleID[OWNERUSERID], VehicleProperty:vehicleID[RADIOSTATIONID]);

		MySQLQuery(sqlQuery);
	}
}