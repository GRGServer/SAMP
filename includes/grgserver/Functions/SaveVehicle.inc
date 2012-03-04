SaveVehicle(vehicleID, interior)
{
	if (vehicles[vehicleID][VEHICLE_SAVEID])
	{
		new Float:posX; 
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetVehiclePos(vehicleID, posX, posY, posZ);
		GetVehicleZAngle(vehicleID, angle);
		MySQLQuery("UPDATE `savedvehicles` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f', `Interior` = '%d', `CurrentFuel` = '%f' WHERE `ID` = '%d'", posX, posY, posZ, angle, interior, vehicles[vehicleID][VEHICLE_CURRENTFUEL], vehicles[vehicleID][VEHICLE_SAVEID]);
	}
}