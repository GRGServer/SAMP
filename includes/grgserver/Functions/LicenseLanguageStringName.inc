/**
 * <summary>
 *	Get the language string name of the specified license type.
 * </summary>
 *
 * <param name="type">
 *	The license type string
 * </param>
 *
 * <returns>
 *	The language string name of the license type
 * </returns>
 */

LicenseLanguageStringName(type[])
{
	new languageStringName[STRINGLENGTH_LANGUAGESTRINGNAME];

	if (IsStr(type, "Bike"))
	{
		languageStringName = "LICENSE_BIKE";
	}
	if (IsStr(type, "Boat"))
	{
		languageStringName = "LICENSE_BOAT";
	}
	if (IsStr(type, "Car"))
	{
		languageStringName = "LICENSE_CAR";
	}
	if (IsStr(type, "Helicopter"))
	{
		languageStringName = "LICENSE_HELICOPTER";
	}
	if (IsStr(type, "Plane"))
	{
		languageStringName = "LICENSE_PLANE";
	}
	if (IsStr(type, "Train"))
	{
		languageStringName = "LICENSE_TRAIN";
	}
	if (IsStr(type, "Truck"))
	{
		languageStringName = "LICENSE_TRUCK";
	}

	return languageStringName;
}