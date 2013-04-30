PlayAudio(playerID, file[])
{
	new url[200];
	strcat(url, file);
	PlayAudioStreamForPlayer(playerID, url);
}