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
		Format:sqlQuery("UPDATE `vehicles` SET `Health` = '%f', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f', `Interior` = '%d'", health, posX, posY, posZ, angle, interior);
		MySQLQuery("%s, `MileAge` = '%f', `CurrentFuel` = '%f', `FrontLightID` = '%d', `NeonLightID` = '%d', `HasNavi` = '%d' WHERE `ID` = '%d'", sqlQuery, VehicleProperty:vehicleID[MILEAGE], VehicleProperty:vehicleID[CURRENTFUEL], VehicleProperty:vehicleID[FRONTLIGHTID], VehicleProperty:vehicleID[NEONLIGHTID], VehicleProperty:vehicleID[HASNAVI], VehicleProperty:vehicleID[SAVEID]);
	}
}