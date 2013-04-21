/*
 * <summary>
 *	Set the state of a progress bar and change the color if the value is bellow the warning or critical value
 *	If the new value is above the warning value COLOR_BAR_OK will be used as color
 *	If the new value is above the critical value but bellow or equal to the warning value COLOR_BAR_WARNING will be used as color
 *	If the new value is bellow or equal to the critical value COLOR_BAR_CRITICAL will be used as color
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 *
 * <param name="barId">
 *	The ID of the progress bar (Return value of CreatePlayerProgressBar)
 * </param>
 *
 * <param name="warningValue">
 *	The warning value
 * </param>
 *
 * <param name="criticalValue">
 *	The critical value
 * </param>
 *
 * <param name="value">
 *	The new value of the progress bar
 * </param>
 */

SetPlayerBar3ColorState(playerID, PlayerBar:barId, Float:warningValue, Float:criticalValue, Float:value)
{
	new color = COLOR_BAR_OK;
	if (value <= criticalValue)
	{
		color = COLOR_BAR_CRITICAL;
	}
	else
	{
		if (value <= warningValue)
		{
			color = COLOR_BAR_WARNING;
		}
	}

	SetPlayerProgressBarColor(playerID, barId, color);
	SetPlayerProgressBarValue(playerID, barId, value);
}