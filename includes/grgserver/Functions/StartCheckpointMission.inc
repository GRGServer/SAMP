/**
 * <summary>
 *	Start a specific checkpoint mission.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 *
 * <param name="missionID">
 *	The ID of the mission
 * </param>
 *
 * <param name="vehicleID">
 *	Only allow the player to enter the checkpoints using this vehicle.
 *	Set to 0 to allow with any vehicle.
 *	Set to -1 to allow without a vehicle.
 * </param>
 */

StartCheckpointMission(playerID, missionID, vehicleID = -1)
{
	PVar:playerID[CPMISSION_ID] = missionID;
	PVar:playerID[CPMISSION_VEHICLEID] = vehicleID;
	NextMissionCheckpoint(playerID);
}