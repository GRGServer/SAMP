/**
 * <summary>
 *	Open the dialog for adding a navigation location (AddNaviLocation_Type).
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which called the command.
 * </param>
 *
 * <param name="params">
 *	The parameters passed to this command (Unused).
 * </param>
 *
 * <returns>
 *	Always returns COMMAND_OK.
 * </returns>
 */

PCMD:addnavilocation[NAVI](playerID, params[], StringID:380("Save you current location as navigation target"))
{
	ShowDialog:AddNaviLocation_Type(playerID);
	return COMMAND_OK;
}