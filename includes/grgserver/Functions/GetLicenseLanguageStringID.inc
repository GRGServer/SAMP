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
		languageStringID = StringID:533("");
	}
	if (IsStr(type, "Boat"))
	{
		languageStringID = StringID:534("");
	}
	if (IsStr(type, "Car"))
	{
		languageStringID = StringID:530("");
	}
	if (IsStr(type, "Helicopter"))
	{
		languageStringID = StringID:542("");
	}
	if (IsStr(type, "Plane"))
	{
		languageStringID = StringID:531("");
	}
	if (IsStr(type, "Train"))
	{
		languageStringID = StringID:543("");
	}
	if (IsStr(type, "Truck"))
	{
		languageStringID = StringID:532("");
	}

	return languageStringID;
}