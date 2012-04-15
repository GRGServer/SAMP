Timer:ScreenFader(playerID, red, green, blue, steps, waitOnEnd, extraID)
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
		CallLocalFunction("OnScreenFadeStop", "ddd", playerID, extraID, false);
		if (waitOnEnd)
		{
			SetTimerEx("OnScreenFadeStop", waitOnEnd, false, "ddd", playerID, extraID, true);
		}
	}
	else
	{
		SetTimerEx("Timer_ScreenFader", TIMER_SCREENFADER, false, "ddddddd", playerID, red, green, blue, steps, waitOnEnd, extraID);
	}
}