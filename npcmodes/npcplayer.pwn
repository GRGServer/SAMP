#include <a_npc>
#include <sscanf>
#include <grgserver/config>

new recordingName[256];
new playbackType;
new autoRepeat;

public OnClientMessage(color, text[])
{
	/*
	Accepted content for "text":
	pause
	resume
	setrec <recordingName> <playbackType> <autoRepeat>
	start (<recordingName> <playbackType> <autoRepeat>)
	stop
	teleport <posX> <posY> <posZ> <angle>
	
	Command "start" without additional parameters will use the last recordingName, playbackType and autoRepeat state
	*/
	new command[16];
	new parameters[100];
	if (color != COLOR_NPCCOMMAND)
	{
		return false;
	}
	if (sscanf(text, "ss", command, parameters))
	{
		if (sscanf(text, "s", command))
		{
			return false;
		}
	}
	if (!strcmp(command, "pause", true))
	{
		PauseRecordingPlayback();
		return true;
	}
	if (!strcmp(command, "resume", true))
	{
		ResumeRecordingPlayback();
		return true;
	}
	if (!strcmp(command, "setrec", true))
	{
		sscanf(parameters, "sdd", recordingName, playbackType, autoRepeat);
		return true;
	}
	if (!strcmp(command, "start", true))
	{
		new recordingName2[256];
		new playbackType2;
		new autoRepeat2;
		sscanf(parameters, "sdd", recordingName2, playbackType2, autoRepeat2);
		if (strlen(recordingName2))
		{
			recordingName = recordingName2;
			playbackType = playbackType2;
			autoRepeat = autoRepeat2;
		}
		StartRecordingPlayback(playbackType, recordingName);
		return true;
	}
	if (!strcmp(command, "stop", true))
	{
		StopRecordingPlayback();
		return true;
	}
	if (!strcmp(command, "teleport", true))
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		if (sscanf(parameters, "ffff", posX, posY, posZ, angle))
		{
			sscanf(parameters, "fff", posX, posY, posZ);
		}
		if (posX && posY && posZ)
		{
			SetMyPos(posX, posY, posZ);
			SetMyFacingAngle(angle);
		}
		return true;
	}
	return false;
}

public OnRecordingPlaybackEnd()
{
	if (autoRepeat)
	{
		StartRecordingPlayback(playbackType, recordingName);
	}
	else
	{
		SendCommand("/npccmd stopped");
	}
}