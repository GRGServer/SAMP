PlayRandomCameraCuts(playerID)
{
	if (!PVar:playerID[PLAYRANDOMCAMERACUTS])
	{
		return false;
	}
	new Float:cuts[][enum_cameraCut] =
	{
		{
			2045.0,
			945.0,
			17.0,
			
			2045.0,
			945.0,
			17.0,
			
			2045.0,
			1155.0,
			17.0,
			
			2045.0,
			1160.0,
			17.0
		},
		{
			1311.978027,
			-1841.159545,
			126.674415,
			
			1312.707641,
			-1840.515014,
			126.445983,
			
			1548.934692,
			-1631.871582,
			52.500888,
			
			1549.664306,
			-1631.227050,
			52.272453
		},
		{
			2662.421142,
			-1364.576904,
			87.178253,
			
			2662.521240,
			-1365.560791,
			87.030357,
			
			2322.674072,
			-1799.792236,
			69.523422,
			
			2323.606933,
			-1799.489990,
			69.327049
		}
	};
	new cut = random(sizeof(cuts));
	InterpolateCameraPos(playerID, cuts[cut][CAMERACUT_STARTPOSX], cuts[cut][CAMERACUT_STARTPOSY], cuts[cut][CAMERACUT_STARTPOSZ], cuts[cut][CAMERACUT_ENDPOSX], cuts[cut][CAMERACUT_ENDPOSY], cuts[cut][CAMERACUT_ENDPOSZ], 10000, CAMERA_CUT);
	InterpolateCameraLookAt(playerID, cuts[cut][CAMERACUT_STARTLOOKX], cuts[cut][CAMERACUT_STARTLOOKY], cuts[cut][CAMERACUT_STARTLOOKZ], cuts[cut][CAMERACUT_ENDLOOKX], cuts[cut][CAMERACUT_ENDLOOKY], cuts[cut][CAMERACUT_ENDLOOKZ], 10000, CAMERA_CUT);
	SetTimerEx("Timer_RandomCameraCutsFader", 9000, false, "d", playerID);
	return true;
}