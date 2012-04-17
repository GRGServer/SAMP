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
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:angle;
	if (color != COLOR_NPCCOMMAND)
	{
		return false;
	}
	if (sscanf(text, "ssdd", command, recordingName, playbackType, autoRepeat))
	{
		if (sscanf(text, "sffff", command, posX, posY, posZ, angle))
		{
			if (sscanf(text, "s", command))
			{
				return false;
			}
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
	if (!strcmp(command, "setrec", true))// Only sets recordingName, playbackType and autoRepeat (For later use of "start" without additional parameters)
	{
		return true;
	}
	if (!strcmp(command, "start", true))
	{
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