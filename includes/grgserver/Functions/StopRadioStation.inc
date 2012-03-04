StopRadioStation(playerID)
{
	StopAudioStreamForPlayer(playerID);
	TextDrawHideForPlayer(playerID, textDrawRadioStation[playerID]);
}