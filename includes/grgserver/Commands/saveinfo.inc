CMD:saveinfo(playerID, params[], StringID:450(""))
{
	new File:file;
	new lines[2048];
	new year;
	new month;
	new day;
	new hour;
	new minute;
	new second;
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:angle;
	new Float:frontVectorX;
	new Float:frontVectorY;
	new Float:frontVectorZ;
	getdate(year, month, day);
	gettime(hour, minute, second);
	AddLine:lines("Player: %s", GetPlayerNameEx(playerID));
	AddLine:lines("Date: %d/%02d/%02d %02d:%02d:%02d", year, month, day, hour, minute, second);
	GetPlayerCameraPos(playerID, posX, posY, posZ);
	GetPlayerCameraFrontVector(playerID, frontVectorX, frontVectorY, frontVectorZ);
	new Float:lookX = floatadd(posX, frontVectorX);
	new Float:lookY = floatadd(posY, frontVectorY);
	new Float:lookZ = floatadd(posZ, frontVectorZ);
	AddLine:lines("Camera Position: %f x %f x %f", posX, posY, posZ);
	AddLine:lines("Camera Look: %f x %f x %f", lookX, lookY, lookZ);
	new vehicleID = GetPlayerVehicleID(playerID);
	if (vehicleID)
	{
		AddLine(lines, "Mode: Vehicle");
		AddLine:lines("ModelID: %d", GetVehicleModel(vehicleID));
		GetVehiclePos(vehicleID, posX, posY, posZ);
		GetVehicleZAngle(vehicleID, angle);
		AddLine:lines("Vehicle Position: %f x %f x %f", posX, posY, posZ);
		AddLine:lines("Z Angle: %f", angle);
	}
	else
	{
		AddLine(lines, "Mode: On Foot");
		AddLine:lines("Skin: %d", GetPlayerSkin(playerID));
		GetPlayerPos(playerID, posX, posY, posZ);
		GetPlayerFacingAngle(playerID, angle);
		AddLine:lines("Player Position: %f x %f x %f", posX, posY, posZ);
		AddLine:lines("Facing Angle: %f", angle);
	}
	if (StrNotNull(params))
	{
		AddLine:lines("Comment: %s", params);
	}
	file = fopen(FILE_SAVEINFO, io_readwrite);
	if (file)
	{
		if (flength(file))
		{
			Format:lines("\n\n%s", lines);
		}
		fseek(file, 0, seek_end);
		fwrite(file, lines);
		fclose(file);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:451(""), FILE_SAVEINFO);
		return COMMAND_OK;
	}
	SendClientMessageEx(playerID, COLOR_INFO, StringID:452(""));
	return COMMAND_ERROR;
}