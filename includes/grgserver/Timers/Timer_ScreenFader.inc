/**
 * <summary>
 *	Fade the screen to a specific color (Or back to normal)
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 *
 * <param name="red">
 *	The amount of red color (0 - 255)
 * </param>
 *
 * <param name="green">
 *	The amount of green color (0 - 255)
 * </param>
 *
 * <param name="blue">
 *	The amount of blue color (0 - 255)
 * </param>
 *
 * <param name="steps">
 *	The number of color steps in the time defined in TIMER_SCREENFADER
 * </param>
 *
 * <param name="waitOnEnd">
 *	Time in milliseconds to wait after the screen fading has finished
 *	OnScreenFadeStop will be triggered twice (Directly after the screen fading and after the timer has expired)
 * </param>
 *
 * <param name="extraID">
 *	An ID to identify the screen fade
 * </param>
 *
 * <param name="subID">
 *	A second ID to identify a screen fade in a group (e.g. to use Normal -> Black and Black -> Normal in the same extraID but different subIDs)
 * </param>
 */

Timer:ScreenFader(playerID, red, green, blue, steps, waitOnEnd, extraID, subID)
{
	new alpha;
	PVar:playerID[SCREENFADE_CURRENTSTEP] += steps;
	if (steps < 0)
	{
		alpha = 255 + PVar:playerID[SCREENFADE_CURRENTSTEP];
	}
	else
	{
		alpha = PVar:playerID[SCREENFADE_CURRENTSTEP];
	}
	if (alpha < 0)
	{
		alpha = 0;
	}
	if (alpha > 255)
	{
		alpha = 255;
	}
	PlayerTextDrawBoxColor(playerID, PTextDraw:playerID[SCREENFADER], GetColor(red, green, blue, alpha));
	PlayerTextDrawShow(playerID, PTextDraw:playerID[SCREENFADER]);
	if ((steps < 0 && !alpha) || (steps > 0 && alpha == 255))
	{
		PVar:playerID[SCREENFADE_CURRENTSTEP] = 0;
		CallLocalFunction("OnScreenFadeStop", "dddd", playerID, extraID, subID, false);
		if (waitOnEnd)
		{
			SetTimerEx("OnScreenFadeStop", waitOnEnd, false, "dddd", playerID, extraID, subID, true);
		}
	}
	else
	{
		SetTimerEx("Timer_ScreenFader", TIMER_SCREENFADER, false, "dddddddd", playerID, red, green, blue, steps, waitOnEnd, extraID, subID);
	}
}