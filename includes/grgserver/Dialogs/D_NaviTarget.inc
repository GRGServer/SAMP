ShowDialog:NAVITARGET(playerID)
{
	new targets[2048];
	AddLine(targets, LanguageString(playerID, 173));// Bank
	AddLine(targets, LanguageString(playerID, 384));// Gas station
	AddLine(targets, LanguageString(playerID, 174));// Hotel
	AddLine(targets, LanguageString(playerID, 175));// House
	MySQLQuery("SELECT * FROM `navigationlocationtypes` ORDER BY `Name` ASC");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new string[256];
		strcat(string, GetMySQLField("Name"));
		new checkCharacter;
		new languageStringID;
		if (!sscanf(string, "p:cd", checkCharacter, languageStringID))
		{
			if (checkCharacter == 'L')
			{
				Format:string(LanguageString(playerID, languageStringID));
			}
		}
		AddLine(targets, string);
	}
	mysql_free_result();
	AddLine(targets, LanguageString(playerID, 342));// Target on map
	AddLine(targets, LanguageString(playerID, 417));// Name of a house
	CreateDialog(playerID, "NAVITARGET", DIALOG_STYLE_LIST, LanguageString(playerID, 247), targets, "OK", LanguageString(playerID, 165));
}

DialogResponse:NAVITARGET(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new Float:target[3];
		if (IsStr(inputText, LanguageString(playerID, 173)))// Bank
		{
			new pickupID = GetClosestPickup(playerID, "BANK");
			target[0] = pickups[pickupID][PICKUP_POSX];
			target[1] = pickups[pickupID][PICKUP_POSY];
			target[2] = pickups[pickupID][PICKUP_POSZ];
		}
		if (IsStr(inputText, LanguageString(playerID, 384)))// Gas station
		{
			new pickupID = GetClosestPickup(playerID, "GASSTATION");
			target[0] = pickups[pickupID][PICKUP_POSX];
			target[1] = pickups[pickupID][PICKUP_POSY];
			target[2] = pickups[pickupID][PICKUP_POSZ];
		}
		if (IsStr(inputText, LanguageString(playerID, 174)))// Hotel
		{
			new pickupID = GetClosestPickup(playerID, "HOTEL");
			target[0] = pickups[pickupID][PICKUP_POSX];
			target[1] = pickups[pickupID][PICKUP_POSY];
			target[2] = pickups[pickupID][PICKUP_POSZ];
		}
		if (IsStr(inputText, LanguageString(playerID, 175)))// House
		{
			new pickupID = GetClosestPickup(playerID, "HOUSE");
			target[0] = pickups[pickupID][PICKUP_POSX];
			target[1] = pickups[pickupID][PICKUP_POSY];
			target[2] = pickups[pickupID][PICKUP_POSZ];
		}
		if (IsStr(inputText, LanguageString(playerID, 342)))// Target on map
		{
			if (PVar:playerID[MAP_POSX] && PVar:playerID[MAP_POSY] && PVar:playerID[MAP_POSZ])
			{
				target[0] = PVar:playerID[MAP_POSX];
				target[1] = PVar:playerID[MAP_POSY];
				target[2] = PVar:playerID[MAP_POSZ];
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 264);
				return false;
			}
		}
		if (IsStr(inputText, LanguageString(playerID, 417)))// Name of a house
		{
			ShowDialog:NaviTarget_HouseName(playerID);
			return true;
		}
		if (!target[0] && !target[1] && !target[2])
		{
			new typeID = GetNavigationLocationTypeByName(playerID, inputText);
			if (typeID)
			{
				GetClosestNavigationLocation(playerID, typeID, target[0], target[1], target[2]);
			}
		}
		if (target[0] || target[1] || target[2])
		{
			if (CalculateRoute(playerID, target[0], target[1], target[2]))
			{
				SendClientMessageEx(playerID, COLOR_INFO, 414);
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 415);
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 343);
		}
	}
	return true;
}