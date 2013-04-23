/**
 * <summary>
 *	Get the name of the specified language ID
 * </summary>
 *
 * <param name="id">
 *	The ID of the language
 * </param>
 *
 * <returns>
 *	The name of the language (e.g. "de" or "en")
 * </returns>
 */

GetLanguageName(id)
{
	new name[3];
	switch (id)
	{
		case LANGUAGE_GERMAN:
			name= "de";
		default:
			name = "en";
	}
	return name;
}