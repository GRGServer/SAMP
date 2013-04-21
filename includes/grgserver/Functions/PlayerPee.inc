/**
 * <summary>
 *	Start or stop to peefor the specified player
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 *
 * <param name="newState">
 *	<title>The new state</title>
 *	<item name="true">Start peeing if not already done</item>
 *	<item name="false">Stop peeing if not already done</item>
 * </param>
 */

PlayerPee(playerID, newState)
{
	if (newState)
	{
		if (!PVar:playerID[PEE_TIMER])
		{
			PVar:playerID[PEE_TIMER] = SetTimerEx("Timer_Pee", TIMER_PEE, true, "d", playerID);
			SetPlayerSpecialAction(playerID, SPECIAL_ACTION_PISSING);
		}
	}
	else
	{
		if (PVar:playerID[PEE_TIMER])
		{
			KillTimer(PVar:playerID[PEE_TIMER]);
			PVar:playerID[PEE_TIMER] = 0;
		}
		SetPlayerSpecialAction(playerID, SPECIAL_ACTION_NONE);
	}
}