SaveVehicle(vehicleID, interior)
{
	if (vehicles[vehicleID][VEHICLE_SAVEID])
	{
		new Float:health;
		new Float:posX; 
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetVehicleHealth(vehicleID, health);
		GetVehiclePos(vehicleID, posX, posY, posZ);
		GetVehicleZAngle(vehicleID, angle);
		MySQLQuery("UPDATE `savedvehicles` SET `Health` = '%f', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f', `Interior` = '%d', `MileAge` = '%f', `CurrentFuel` = '%f' WHERE `ID` = '%d'", health, posX, posY, posZ, angle, interior, vehicles[vehicleID][VEHICLE_CURRENTFUEL], vehicles[vehicleID][VEHICLE_MILEAGE], vehicles[vehicleID][VEHICLE_SAVEID]);
	}
}