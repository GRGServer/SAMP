/**
 * <summary>
 *	Checks if the given model ID is a gate object which can be opened using /opengate.
 * </summary>
 *
 * <param name="modelID">
 *	The model ID of the object
 * </param>
 *
 * <returns>
 *	<item>true if the model ID is a valid gate object</item>
 *	<item>false if the model ID is not a gate object</item>
 * </returns>
 */

IsGateObject(modelID)
{
	switch (modelID)
	{
		case 968:
			return true;
		case 969:
			return true;
		case 980:
			return true;
	}
	return false;
}