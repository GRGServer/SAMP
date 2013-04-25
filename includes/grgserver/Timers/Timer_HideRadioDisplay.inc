/**
 * <summary>
 *	This timer hides the radio display.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 */

Timer:HideRadioDisplay(playerID)
{
	PlayerTextDrawHide(playerID, PTextDraw:playerID[RADIOSTATION]);
}