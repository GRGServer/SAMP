/**
 * <summary>
 *	Timer to reset the last pickup (LASTPICKUP PVar) after some time
 * </summary>
 */

Timer:PickupTimeout(playerID)
{
	PVar:playerID[LASTPICKUP] = 0;
}