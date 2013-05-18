/**
 * <summary>
 *	Connect an NPC
 * </summary>
 *
 * <param name="arrayIndex">
 *	Index in the npcs array
 * </param>
 */

Timer:ConnectNPC(arrayIndex)
{
	ConnectNPC(npcs[arrayIndex][NPC_NAME], NPC_SCRIPTNAME);
}