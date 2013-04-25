/**
 * <summary>
 *	Start or stop the engine of the current vehicle if the player has the permission and is the driver of the vehicle.
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
 *	<item>COMMAND_ERROR</item>
 *	<item>COMMAND_NOT_IN_VEHICLE</item>
 *	<item>COMMAND_OK</item>
 * </returns>
 */

CMD:engine(playerID, params[], StringID:111("Start or stop the engine of your vehicle"))
{
	if (!IsPlayerInAnyVehicle(playerID))
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (TogglePlayerVehicleEngine(playerID))
	{
		return COMMAND_OK;
	}
	return COMMAND_ERROR;
}