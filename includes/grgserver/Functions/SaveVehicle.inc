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
		MySQLQuery("UPDATE `savedvehicles` SET `Health` = '%f', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f', `Interior` = '%d', `MileAge` = '%f', `CurrentFuel` = '%f', `HasNavi` = '%d' WHERE `ID` = '%d'", health, posX, posY, posZ, angle, interior, VehicleProperty:vehicleID[CURRENTFUEL], VehicleProperty:vehicleID[MILEAGE], VehicleProperty:vehicleID[HASNAVI], VehicleProperty:vehicleID[SAVEID]);
	}
}