#include <a_npc>
#include <sscanf>
#include <grgserver/config>

new recordingName[256];
new playbackType;
new autoRepeat;
new isPaused;
new isTimer;
new timer;

forward Timer();

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
			StartNPC();
		}
		else
		{
			new command[256];
			if (!sscanf(text, "s", command))
			{
				if (!strcmp(command, "stop", true))
				{
					StopNPC();
				}
				if (!strcmp(command, "pause", true))
				{
					StopTimer();
					PauseNPC(true);
				}
				if (!strcmp(command, "resume", true))
				{
					PauseNPC(true);
					StartTimer();
				}
			}
			else
			{
				printf("Incorrect command format sent by server: %s", text);
			}
		}
	}
}

public OnNPCEnterVehicle(vehicleid,seatid)
{
	if (playbackType == PLAYER_RECORDING_TYPE_DRIVER)
	{
		StartNPC();
	}
}

public OnNPCExitVehicle()
{
	if (playbackType == PLAYER_RECORDING_TYPE_DRIVER)
	{
		StopNPC();
	}
}

public OnRecordingPlaybackEnd()
{
	print("NPC playback ended");
	if (autoRepeat)
	{
		StartNPC();
	}
	else
	{
		SendCommand("/npccmd stopped");
	}
}

public Timer()
{
	new pause;
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new Float:distance;
		GetPlayerPos(playerID, posX, posY, posZ);
		GetDistanceFromMeToPoint(posX, posY, posZ, distance);
		if (distance <= NPC_PAUSEDISTANCE)
		{
			pause = true;
			break;
		}
	}
	if (pause)
	{
		if (!isPaused)
		{
			PauseNPC(true);
		}
	}
	else
	{
		if (isPaused)
		{
			PauseNPC(false);
		}
	}
}

PauseNPC(newState)
{
	if (newState)
	{
		isPaused = true;
		PauseRecordingPlayback();
		print("NPC playback paused");
	}
	else
	{
		isPaused = false;
		ResumeRecordingPlayback();
		print("NPC playback resumed");
	}
}

StartNPC()
{
	isPaused = false;
	StartRecordingPlayback(playbackType, recordingName);
	print("NPC playback started");
	StartTimer();
}

StartTimer()
{
	if (!isTimer)
	{
		print("Timer started");
		timer = SetTimer("Timer", 200, true);
		isTimer = true;
	}
}

StopNPC()
{
	StopRecordingPlayback();
	print("NPC playback stopped");
}

StopTimer()
{
	if (isTimer)
	{
		print("Timer stopped");
		KillTimer(timer);
		isTimer = false;
	}
}