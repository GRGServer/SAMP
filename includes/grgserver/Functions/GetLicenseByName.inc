GetLicenseByName(licenseName[])
{
	if (!strcmp(licenseName, "Car", true))
	{
		return LICENSE_CAR;
	}
	if (!strcmp(licenseName, "Bike", true))
	{
		return LICENSE_BIKE;
	}
	if(!strcmp(licenseName, "Sailing", true))
	{
		return LICENSE_SAILING;
	}
	if(!strcmp(licenseName, "Fishing", true))
	{
		return LICENSE_FISHING;
	}
	if(!strcmp(licenseName, "Truck", true))
	{
		return LICENSE_TRUCK;
	}
	if(!strcmp(licenseName, "Weapon", true))
	{
		return LICENSE_WEAPON;
	}
	return -1;
}