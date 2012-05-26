/**
 * <summary>
 *	Gets the color combination for the given vehicle model ID.
 * </summary>
 *
 * <param name="modelID">
 *	The ID of the vehicle model.
 * </param>
 *
 * <param name="color1">
 *	The first color.
 * </param>
 *
 * <param name="color2">
 *	The second color.
 * </param>
 */

GetVehicleColor(modelID, &color1, &color2)
{
	if (modelID < 400 || modelID > 611)
	{
		return false;
	}
	new colors[10][16];
	new elements = explode(vehicleModels[modelID - 400][VEHICLEMODEL_COLORS], colors, '|');
	new color3;// Not used in SA-MP
	new color4;// Not used in SA-MP
	if (sscanf(colors[random(elements)], "p,dddd", color1, color2, color3, color4))
	{
		if (sscanf(colors[random(elements)], "p,dd", color1, color2))
		{
			return false;
		}
	}
	return true;
}