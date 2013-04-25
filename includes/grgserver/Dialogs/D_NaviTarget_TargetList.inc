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
	CreateDialog(playerID, "NaviTarget_TargetList", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:247("Select target")), list, "OK", LanguageString(playerID, StringID:171("Back")));
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
			SendClientMessageEx(playerID, COLOR_INFO, StringID:414("Calculating route"));
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:415("No GPS!"));
		}
	}
	return true;
}