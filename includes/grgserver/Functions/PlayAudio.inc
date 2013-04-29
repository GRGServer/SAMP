PlayAudio(playerID, file[])
{
	new url[200];
	strcat(url, AUDIO_BASE_URL);
	strcat(url, file);
	PlayAudioStreamForPlayer(playerID, url);
}