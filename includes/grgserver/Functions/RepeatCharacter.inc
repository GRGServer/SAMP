/**
 * <summary>
 *	Create a string from the given character with the given length
 * </summary>
 *
 * <param name="character">
 *	The character to use
 * </param>
 *
 * <param name="length">
 *	The string length
 *	The maximum length is 256
 * </param>
 *
 * <returns>
 *	The string containing the character repeated X times (specified using the length parameter)
 * </returns>
 */

RepeatCharacter(character, length)
{
	new string[256];
	Count(index, length)
	{
		string[index] = character;
	}
	return string;
}