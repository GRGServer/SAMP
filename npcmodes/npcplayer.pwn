#include <a_npc>
#include <sscanf_old>
#include <grgserver/config>

new recordingName[256];
new playbackType;
new plabackTimer;
new autoRepeat;
new startTime;

public OnClientMessage(color, text[])
{
	/*
	Accepted content for "text":
	pause
	resume
	setrec <recordingName> <playbackType> <autoRepeat> <startNow> <startDelay>
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
		new startNow;
		new startDelay;
		if (sscanf(parameters, "sdddd", recordingName, playbackType, autoRepeat, startNow, startDelay))
		{
			if (sscanf(parameters, "sddd", recordingName, playbackType, autoRepeat, startNow))
			{
				sscanf(parameters, "sdd", recordingName, playbackType, autoRepeat);
			}
		}
		if (startNow)
		{
			if (plabackTimer)
			{
				KillTimer(plabackTimer);
			}
			plabackTimer = SetTimer("StartRecordingPlaybackTimer", startDelay, false);
		}
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
		startTime = gettime();
		return true;
	}
	if (!strcmp(command, "stop", true))
	{
		StopRecordingPlayback();
		format(command, sizeof(command), "/npccmd reclength %d", gettime() - startTime);
		SendCommand(command);
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
		if (posX || posY || posZ)
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
	new command[50];
	format(command, sizeof(command), "/npccmd reclength %d", gettime() - startTime);
	SendCommand(command);
	if (autoRepeat)
	{
		StartRecordingPlayback(playbackType, recordingName);
		startTime = gettime();
	}
	else
	{
		SendCommand("/npccmd stopped");
	}
}

forward StartRecordingPlaybackTimer();
public StartRecordingPlaybackTimer()
{
	StartRecordingPlayback(playbackType, recordingName);
	startTime = gettime();
}