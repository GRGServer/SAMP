PlayAudio(playerID, file[])
{
	new url[200];
	strcat(url, "http://audio.grgserver.net/");
	strcat(url, file);
	PlayAudioStreamForPlayer(playerID, url);
}