/**
 * <summary>
 *	Get the language string ID of the specified license type.
 * </summary>
 *
 * <param name="type">
 *	The license type string
 * </param>
 *
 * <returns>
 *	<item>The language string ID if the license type is valid</item>
 *	<item>0 if the license type is invalid</item>
 * </returns>
 */

LicenseLanguageStringID(type[])
{
	if (IsStr(type, "Bike"))
	{
		return 533;
	}
	if (IsStr(type, "Boat"))
	{
		return 534;
	}
	if (IsStr(type, "Car"))
	{
		return 530;
	}
	if (IsStr(type, "Helicopter"))
	{
		return 542;
	}
	if (IsStr(type, "Plane"))
	{
		return 531;
	}
	if (IsStr(type, "Train"))
	{
		return 543;
	}
	if (IsStr(type, "Truck"))
	{
		return 532;
	}
	return 0;
}