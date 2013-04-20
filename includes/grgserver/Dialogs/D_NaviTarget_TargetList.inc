ShowDialog:NaviTarget_TargetList(playerID)
{
	new list[2048];
	Count(listIndex, MAX_NAVITARGETS)
	{
		if (naviTargets[playerID][listIndex][NAVITARGET_DISTANCE] == 6000.0)
		{
			break;
		}
		AddLine:list("%d:\t%.2fm", listIndex + 1, naviTargets[playerID][listIndex][NAVITARGET_DISTANCE]);
	}
	CreateDialog(playerID, "NaviTarget_TargetList", DIALOG_STYLE_LIST, LanguageString(playerID, "247"), list, "OK", LanguageString(playerID, "BACK"));
}

DialogResponse:NaviTarget_TargetList(playerID, response, listItem, inputText[])
{
	if (!response)
	{
		ShowDialog:NaviTarget(playerID);
		return true;
	}
	if (listItem < MAX_NAVITARGETS && naviTargets[playerID][listItem][NAVITARGET_DISTANCE] != 6000.0)
	{
		if (CalculateRoute(playerID, naviTargets[playerID][listItem][NAVITARGET_POSX], naviTargets[playerID][listItem][NAVITARGET_POSY], naviTargets[playerID][listItem][NAVITARGET_POSZ]))
		{
			SendClientMessageEx(playerID, COLOR_INFO, "414");
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, "415");
		}
	}
	return true;
}