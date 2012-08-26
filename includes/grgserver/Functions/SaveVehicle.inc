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
		Format:sqlQuery("UPDATE `vehicles` SET `health` = '%f', `mileAge` = '%f', `currentFuel` = '%f', `locked` = '%d'", health, VehicleProperty:vehicleID[MILEAGE], VehicleProperty:vehicleID[CURRENTFUEL], IsVehicleLocked(vehicleID));
		MySQLQuery("%s, `frontLightId` = '%d', `neonLightId` = '%d', `hasNavi` = '%d' WHERE `id` = '%d'", sqlQuery, VehicleProperty:vehicleID[FRONTLIGHTID], VehicleProperty:vehicleID[NEONLIGHTID], VehicleProperty:vehicleID[HASNAVI], VehicleProperty:vehicleID[SAVEID]);
		if (VehicleProperty:vehicleID[ALLOWPOSSAVE])
		{
			MySQLQuery("UPDATE `vehicles` SET `posX` = '%f', `posY` = '%f', `posZ` = '%f', `angle` = '%f', `interior` = '%d' WHERE `id` = '%d'", posX, posY, posZ, angle, interior, VehicleProperty:vehicleID[SAVEID]);
		}
	}
}