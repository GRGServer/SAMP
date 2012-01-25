#include <a_npc>

new NPCID;
//new IsPaused;
new Float:Distance;

//forward Timer();

main(){}

public OnNPCModeInit()
{
    #if RecordType==PLAYER_RECORDING_TYPE_DRIVER
		Distance=10.0;
	#endif
	#if RecordType==PLAYER_RECORDING_TYPE_ONFOOT
		Distance=5.0;
	#endif
	//SetTimer("Timer",1,true);
}

public OnNPCConnect(myplayerid)
{
	NPCID=myplayerid;
}

/*public Timer()
{
	new InRange;
	for (new PlayerID=0;PlayerID<MAX_PLAYERS;PlayerID++)
	{
	    if (IsPlayerConnected(PlayerID))
	    {
	        new Float:X;
	        new Float:Y;
	        new Float:Z;
	        GetMyPos(X,Y,Z);
	        if (IsPlayerInRangeOfPoint(PlayerID,Distance,X,Y,Z))
			{
			    if (GetPlayerVehicleID(PlayerID)!=GetPlayerVehicleID(NPCID))
			    {
			    	InRange=true;
				}
			}
		}
	}
	if (InRange)
	{
	    if (!IsPaused)
	    {
	        IsPaused=true;
		    PauseRecordingPlayback();
		}
	}
	else
	{
	    if (IsPaused)
	    {
	        IsPaused=false;
	    	ResumeRecordingPlayback();
		}
	}
}*/

public OnRecordingPlaybackEnd()
{
	Play();
}

#if RecordType==PLAYER_RECORDING_TYPE_DRIVER
	public OnNPCEnterVehicle(vehicleid,seatid)
	{
		Play();
	}
	public OnNPCExitVehicle()
	{
		StopRecordingPlayback();
	}
#endif
#if RecordType==PLAYER_RECORDING_TYPE_ONFOOT
	public OnNPCSpawn()
	{
		Play();
	}
#endif

stock Play()
{
	StartRecordingPlayback(RecordType,RecordName);
}
