//Filterscript von SparY
//---------------
#include <a_samp>
//---------------
#define DIALOG_ID 345   // <-- Ändern falls bereits vorhanden!
#define COLOR_LIGHTBLUE 0x33CCFFAA
#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
//---------------
new Text:LIVE;
new Text:YOUFM;
new Text:YOUFM2;
new Text:YOUFM3;
new Text:YOUFM4;
new Text:RTL;
new Text:RADIOAUS;
new Text:radioplanet;
new Text:technobase;
new timer;
new sender[MAX_VEHICLES];
new gesperrt[MAX_PLAYERS];
//---------------
forward entftextdraw(playerid);
//---------------

public OnGameModeInit()
{
	LIVE=TextDrawCreate(290.0,10.0,"1LIVE");
	YOUFM=TextDrawCreate(270.0,10.0,"YouFM Live");
	YOUFM2=TextDrawCreate(265.0,10.0,"YouFM Rock");
	YOUFM3=TextDrawCreate(265.0,10.0,"YouFM Club");
	YOUFM4=TextDrawCreate(265.0,10.0,"YouFM Black");
	RTL=TextDrawCreate(282.0,10.0,"89.0 RTL");
	RADIOAUS=TextDrawCreate(270.0,10.0,"Radio aus");
	technobase=TextDrawCreate(265.0,10.0,"Technobase FM");
	radioplanet=TextDrawCreate(265.0,10.0,"Planet Radio");
	TextDrawSetShadow(LIVE,0);
	TextDrawSetShadow(YOUFM,0);
	TextDrawSetShadow(YOUFM2,0);
	TextDrawSetShadow(YOUFM3,0);
	TextDrawSetShadow(YOUFM4,0);
	TextDrawSetShadow(RTL,0);
	TextDrawSetShadow(RADIOAUS,0);
	TextDrawSetShadow(technobase,0);
	TextDrawSetShadow(radioplanet,0);
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (strcmp("/radio", cmdtext, true, 10) == 0)
	{
        if(IsPlayerInAnyVehicle(playerid))
        {
            new VID = GetPlayerVehicleID(playerid);
            if(sender[VID]==0)
            {
                sender[VID]=1;
				KillTimer(timer);
                entftextdraw(playerid);
                gesperrt[playerid]=1;
				PlayAudioStreamForPlayer(playerid, "http://gffstream.ic.llnwd.net/stream/gffstream_stream_wdr_einslive_a");//1LIVE
				SendClientMessage(playerid,COLOR_LIGHTBLUE,"Du kannst nun mit der NUM8 u. NUM2 Taste den Radiosender ändern! Radio ausschalten: /radio");
				timer = TextDrawShowForPlayer(playerid,LIVE);
				timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
			}
			else
			{
				sender[VID]=0;
				KillTimer(timer);
                entftextdraw(playerid);
				TextDrawShowForPlayer(playerid,RADIOAUS);
				StopAudioStreamForPlayer(playerid);
				timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
			}
		}
		return 1;
	}
	else if (strcmp("/dradio", cmdtext, true, 10) == 0)
	{
        if(IsPlayerInAnyVehicle(playerid))
        {
            if(gesperrt[playerid]!=1)
            {
	    		ShowPlayerDialog(playerid,DIALOG_ID,DIALOG_STYLE_LIST,"Wähle einen Sender","1LIVE\nYouFM ->\n89.0 RTL\nPlanet Radio\nTechnoBase FM\n{FF0000}Radio aus","Auswählen", "Abbrechen");
			}
			else
			{
			    SendClientMessage(playerid,0xFF0000FF,"Um Bugs zu vermeiden ist der Command für 3 Sekunden gesperrt!");
			}
		}
	}
	return 0;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    new VID = GetPlayerVehicleID(playerid);
	if(response)
	{
	    if(dialogid == DIALOG_ID)
	    {
			switch(listitem)
			{
				case 0:
				{
					KillTimer(timer);
     				entftextdraw(playerid);
         			gesperrt[playerid]=1;
	    			sender[VID]=1;
				    StopAudioStreamForPlayer(playerid);
				    PlayAudioStreamForPlayer(playerid, "http://gffstream.ic.llnwd.net/stream/gffstream_stream_wdr_einslive_a");//1LIVE
				    TextDrawShowForPlayer(playerid,LIVE);
					timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
				}
				case 1:
				{
				    ShowPlayerDialog(playerid,DIALOG_ID+1,DIALOG_STYLE_LIST,"Wähle einen Sender","YouFM Live\nYouFM Rock\nYouFM Club\nYouFM Black\n{FF0000}<- Zurück","Auswählen", "Abbrechen");
				}
				case 2:
				{
					KillTimer(timer);
	                entftextdraw(playerid);
	                gesperrt[playerid]=1;
				    sender[VID]=6;
	   				StopAudioStreamForPlayer(playerid);
		    		TextDrawShowForPlayer(playerid,RTL);
					timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
					PlayAudioStreamForPlayer(playerid, "http://mp3.89.0rtl.de/listen.pls"); // 89.0 RTL
				}
				case 3:
				{
				    sender[VID]=7;
					KillTimer(timer);
				   	entftextdraw(playerid);
				   	gesperrt[playerid]=1;
				    StopAudioStreamForPlayer(playerid);
				    PlayAudioStreamForPlayer(playerid, "http://streams.planetradio.de/planetradio/mp3/hqlivestream.m3u"); // Planet Radio
				    TextDrawShowForPlayer(playerid,radioplanet);
					timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
				}
				case 4:
				{
					KillTimer(timer);
	                entftextdraw(playerid);
	                gesperrt[playerid]=1;
	       			sender[VID]=8;
		    		StopAudioStreamForPlayer(playerid);
		    		TextDrawShowForPlayer(playerid,technobase);
					timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
					PlayAudioStreamForPlayer(playerid, "http://listen.technobase.fm/dsl.pls"); // Technobase
				}
				case 5:
				{
					sender[VID]=0;
					KillTimer(timer);
	                entftextdraw(playerid);
					TextDrawShowForPlayer(playerid,RADIOAUS);
					StopAudioStreamForPlayer(playerid);
					timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
				}
			}
		}
		if(dialogid == DIALOG_ID+1)
		{
		    switch(listitem)
		    {
		        case 0:
		        {
					KillTimer(timer);
      				entftextdraw(playerid);
	               	gesperrt[playerid]=1;
				    sender[VID]=2;
				    StopAudioStreamForPlayer(playerid);
				    TextDrawShowForPlayer(playerid,YOUFM);
					timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
					PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_2.m3u");//YOU FM LIVE
				}
				case 1:
				{
					KillTimer(timer);
			        entftextdraw(playerid);
			        gesperrt[playerid]=1;
				    sender[VID]=3;
				    StopAudioStreamForPlayer(playerid);
				    TextDrawShowForPlayer(playerid,YOUFM2);
					timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
					PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_rock.m3u"); // YOU FM ROCK
				}
				case 2:
				{
					KillTimer(timer);
	                entftextdraw(playerid);
	                gesperrt[playerid]=1;
				    sender[VID]=4;
				    StopAudioStreamForPlayer(playerid);
				    TextDrawShowForPlayer(playerid,YOUFM3);
					timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
					PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_club.m3u"); // YOU FM CLUB
				}
				case 3:
				{
					KillTimer(timer);
     				entftextdraw(playerid);
         			gesperrt[playerid]=1;
	    			sender[VID]=5;
			    	StopAudioStreamForPlayer(playerid);
			    	TextDrawShowForPlayer(playerid,YOUFM4);
					timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
					PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_black.m3u"); // YOU FM BLACK
				}
				case 4:
				{
					ShowPlayerDialog(playerid,DIALOG_ID,DIALOG_STYLE_LIST,"Wähle einen Sender","1LIVE\nYouFM ->\n89.0 RTL\nPlanet Radio\nTechnoBase FM\n{FF0000}Radio aus","Auswählen", "Abbrechen");
				}
			}
		}
	}
	return 0;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	switch(sender[vehicleid])
	{
		case 0:
		{
			KillTimer(timer);
   			entftextdraw(playerid);
		    TextDrawShowForPlayer(playerid,RADIOAUS);
			timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		    StopAudioStreamForPlayer(playerid);
			SendClientMessage(playerid,COLOR_LIGHTBLUE,"Tippe /radio um das Radio einzuschalten!");
		}
		case 1:
		{
			KillTimer(timer);
   			entftextdraw(playerid);
   			gesperrt[playerid]=1;
		    StopAudioStreamForPlayer(playerid);
		    PlayAudioStreamForPlayer(playerid, "http://gffstream.ic.llnwd.net/stream/gffstream_stream_wdr_einslive_a");//1LIVE
		    TextDrawShowForPlayer(playerid,LIVE);
			timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 2:
		{
			KillTimer(timer);
   			entftextdraw(playerid);
   			gesperrt[playerid]=1;
		    StopAudioStreamForPlayer(playerid);
		    PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_2.m3u");//YOU FM LIVE
		    TextDrawShowForPlayer(playerid,YOUFM);
			timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 3:
		{
			KillTimer(timer);
    		entftextdraw(playerid);
    		gesperrt[playerid]=1;
		    StopAudioStreamForPlayer(playerid);
		    PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_rock.m3u"); // YOU FM ROCK
		    TextDrawShowForPlayer(playerid,YOUFM2);
			timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 4:
		{
			KillTimer(timer);
   			entftextdraw(playerid);
   			gesperrt[playerid]=1;
		    StopAudioStreamForPlayer(playerid);
		    PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_club.m3u"); // YOU FM CLUB
		    TextDrawShowForPlayer(playerid,YOUFM3);
			timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 5:
		{
			KillTimer(timer);
   			entftextdraw(playerid);
   			gesperrt[playerid]=1;
		    StopAudioStreamForPlayer(playerid);
		    PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_black.m3u"); // YOU FM BLACK
		    TextDrawShowForPlayer(playerid,YOUFM4);
			timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 6:
		{
			KillTimer(timer);
   			entftextdraw(playerid);
   			gesperrt[playerid]=1;
		    StopAudioStreamForPlayer(playerid);
		    PlayAudioStreamForPlayer(playerid, "http://mp3.89.0rtl.de/listen.pls"); // 89.0 RTL
		    TextDrawShowForPlayer(playerid,RTL);
			timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 7:
		{
			KillTimer(timer);
   			entftextdraw(playerid);
   			gesperrt[playerid]=1;
		    StopAudioStreamForPlayer(playerid);
		    PlayAudioStreamForPlayer(playerid, "http://streams.planetradio.de/planetradio/mp3/hqlivestream.m3u"); // Planet Radio
		    TextDrawShowForPlayer(playerid,radioplanet);
			timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 8:
		{
			KillTimer(timer);
   			entftextdraw(playerid);
   			gesperrt[playerid]=1;
		    StopAudioStreamForPlayer(playerid);
		    PlayAudioStreamForPlayer(playerid, "http://listen.technobase.fm/dsl.pls"); // TechnoBase
		    TextDrawShowForPlayer(playerid,technobase);
			timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
	}
	return 0;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
    StopAudioStreamForPlayer(playerid);
	return 0;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new VID = GetPlayerVehicleID(playerid);
	if(IsPlayerInAnyVehicle(playerid))
	{
	    if(sender[VID]!=0)
	    {
			if(PRESSED(KEY_ANALOG_UP))
			{
   				if(gesperrt[playerid]!=1)
				{
					switch(sender[VID])
					{
					    case 1:
					    {
							KillTimer(timer);
			                entftextdraw(playerid);
			                gesperrt[playerid]=1;
						    sender[VID]=8;
		    				StopAudioStreamForPlayer(playerid);
		    				TextDrawShowForPlayer(playerid,technobase);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://listen.technobase.fm/dsl.pls"); // Technobase
						}
						case 2:
						{
							KillTimer(timer);
			                entftextdraw(playerid);
			                gesperrt[playerid]=1;
						    sender[VID]=1;
						    StopAudioStreamForPlayer(playerid);
						    TextDrawShowForPlayer(playerid,LIVE);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://gffstream.ic.llnwd.net/stream/gffstream_stream_wdr_einslive_a");//1LIVE
						}
						case 3:
						{
							KillTimer(timer);
			                entftextdraw(playerid);
			                gesperrt[playerid]=1;
						    sender[VID]=2;
						    StopAudioStreamForPlayer(playerid);
						    TextDrawShowForPlayer(playerid,YOUFM);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_2.m3u");//YOU FM LIVE
						}
						case 4:
						{
			 				KillTimer(timer);
			                entftextdraw(playerid);
			                gesperrt[playerid]=1;
						    sender[VID]=3;
						    StopAudioStreamForPlayer(playerid);
						    TextDrawShowForPlayer(playerid,YOUFM2);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_rock.m3u"); // YOU FM ROCK
						}
						case 5:
						{
	        				KillTimer(timer);
	                		entftextdraw(playerid);
	                		gesperrt[playerid]=1;
						    sender[VID]=4;
						    StopAudioStreamForPlayer(playerid);
						    TextDrawShowForPlayer(playerid,YOUFM3);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_club.m3u"); // YOU FM CLUB
						}
						case 6:
						{
							KillTimer(timer);
			                entftextdraw(playerid);
			                gesperrt[playerid]=1;
						    sender[VID]=5;
						    StopAudioStreamForPlayer(playerid);
						    TextDrawShowForPlayer(playerid,YOUFM4);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_black.m3u"); // YOU FM BLACK
						}
						case 7:
						{
							KillTimer(timer);
			                entftextdraw(playerid);
			                gesperrt[playerid]=1;
						    sender[VID]=6;
		    				StopAudioStreamForPlayer(playerid);
		    				TextDrawShowForPlayer(playerid,RTL);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://mp3.89.0rtl.de/listen.pls"); // 89.0 RTL
						}
						case 8:
						{
						    sender[VID]=7;
							KillTimer(timer);
				   			entftextdraw(playerid);
				   			gesperrt[playerid]=1;
						    StopAudioStreamForPlayer(playerid);
						    TextDrawShowForPlayer(playerid,radioplanet);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://streams.planetradio.de/planetradio/mp3/hqlivestream.m3u"); // Planet Radio
						}
					}
				}
				return 1;
			}
			if(PRESSED(KEY_ANALOG_DOWN))
			{
   				if(gesperrt[playerid]!=1)
				{
					switch(sender[VID])
					{
						case 1:
						{
	    					KillTimer(timer);
	                		entftextdraw(playerid);
	                		gesperrt[playerid]=1;
						    sender[VID]=2;
						    StopAudioStreamForPlayer(playerid);
						    TextDrawShowForPlayer(playerid,YOUFM);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_2.m3u");//YOU FM LIVE
						}
						case 2:
						{
							KillTimer(timer);
			                entftextdraw(playerid);
			                gesperrt[playerid]=1;
						    sender[VID]=3;
						    StopAudioStreamForPlayer(playerid);
						    TextDrawShowForPlayer(playerid,YOUFM2);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_rock.m3u"); // YOU FM ROCK
						}
						case 3:
						{
							KillTimer(timer);
			                entftextdraw(playerid);
			                gesperrt[playerid]=1;
						    sender[VID]=4;
						    StopAudioStreamForPlayer(playerid);
						    TextDrawShowForPlayer(playerid,YOUFM3);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_club.m3u"); // YOU FM CLUB
						}
						case 4:
						{
							KillTimer(timer);
			                entftextdraw(playerid);
			                gesperrt[playerid]=1;
						    sender[VID]=5;
						    StopAudioStreamForPlayer(playerid);
						    TextDrawShowForPlayer(playerid,YOUFM4);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_black.m3u"); // YOU FM BLACK
						}
						case 5:
						{
							KillTimer(timer);
			                entftextdraw(playerid);
			                gesperrt[playerid]=1;
						    sender[VID]=6;
		    				StopAudioStreamForPlayer(playerid);
		    				TextDrawShowForPlayer(playerid,RTL);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://mp3.89.0rtl.de/listen.pls"); // 89.0 RTL
						}
						case 6:
						{
						    sender[VID]=7;
							KillTimer(timer);
				   			entftextdraw(playerid);
				   			gesperrt[playerid]=1;
						    StopAudioStreamForPlayer(playerid);
						    PlayAudioStreamForPlayer(playerid, "http://streams.planetradio.de/planetradio/mp3/hqlivestream.m3u"); // Planet Radio
						    TextDrawShowForPlayer(playerid,radioplanet);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
						}
						case 7:
						{
							KillTimer(timer);
			                entftextdraw(playerid);
			                gesperrt[playerid]=1;
						    sender[VID]=8;
		    				StopAudioStreamForPlayer(playerid);
		    				TextDrawShowForPlayer(playerid,technobase);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://listen.technobase.fm/dsl.pls"); // Technobase
						}
						case 8:
						{
							KillTimer(timer);
			                entftextdraw(playerid);
			                gesperrt[playerid]=1;
						    sender[VID]=1;
						    StopAudioStreamForPlayer(playerid);
						    PlayAudioStreamForPlayer(playerid, "http://gffstream.ic.llnwd.net/stream/gffstream_stream_wdr_einslive_a");//1LIVE
						    TextDrawShowForPlayer(playerid,LIVE);
							timer = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
						}
					}
				}
			}
		}
	}
	return 1;
}

public entftextdraw(playerid)
{
	TextDrawHideForPlayer(playerid,radioplanet);
	TextDrawHideForPlayer(playerid,LIVE);
	TextDrawHideForPlayer(playerid,YOUFM);
	TextDrawHideForPlayer(playerid,YOUFM2);
	TextDrawHideForPlayer(playerid,YOUFM3);
	TextDrawHideForPlayer(playerid,YOUFM4);
	TextDrawHideForPlayer(playerid,RTL);
	TextDrawHideForPlayer(playerid,RADIOAUS);
	TextDrawHideForPlayer(playerid,technobase);
 	gesperrt[playerid]=0;
}
