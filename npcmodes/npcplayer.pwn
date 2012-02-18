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
	<recordingName> <playbackType> <autoRepeat>
	stop
	pause
	resume
	*/
	if (color == COLOR_NPCCOMMAND)
	{
		if (!sscanf(text, "sdd", recordingName, playbackType, autoRepeat))
		{
			StartRecordingPlayback(playbackType, recordingName);
		}
		else
		{
			new command[256];
			if (!sscanf(text, "s", command))
			{
				if (!strcmp(command, "stop", true))
				{
					StopRecordingPlayback();
				}
				if (!strcmp(command, "pause", true))
				{
					PauseRecordingPlayback();
				}
				if (!strcmp(command, "resume", true))
				{
					ResumeRecordingPlayback();
				}
			}
			else
			{
				printf("Incorrect command format sent by server: %s", text);
			}
		}
	}
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

public OnNPCEnterVehicle(vehicleid,seatid)
{
	if (playbackType == PLAYER_RECORDING_TYPE_DRIVER)
	{
		StartRecordingPlayback(playbackType, recordingName);
	}
}

public OnNPCExitVehicle()
{
	if (playbackType == PLAYER_RECORDING_TYPE_DRIVER)
	{
		StopRecordingPlayback();
	}
}