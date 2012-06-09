SaveVehicle(vehicleID, interior)
{
	if (VehicleProperty:vehicleID[SAVEID] && VehicleProperty:vehicleID[ALLOWSAVE])
	{
		new Float:health;
		new Float:posX; 
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetVehicleHealth(vehicleID, health);
		GetVehiclePos(vehicleID, posX, posY, posZ);
		GetVehicleZAngle(vehicleID, angle);
		Format:sqlQuery("UPDATE `vehicles` SET `health` = '%f', `posX` = '%f', `posY` = '%f', `posZ` = '%f', `angle` = '%f', `interior` = '%d', `locked` = '%d'", health, posX, posY, posZ, angle, interior, IsVehicleLocked(vehicleID));
		MySQLQuery("%s, `mileAge` = '%f', `currentFuel` = '%f', `frontLightId` = '%d', `neonLightId` = '%d', `hasNavi` = '%d' WHERE `id` = '%d'", sqlQuery, VehicleProperty:vehicleID[MILEAGE], VehicleProperty:vehicleID[CURRENTFUEL], VehicleProperty:vehicleID[FRONTLIGHTID], VehicleProperty:vehicleID[NEONLIGHTID], VehicleProperty:vehicleID[HASNAVI], VehicleProperty:vehicleID[SAVEID]);
	}
}