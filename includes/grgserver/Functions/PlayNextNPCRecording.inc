/**
 * <summary>
 *	Play the next MultiRec NPC recording or play the first one if the last has been played and auto repeat is enabled.
 * </summary>
 *
 * <param name="playerID">
 *	The PlayerID of the NPC which should play the recording.
 * </param>
 *
 * <returns>
 *	<item name="true">The playback of the recording has been started</item>
 *	<item name="false">The playback of the recording failed (e.g. There are no more recordings to play and auto repeat is disabled)</item>
 * </returns>
 */

PlayNextNPCRecording(playerID)
{
	PVar:playerID[NPC_RECORDINGSLOT]++;
	new slot = PVar:playerID[NPC_RECORDINGSLOT];
	if (slot <= MAX_NPC_MULTIRECS)
	{
		new id = PVar:playerID[NPC_RECORDINGS][slot - 1];
		if (id)
		{
			MySQLQuery("SELECT * FROM `npcmultirecs` WHERE `id` = '%d'", id);
			mysql_store_result();
			FormatNew:command[40]("setrec %s %d 0 1", GetMySQLField("recording"), PVar:playerID[NPC_RECORDINGTYPE]);
			mysql_free_result();
			SendNPCCommand(playerID, command);
			return true;
		}
		if (slot > 1 && PVar:playerID[NPC_AUTOREPEAT])
		{
			PVar:playerID[NPC_RECORDINGSLOT] = 0;
			return PlayNextNPCRecording(playerID);
		}
	}
	return false;
}