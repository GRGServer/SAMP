/**
 * <summary>
 *	This timer gets executed every minute.
 *	Tasks like saving all currently logged in players were executed in this timer.
 * </summary>
 */

Timer:EveryMinute()
{
	LoggedInPlayers(playerID)
	{
		SavePlayer(playerID);
	}
}