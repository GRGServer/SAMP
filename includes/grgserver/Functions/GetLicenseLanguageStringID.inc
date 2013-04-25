/**
 * <summary>
 *	Get the language string ID of the specified license type.
 * </summary>
 *
 * <param name="type">
 *	The license type
 * </param>
 *
 * <returns>
 *	The language string ID of the license type
 * </returns>
 */

GetLicenseLanguageStringID(type[])
{
	new languageStringID;

	if (IsStr(type, "Bike"))
	{
		languageStringID = StringID:533("Bike driving license");
	}
	if (IsStr(type, "Boat"))
	{
		languageStringID = StringID:534("Sailing license");
	}
	if (IsStr(type, "Car"))
	{
		languageStringID = StringID:530("Car driving license");
	}
	if (IsStr(type, "Helicopter"))
	{
		languageStringID = StringID:542("Helicopter flying license");
	}
	if (IsStr(type, "Plane"))
	{
		languageStringID = StringID:531("Plane fly license");
	}
	if (IsStr(type, "Train"))
	{
		languageStringID = StringID:543("Train driving license");
	}
	if (IsStr(type, "Truck"))
	{
		languageStringID = StringID:532("Truck driving license");
	}

	return languageStringID;
}