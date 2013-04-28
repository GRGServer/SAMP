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

	new arrayIndex = modelID - 400;
	new maxColorIndex = -1;
	Count(colorIndex, MAX_VEHICLE_COLORS)
	{
		if (vehicleColors[arrayIndex][colorIndex][0] == -1 || vehicleColors[arrayIndex][colorIndex][1] == -1)
		{
			break;
		}
		maxColorIndex = colorIndex;
	}

	if (maxColorIndex < 0)
	{
		return false;
	}

	new randomColorIndex = random(maxColorIndex + 1);// random returns a value between 0 and max (Excluding the max value) -> maxColorIndex + 1 will return a value between 0 and maxColorIndex

	color1 = vehicleColors[arrayIndex][randomColorIndex][0];
	color2 = vehicleColors[arrayIndex][randomColorIndex][1];

	return true;
}