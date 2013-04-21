/**
 * <summary>
 *	This timer runs while a player is pissing
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 */

Timer:Pee(playerID)
{
	PVar:playerID[NEEDS_BLADDER] = PVar:playerID[NEEDS_BLADDER] + 2;
	UpdatePlayerNeeds(playerID);
	if (PVar:playerID[NEEDS_BLADDER] >= 100)
	{
		PVar:playerID[NEEDS_BLADDER] = 100;
		PlayerPee(playerID, false);
	}
}