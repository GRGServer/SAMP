StartNPCPlayback(npcPlayerID, recordingName[], recordingType, autoRepeat)
{
	new string[256];
	Format:string("%s %d %d", recordingName, recordingType, autoRepeat);
	SendClientMessage(npcPlayerID, COLOR_NPCCOMMAND, string);
}