/**
 * <summary>
 *	Called every 5 seconds for each connected player to update the player needs (bladder, hunger and thirst)
 *	This function also gets called while restoring the needs (e.g. while peeing or sleeping)
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 */

UpdatePlayerNeeds(playerID)
{
	PVar:playerID[NEEDS_BLADDER] = PVar:playerID[NEEDS_BLADDER] - NEEDS_BLADDER;
	PVar:playerID[NEEDS_ENERGY] = PVar:playerID[NEEDS_ENERGY] - NEEDS_ENERGY;
	PVar:playerID[NEEDS_HUNGER] = PVar:playerID[NEEDS_HUNGER] - NEEDS_HUNGER;
	PVar:playerID[NEEDS_THIRST] = PVar:playerID[NEEDS_THIRST] - NEEDS_THIRST;

	// Fix values which may be < 0
	if (PVar:playerID[NEEDS_BLADDER] <= 0)
	{
		PVar:playerID[NEEDS_BLADDER] = 0;
		SendClientMessageEx(playerID, COLOR_WARNING, StringID:632(""));
		PlayerPee(playerID, true);
	}
	if (PVar:playerID[NEEDS_ENERGY] <= 0)
	{
		PVar:playerID[NEEDS_ENERGY] = 0;
	}
	if (PVar:playerID[NEEDS_HUNGER] <= 0)
	{
		PVar:playerID[NEEDS_HUNGER] = 0;
	}
	if (PVar:playerID[NEEDS_THIRST] <= 0)
	{
		PVar:playerID[NEEDS_THIRST] = 0;
	}

	SetPlayerBar3ColorState(playerID, PVar:playerID[PROGRESSBAR_NEEDS_BLADDER], NEEDS_WARNING, NEEDS_CRITICAL, PVar:playerID[NEEDS_BLADDER]);
	SetPlayerBar3ColorState(playerID, PVar:playerID[PROGRESSBAR_NEEDS_ENERGY], NEEDS_WARNING, NEEDS_CRITICAL, PVar:playerID[NEEDS_ENERGY]);
	SetPlayerBar3ColorState(playerID, PVar:playerID[PROGRESSBAR_NEEDS_HUNGER], NEEDS_WARNING, NEEDS_CRITICAL, PVar:playerID[NEEDS_HUNGER]);
	SetPlayerBar3ColorState(playerID, PVar:playerID[PROGRESSBAR_NEEDS_THIRST], NEEDS_WARNING, NEEDS_CRITICAL, PVar:playerID[NEEDS_THIRST]);

	ShowPlayerProgressBar(playerID, PVar:playerID[PROGRESSBAR_NEEDS_BLADDER]);
	ShowPlayerProgressBar(playerID, PVar:playerID[PROGRESSBAR_NEEDS_ENERGY]);
	ShowPlayerProgressBar(playerID, PVar:playerID[PROGRESSBAR_NEEDS_HUNGER]);
	ShowPlayerProgressBar(playerID, PVar:playerID[PROGRESSBAR_NEEDS_THIRST]);

	PlayerTextDrawShow(playerID, PTextDraw:playerID[NEEDS_TEXT]);
}