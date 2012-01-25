// Aero Engine by Luby

#define LIMIT 10000
#pragma dynamic 49042168

#define EnableAero() SetTimer("Streamer",1117,true);SetTimer("PickupStreamer",4006,true);SetTimer("VehicleStreamer",1707,true)

new DontStreamVehicle[LIMIT];
new IsVehicleStreamed[699];
new VehicleIDX[LIMIT];
new AllVehiclesInPool = 0;
new VehicleDoesntStreamed[LIMIT];
enum VehicleStreamerEnum{strmodelid, Float:strX, Float:strY, Float:strZ, Float:startX, Float:startY, Float:startZ,  Float:strAng,  Float:startAng, c1, c2, Float:sstream};
new VehicleStreamerArray[LIMIT][VehicleStreamerEnum];
new VehiclesStreamed;
new StreamedVehiclesID[LIMIT];
new PickupDoesntStreamed[LIMIT];
enum PickupStreamerEnum{strmodelid, Float:strX, Float:strY, Float:strZ, typ, Float:sstream};
new PickupStreamerArray[LIMIT][PickupStreamerEnum];
new PickupsStreamed;
new StreamedPickupsID[LIMIT];
enum ObjectStreamerEnum{strmodelid, Float:strX, Float:strY, Float:strZ, Float:strrX, Float:strrY, Float:strrZ, Float:sstream};
new ObjectStreamerArray[LIMIT][ObjectStreamerEnum];
new ObjectsStreamed;
new PlayerStreamedObjectsID[200][LIMIT];

forward ObjectStreamer();
public ObjectStreamer(){
	new Float:X, Float:Y, Float:Z, val = 0;
	for(new g=0;g<GetMaxPlayers();g++){
		if(IsPlayerConnected(g)){
			GetPlayerPos(g, X, Y, Z);
			for(new x=0;x<ObjectsStreamed;x++){
				if(floatsqroot(floatpower(floatabs(floatsub(X,ObjectStreamerArray[x][strX])),2)+floatpower(floatabs(floatsub(Y,ObjectStreamerArray[x][strY])),2)+floatpower(floatabs(floatsub(Z,ObjectStreamerArray[x][strZ])),2))>ObjectStreamerArray[x][sstream]){
					if(PlayerStreamedObjectsID[g][x] > -1 && val < 100){
					    val++;
						DestroyPlayerObject(g, PlayerStreamedObjectsID[g][x]);
						PlayerStreamedObjectsID[g][x] = -1;
					}
				} else {
					if(PlayerStreamedObjectsID[g][x] == -1){
						PlayerStreamedObjectsID[g][x] = CreatePlayerObject(g, ObjectStreamerArray[x][strmodelid],ObjectStreamerArray[x][strX],ObjectStreamerArray[x][strY],ObjectStreamerArray[x][strZ],ObjectStreamerArray[x][strrX],ObjectStreamerArray[x][strrY],ObjectStreamerArray[x][strrZ]);
					}
					if(PlayerStreamedObjectsID[g][x] == 0){
						PlayerStreamedObjectsID[g][x] = CreatePlayerObject(g, ObjectStreamerArray[x][strmodelid],ObjectStreamerArray[x][strX],ObjectStreamerArray[x][strY],ObjectStreamerArray[x][strZ],ObjectStreamerArray[x][strrX],ObjectStreamerArray[x][strrY],ObjectStreamerArray[x][strrZ]);
					}
				}
			}
		}
	}
}

forward PickupStreamer();
public PickupStreamer(){
	new Float:X, Float:Y, Float:Z, addon;
	new Float:Distance;
	for(new x=0;x<PickupsStreamed;x++){
		addon=0;
		for(new g=0;g<GetMaxPlayers();g++)if(IsPlayerConnected(g)){
			GetPlayerPos(g, X, Y, Z);
			Distance = floatsqroot(floatpower(floatabs(floatsub(X,PickupStreamerArray[x][strX])),2)+floatpower(floatabs(floatsub(Y,PickupStreamerArray[x][strY])),2)+floatpower(floatabs(floatsub(Z,PickupStreamerArray[x][strZ])),2));
			if(Distance < PickupStreamerArray[x][sstream]){
				addon++;
				break;
			}
		}
		if(addon>0  && PickupDoesntStreamed[x] == 0){
			StreamedPickupsID[x] = CreatePickup(PickupStreamerArray[x][strmodelid], PickupStreamerArray[x][typ], PickupStreamerArray[x][strX], PickupStreamerArray[x][strY], PickupStreamerArray[x][strZ]);
			PickupDoesntStreamed[x] = 1;
		}
		if(addon == 0 && PickupDoesntStreamed[x] == 1){
			DestroyPickup(StreamedPickupsID[x]);
			PickupDoesntStreamed[x] = 0;
		}
	}
}

forward VehicleStreamer();
public VehicleStreamer(){
	new Float:X, Float:Y, Float:Z, addon;
	new Float:Distance;
	for(new x=0;x<VehiclesStreamed;x++){
		addon=0;
		for(new g=0;g<GetMaxPlayers();g++)if(IsPlayerConnected(g)){
			GetPlayerPos(g, X, Y, Z);
			Distance = floatsqroot(floatpower(floatabs(floatsub(X,VehicleStreamerArray[x][strX])),2)+floatpower(floatabs(floatsub(Y,VehicleStreamerArray[x][strY])),2)+floatpower(floatabs(floatsub(Z,VehicleStreamerArray[x][strZ])),2));
			if(Distance < VehicleStreamerArray[x][sstream]){
				addon++;
				break;
			}
		}
		if(addon>0 && VehicleDoesntStreamed[x] == 0 && AllVehiclesInPool < 690 && !DontStreamVehicle[x]){
			StreamedVehiclesID[x] =
			CreateVehicle(VehicleStreamerArray[x][strmodelid],VehicleStreamerArray[x][strX],VehicleStreamerArray[x][strY],VehicleStreamerArray[x][strZ],VehicleStreamerArray[x][strAng],VehicleStreamerArray[x][c1],VehicleStreamerArray[x][c2],999999);
			VehicleDoesntStreamed[x] = 1;
			AllVehiclesInPool = StreamedVehiclesID[x];
			VehicleIDX[StreamedVehiclesID[x]] = x;
			IsVehicleStreamed[StreamedVehiclesID[x]] = 1;
		}
		if(addon == 0 && VehicleDoesntStreamed[x] == 1 && !IsVehicleInUseDFforAero(StreamedVehiclesID[x])){
		    new Float:X2, Float:Y2, Float:Z2, Float:A2;
		    GetVehiclePos(StreamedVehiclesID[x], X2, Y2, Z2);
		    GetVehicleZAngle(StreamedVehiclesID[x], A2);
			new Float:Distance2 = floatsqroot(floatpower(floatabs(floatsub(X,X2)),2)+floatpower(floatabs(floatsub(Y,Y2)),2)+floatpower(floatabs(floatsub(Z,Z2)),2));
			if(Distance2 > 200.0){
				DestroyVehicle(StreamedVehiclesID[x]);
				VehicleDoesntStreamed[x] = 0;
				AllVehiclesInPool--;
				VehicleIDX[StreamedVehiclesID[x]] = -1;
				IsVehicleStreamed[StreamedVehiclesID[x]] = 0;
			}
			if(A2 != 0.00000 && !DontStreamVehicle[x]){
				VehicleStreamerArray[x][strX] = X2;
				VehicleStreamerArray[x][strY] = Y2;
				VehicleStreamerArray[x][strZ] = Z2;
				VehicleStreamerArray[x][strAng] = A2;
			}
		}
	}
}

stock AddStreamableObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:stream=1000.0){
	ObjectStreamerArray[ObjectsStreamed][strmodelid]=modelid;
	ObjectStreamerArray[ObjectsStreamed][strX]=X;
	ObjectStreamerArray[ObjectsStreamed][strY]=Y;
	ObjectStreamerArray[ObjectsStreamed][strZ]=Z;
	ObjectStreamerArray[ObjectsStreamed][strrX]=rX;
	ObjectStreamerArray[ObjectsStreamed][strrY]=rY;
	ObjectStreamerArray[ObjectsStreamed][strrZ]=rZ;
	ObjectStreamerArray[ObjectsStreamed][sstream]=stream;
	ObjectsStreamed++;
	return ObjectsStreamed-1;
}

stock AddStreamablePickup(modelid, rX, Float:X, Float:Y, Float:Z, Float:stream=30.0){
	PickupStreamerArray[PickupsStreamed][strmodelid]=modelid;
	PickupStreamerArray[PickupsStreamed][strX]=X;
	PickupStreamerArray[PickupsStreamed][strY]=Y;
	PickupStreamerArray[PickupsStreamed][strZ]=Z;
	PickupStreamerArray[PickupsStreamed][typ]=rX;
	PickupStreamerArray[PickupsStreamed][sstream]=stream;
	PickupsStreamed++;
	return PickupsStreamed-1;
}

stock AddStreamableVehicle(modelid, Float:X, Float:Y, Float:Z, Float:Angle, c11, c22, Float:stream=300.0){
	VehicleStreamerArray[VehiclesStreamed][strmodelid]=modelid;
	VehicleStreamerArray[VehiclesStreamed][strX]=X;
	VehicleStreamerArray[VehiclesStreamed][strY]=Y;
	VehicleStreamerArray[VehiclesStreamed][strZ]=Z;
	VehicleStreamerArray[VehiclesStreamed][strAng]=Angle;
	VehicleStreamerArray[VehiclesStreamed][startX]=X;
	VehicleStreamerArray[VehiclesStreamed][startY]=Y;
	VehicleStreamerArray[VehiclesStreamed][startZ]=Z;
	VehicleStreamerArray[VehiclesStreamed][startAng]=Angle;
	VehicleStreamerArray[VehiclesStreamed][c1]=c11;
	VehicleStreamerArray[VehiclesStreamed][c2]=c22;
	VehicleStreamerArray[VehiclesStreamed][sstream]=stream;
	DontStreamVehicle[VehiclesStreamed] = 0;
	VehiclesStreamed++;
	return VehiclesStreamed-1;
}

stock IsVehicleInUseDFforAero(vehicleid){
	new temp;
	for(new i=0;i<200;i++){
		if(IsPlayerConnected(i) && IsPlayerInVehicle(i, vehicleid) && GetPlayerState(i)==PLAYER_STATE_DRIVER){
			temp++;
		}
	}
	if(temp > 0){ return true; } else return false;
}

IsNumeric(const string2[]){ //By Mike
	for (new i=0,j=strlen(string2);i<j;i++){
	    if (string2[i] > '9' || string2[i] < '0') return false;
	}
	return true;
}

stock Aero_ProcessFile(file[], formatting[]){
	CallRemoteFunction("OnProcessInit", "s", file);
	new vehs, objs, picks;
	new File:fh = fopen(file, io_readwrite);
	new ToParse[512], FuncName[256], args[30][256], id=0;
	new funcidxx=0;
	new Variables[512];
	new CommentEnabled = 0;
	while(fread(fh, ToParse)){
	    new AttVariable[256], returnval;
	    ToParse = strreplace("\t", "", ToParse);
		while(ToParse[0] == ' ' || ToParse[0] == '='){
			new tmp4[256];
			for(new i=0;i<strlen(ToParse)-1;i++)tmp4[i] = ToParse[i+1];
			ToParse = tmp4;
		}
	    if(ToParse[0] == '/' && ToParse[1] == '/')continue;
	    if((ToParse[0] == '*' && ToParse[1] == '/')){
            CommentEnabled = 0;
            ToParse = strreplace("*/", "", ToParse);
		}
	    if((ToParse[0] == '/' && ToParse[1] == '*') || CommentEnabled){
	        CommentEnabled = 1;
			continue;
		}
   		if(ToParse[0] == 'n' && ToParse[1] == 'e' && ToParse[2] == 'w'){
			if(strfind(ToParse, "=", true)!=-1){
				new varb[256], idx2=0;
				varb = Aero_strtok(ToParse, idx2, '=');
				ToParse = strreplace(varb, "", ToParse);
				while(ToParse[0] == ' ' || ToParse[0] == '='){
					new tmp3[256];
					for(new i=0;i<strlen(ToParse)-1;i++)tmp3[i] = ToParse[i+1];
					ToParse = tmp3;
				}
				varb = strreplace("new ", "", varb);
				AttVariable = varb;
				varb = Aero_strtok(ToParse, idx2, '=');
				idx2=0;
				varb = Aero_strtok(varb, idx2, '(');
				while(varb[0] == ' '){
					new tmp2[256];
					for(new i=0;i<strlen(varb)-1;i++)tmp2[i] = varb[i+1];
					varb = tmp2;
				}
				AttVariable = strreplace(" ", "", AttVariable);
				AttVariable = strreplace("[", "", AttVariable);
				AttVariable = strreplace("]", "", AttVariable);
				if(strfind(varb, "\"", true)!=-1 || strfind(varb, ".", true)!=-1 || IsNumeric(varb)){
					varb = strreplace(";", "", varb);
					varb = strreplace("\"", "", varb);
				    format(Variables, 256, "%s%s %s ", Variables, AttVariable, varb);
				    AttVariable[0]='\0';
				}
			} else {
				new varb[256], idx2=0;
				varb = Aero_strtok(ToParse, idx2, ';');
				varb = strreplace("new ", "", varb);
				AttVariable = varb;
			    format(Variables, 256, "%s%s 0 ", Variables, AttVariable);
			}
  		}
		FuncName = Aero_strtok(ToParse, id, '(');
		ToParse = strreplace(FuncName, "", ToParse);
		ToParse = strreplace("(", "", ToParse);
		ToParse = strreplace(")", "", ToParse);
		ToParse = strreplace(";", "", ToParse);
		ToParse = strreplace("/", "", ToParse);
		ToParse = strreplace("\"", "", ToParse);
  		new names[20][256];
  		new vars[20][256];
  		new names2[20][256];
  		new vars2[20][256];
  		funcidxx=0;
  		new f=0;
		for(f=0;f<20;f++){
			names[f] = Aero_strtok(formatting, funcidxx, ' ');
			vars[f] = Aero_strtok(formatting, funcidxx, ' ');
			if(names[f][0] && vars[f][0]){
				ToParse = strreplace(names[f], vars[f], ToParse);
			} else break;
		}
		funcidxx=0;
		for(f=0;f<200;f++){
			names2[f] = Aero_strtok(Variables, funcidxx, ' ');
			vars2[f] = Aero_strtok(Variables, funcidxx, ' ');
			if(names2[f][0] && vars2[f][0]){
				ToParse = strreplace(names2[f], vars2[f], ToParse);
			} else break;
		}
		new g=0;
		id=0;
		args[g] = Aero_strtok(ToParse, id, ',');
		while(args[g][0]){
		    g++;
            args[g] = Aero_strtok(ToParse, id, ',');
		}
		for(new x=0;x<30;x++){
		    if(strfind(args[x], "0x", true)!=-1){
                args[x] = strreplace("0x", "", args[x]);
				new reverse[256];
				new o=0;
				for(o=0;o<strlen(args[x]);o++)reverse[o] = args[x][strlen(args[x])-o-1];
				new intg=0, power=0;
				for(o=0;o<strlen(reverse);o++){
				    new character = reverse[o];
				    new strone[16];
				    switch(toupper(character)){
				        case 'F': strone = "15";
				        case 'E': strone = "14";
				        case 'D': strone = "13";
				        case 'C': strone = "12";
				        case 'B': strone = "11";
				        case 'A': strone = "10";
				        case '9': strone = "9";
				        case '8': strone = "8";
				        case '7': strone = "7";
				        case '6': strone = "6";
				        case '5': strone = "5";
				        case '4': strone = "4";
				        case '3': strone = "3";
				        case '2': strone = "2";
				        case '1': strone = "1";
				        case '0': strone = "0";
				        default: strone = "n";
				    }
				    if(strone[0] != 'n'){
				    	new powered=1;
						if(power == 0)powered = 1;
						if(power == 1)powered = 16;
						if(power > 1)for(new pwr=0;pwr<power;pwr++)powered*=16;
						intg+=strval(strone)*(powered);
						power++;
					}
				}
				format(args[x], 256, "%d", intg);
		    }
		}
		id=0;
		if(!strcmp(FuncName, "AddStreamableVehicle", false)){
		    returnval = AddStreamableVehicle(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), strval(args[5]), strval(args[6]));
			vehs++;
		}
		if(!strcmp(FuncName, "AddStreamablePickup", false)){
		    returnval = AddStreamablePickup(strval(args[0]), strval(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]));
			picks++;
		}
		if(!strcmp(FuncName, "AddStreamableObject", false)){
		    returnval = AddStreamableObject(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), floatstr(args[5]), floatstr(args[6]));
			objs++;
		}
		if(!strcmp(FuncName, "AddStaticVehicle", false)){
		    returnval = AddStaticVehicle(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), strval(args[5]), strval(args[6]));
			vehs++;
		}
		if(!strcmp(FuncName, "AddStaticVehicleEx", false)){
		    returnval = AddStaticVehicleEx(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), strval(args[5]), strval(args[6]), strval(args[7]));
			vehs++;
		}
		if(!strcmp(FuncName, "AddStaticPickup", false)){
		    returnval = AddStaticPickup(strval(args[0]), strval(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]));
			picks++;
		}
		if(!strcmp(FuncName, "CreateObject", false)){
		    returnval = CreateObject(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), floatstr(args[5]), floatstr(args[6]));
			objs++;
		}
		if(!strcmp(FuncName, "print", false)){
			returnval = print(args[0]);
		}
		if(!strcmp(FuncName, "printf", false)){
			returnval = printf(args[0], strval(args[1]), floatstr(args[2]));
		}
		if(!strcmp(FuncName, "SendClientMessage", false)){
			returnval = SendClientMessage(strval(args[0]), strval(args[1]), args[2]);
		}
		if(!strcmp(FuncName, "SendClientMessageToAll", false)){
			returnval = SendClientMessageToAll(strval(args[0]), args[1]);
		}
		if(!strcmp(FuncName, "SendPlayerMessageToPlayer", false)){
			returnval = SendPlayerMessageToPlayer(strval(args[0]), strval(args[1]), args[2]);
		}
		if(!strcmp(FuncName, "SendPlayerMessageToAll", false)){
			returnval = SendPlayerMessageToAll(strval(args[0]), args[1]);
		}
		if(!strcmp(FuncName, "SendDeathMessage", false)){
			returnval = SendDeathMessage(strval(args[0]), strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "GameTextForAll", false)){
			returnval = GameTextForAll(args[0], strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "GameTextForPlayer", false)){
			returnval = GameTextForPlayer(strval(args[0]), args[1], strval(args[2]), strval(args[3]));
		}
		if(!strcmp(FuncName, "SetTimer", false)){
			returnval = SetTimer(args[0], strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "SetTimerEx", false)){
			returnval = SetTimerEx(args[0], strval(args[1]), strval(args[2]), args[3], strval(args[4]), floatstr(args[5]));
		}
		if(!strcmp(FuncName, "KillTimer", false)){
			returnval = KillTimer(strval(args[0]));
		}
		if(!strcmp(FuncName, "GetTickCount", false)){
			returnval = GetTickCount();
		}
		if(!strcmp(FuncName, "GetMaxPlayers", false)){
			returnval = GetMaxPlayers();
		}
		if(!strcmp(FuncName, "LimitGlobalChatRadius", false)){
			returnval = LimitGlobalChatRadius(floatstr(args[0]));
		}
		if(!strcmp(FuncName, "CallRemoteFunction", false)){
			returnval = CallRemoteFunction(args[0], args[1], strval(args[2]), floatstr(args[3]));
		}
		if(!strcmp(FuncName, "CallLocalFunction", false)){
			returnval = CallLocalFunction(args[0], args[1], strval(args[2]), floatstr(args[3]));
		}
		if(!strcmp(FuncName, "asin", false)){
			asin(floatstr(args[0]));
		}
		if(!strcmp(FuncName, "acos", false)){
			acos(floatstr(args[0]));
		}
		if(!strcmp(FuncName, "atan", false)){
			atan(floatstr(args[0]));
		}
		if(!strcmp(FuncName, "atan2", false)){
			atan2(floatstr(args[0]), floatstr(args[1]));
		}
		if(!strcmp(FuncName, "SetGameModeText", false)){
			returnval = SetGameModeText(args[0]);
		}
		if(!strcmp(FuncName, "SetTeamCount", false)){
			returnval = SetTeamCount(strval(args[0]));
		}
		print(FuncName);
		if(!strcmp(FuncName, "AddPlayerClass", false)){
		    printf("AddPlayerClass(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);",strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), strval(args[5]), strval(args[6]), strval(args[7]), strval(args[8]), strval(args[9]), strval(args[10]));
			returnval = AddPlayerClass(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), strval(args[5]), strval(args[6]), strval(args[7]), strval(args[8]), strval(args[9]), strval(args[10]));
		}
		if(!strcmp(FuncName, "AddPlayerClassEx", false)){
			returnval = AddPlayerClassEx(strval(args[0]), strval(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), floatstr(args[5]), strval(args[6]), strval(args[7]), strval(args[8]), strval(args[9]), strval(args[10]), strval(args[11]));
		}
		if(!strcmp(FuncName, "CreatePickup", false)){
			returnval = CreatePickup(strval(args[0]), strval(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]));
		}
		if(!strcmp(FuncName, "DestroyPickup", false)){
			returnval = DestroyPickup(strval(args[0]));
		}
		if(!strcmp(FuncName, "ShowNameTags", false)){
			returnval = ShowNameTags(strval(args[0]));
		}
		if(!strcmp(FuncName, "ShowPlayerMarkers", false)){
			returnval = ShowPlayerMarkers(strval(args[0]));
		}
		if(!strcmp(FuncName, "GameModeExit", false)){
			returnval = GameModeExit();
		}
		if(!strcmp(FuncName, "SetWorldTime", false)){
			returnval = SetWorldTime(strval(args[0]));
		}
		if(!strcmp(FuncName, "GetWeaponName", false)){
			returnval = GetWeaponName(strval(args[0]), args[1], strval(args[2]));
		}
		if(!strcmp(FuncName, "EnableTirePopping", false)){
			returnval = EnableTirePopping(strval(args[0]));
		}
		if(!strcmp(FuncName, "AllowInteriorWeapons", false)){
			returnval = AllowInteriorWeapons(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetWeather", false)){
			returnval = SetWeather(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetGravity", false)){
			returnval = SetGravity(floatstr(args[0]));
		}
		if(!strcmp(FuncName, "AllowAdminTeleport", false)){
			returnval = AllowAdminTeleport(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetDeathDropAmount", false)){
			returnval = SetDeathDropAmount(strval(args[0]));
		}
		if(!strcmp(FuncName, "CreateExplosion", false)){
			returnval = CreateExplosion(floatstr(args[0]), floatstr(args[1]), floatstr(args[2]), strval(args[3]), floatstr(args[4]));
		}
		if(!strcmp(FuncName, "EnableZoneNames", false)){
			returnval = EnableZoneNames(strval(args[0]));
		}
		if(!strcmp(FuncName, "UsePlayerPedAnims", false)){
			returnval = UsePlayerPedAnims();
		}
		if(!strcmp(FuncName, "DisableInteriorEnterExits", false)){
			returnval = DisableInteriorEnterExits();
		}
		if(!strcmp(FuncName, "SetNameTagDrawDistance", false)){
			returnval = SetNameTagDrawDistance(floatstr(args[0]));
		}
		if(!strcmp(FuncName, "IsPlayerAdmin", false)){
			returnval = IsPlayerAdmin(strval(args[0]));
		}
		if(!strcmp(FuncName, "Kick", false)){
			returnval = Kick(strval(args[0]));
		}
		if(!strcmp(FuncName, "Ban", false)){
			returnval = Ban(strval(args[0]));
		}
		if(!strcmp(FuncName, "BanEx", false)){
			returnval = BanEx(strval(args[0]), args[1]);
		}
		if(!strcmp(FuncName, "SendRconCommand", false)){
			returnval = SendRconCommand(args[0]);
		}
		if(!strcmp(FuncName, "GetServerVarAsString", false)){
			returnval = GetServerVarAsString(args[0], args[1], strval(args[2]));
		}
		if(!strcmp(FuncName, "GetServerVarAsInt", false)){
			returnval = GetServerVarAsInt(args[0]);
		}
		if(!strcmp(FuncName, "GetServerVarAsBool", false)){
			returnval = GetServerVarAsBool(args[0]);
		}
		if(!strcmp(FuncName, "CreateMenu", false)){
		    new Menu:variab, frmt[256];
			variab = CreateMenu(args[0], strval(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), floatstr(args[5]));
			format(frmt, 256, "%d", _:variab);
			returnval = strval(frmt);
		}
		if(!strcmp(FuncName, "DestroyMenu", false)){
			returnval = DestroyMenu(Menu:strval(args[0]));
		}
		if(!strcmp(FuncName, "AddMenuItem", false)){
			returnval = AddMenuItem(Menu:strval(args[0]), strval(args[1]), args[2]);
		}
		if(!strcmp(FuncName, "SetMenuColumnHeader", false)){
			returnval = SetMenuColumnHeader(Menu:strval(args[0]), strval(args[1]), args[2]);
		}
		if(!strcmp(FuncName, "ShowMenuForPlayer", false)){
			returnval = ShowMenuForPlayer(Menu:strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "HideMenuForPlayer", false)){
			returnval = HideMenuForPlayer(Menu:strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "IsValidMenu", false)){
			returnval = IsValidMenu(Menu:strval(args[0]));
		}
		if(!strcmp(FuncName, "DisableMenu", false)){
			returnval = DisableMenu(Menu:strval(args[0]));
		}
		if(!strcmp(FuncName, "DisableMenuRow", false)){
			returnval = DisableMenuRow(Menu:strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "GetPlayerMenu", false)){
		    new Menu:variab, frmt[256];
			variab = GetPlayerMenu(strval(args[0]));
			format(frmt, 256, "%d", _:variab);
			returnval = strval(frmt);
		}
		if(!strcmp(FuncName, "TextDrawCreate", false)){
   			new Text:variab, frmt[256];
			variab = TextDrawCreate(floatstr(args[0]), floatstr(args[1]), args[2]);
			format(frmt, 256, "%d", _:variab);
			returnval = strval(frmt);
		}
		if(!strcmp(FuncName, "TextDrawDestroy", false)){
			returnval = TextDrawDestroy(Text:strval(args[0]));
		}
		if(!strcmp(FuncName, "TextDrawLetterSize", false)){
			returnval = TextDrawLetterSize(Text:strval(args[0]), floatstr(args[1]), floatstr(args[2]));
		}
		if(!strcmp(FuncName, "TextDrawTextSize", false)){
			returnval = TextDrawTextSize(Text:strval(args[0]), floatstr(args[1]), floatstr(args[2]));
		}
		if(!strcmp(FuncName, "TextDrawAlignment", false)){
			returnval = TextDrawAlignment(Text:strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "TextDrawColor", false)){
			returnval = TextDrawColor(Text:strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "TextDrawUseBox", false)){
			returnval = TextDrawUseBox(Text:strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "TextDrawBoxColor", false)){
			returnval = TextDrawBoxColor(Text:strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "TextDrawSetShadow", false)){
			returnval = TextDrawSetShadow(Text:strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "TextDrawSetOutline", false)){
			returnval = TextDrawSetOutline(Text:strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "TextDrawBackgroundColor", false)){
			returnval = TextDrawBackgroundColor(Text:strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "TextDrawFont", false)){
			returnval = TextDrawFont(Text:strval(args[0]), strval(args[1]));
		}
		
		//_____________________________________________________
		
		if(!strcmp(FuncName, "TextDrawSetProportional", false)){
			returnval = TextDrawSetProportional(Text:strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "TextDrawShowForPlayer", false)){
			returnval = TextDrawShowForPlayer(strval(args[0]), Text:strval(args[1]));
		}
		if(!strcmp(FuncName, "TextDrawHideForPlayer", false)){
			returnval = TextDrawHideForPlayer(strval(args[0]), Text:strval(args[1]));
		}
		if(!strcmp(FuncName, "TextDrawShowForAll", false)){
			returnval = TextDrawShowForAll(Text:strval(args[0]));
		}
		if(!strcmp(FuncName, "TextDrawHideForAll", false)){
			returnval = TextDrawHideForAll(Text:strval(args[0]));
		}
		if(!strcmp(FuncName, "TextDrawSetString", false)){
			returnval = TextDrawSetString(Text:strval(args[0]), args[1]);
		}
		if(!strcmp(FuncName, "GangZoneCreate", false)){
			returnval = GangZoneCreate(floatstr(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]));
		}
		if(!strcmp(FuncName, "GangZoneDestroy", false)){
			returnval = GangZoneDestroy(strval(args[0]));
		}
		if(!strcmp(FuncName, "GangZoneShowForPlayer", false)){
			returnval = GangZoneShowForPlayer(strval(args[0]), strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "GangZoneShowForAll", false)){
			returnval = GangZoneShowForAll(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "GangZoneHideForPlayer", false)){
			returnval = GangZoneHideForPlayer(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "GangZoneHideForAll", false)){
			returnval = GangZoneHideForAll(strval(args[0]));
		}
		if(!strcmp(FuncName, "GangZoneFlashForPlayer", false)){
			returnval = GangZoneFlashForPlayer(strval(args[0]), strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "GangZoneFlashForAll", false)){
			returnval = GangZoneFlashForAll(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "GangZoneStopFlashForPlayer", false)){
			returnval = GangZoneStopFlashForPlayer(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "GangZoneStopFlashForAll", false)){
			returnval = GangZoneStopFlashForAll(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetSpawnInfo", false)){
			returnval = SetSpawnInfo(strval(args[0]), strval(args[1]), strval(args[2]), floatstr(args[3]), floatstr(args[4]), floatstr(args[5]), floatstr(args[6]), strval(args[7]), strval(args[8]), strval(args[9]), strval(args[10]), strval(args[11]), strval(args[12]));
		}
		if(!strcmp(FuncName, "SpawnPlayer", false)){
			returnval = SpawnPlayer(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetPlayerPos", false)){
			returnval = SetPlayerPos(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]));
		}
		if(!strcmp(FuncName, "SetPlayerPosFindZ", false)){
			returnval = SetPlayerPosFindZ(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]));
		}
		if(!strcmp(FuncName, "GetPlayerPos", false)){
			new Float:X, Float:Y, Float:Z;
			returnval = GetPlayerPos(strval(args[0]), X, Y, Z);
		}
		if(!strcmp(FuncName, "SetPlayerFacingAngle", false)){
			returnval = SetPlayerFacingAngle(strval(args[0]), floatstr(args[1]));
		}
		if(!strcmp(FuncName, "GetPlayerFacingAngle", false)){
			new Float:A;
			returnval = GetPlayerFacingAngle(strval(args[0]), A);
		}
		if(!strcmp(FuncName, "SetPlayerInterior", false)){
			returnval = SetPlayerInterior(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "GetPlayerInterior", false)){
			returnval = GetPlayerInterior(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetPlayerHealth", false)){
			returnval = SetPlayerHealth(strval(args[0]), floatstr(args[1]));
		}
		if(!strcmp(FuncName, "GetPlayerHealth", false)){
			new Float:X;
			returnval = GetPlayerHealth(strval(args[0]), X);
		}
		if(!strcmp(FuncName, "SetPlayerArmour", false)){
			returnval = SetPlayerArmour(strval(args[0]), floatstr(args[1]));
		}
		if(!strcmp(FuncName, "GetPlayerArmour", false)){
			new Float:X;
			returnval = GetPlayerArmour(strval(args[0]), X);
		}
		if(!strcmp(FuncName, "SetPlayerAmmo", false)){
			returnval = SetPlayerAmmo(strval(args[0]), strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "GetPlayerAmmo", false)){
			returnval = GetPlayerAmmo(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetPlayerTeam", false)){
			returnval = SetPlayerTeam(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "GetPlayerTeam", false)){
			returnval = GetPlayerTeam(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetPlayerScore", false)){
			returnval = SetPlayerScore(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "GetPlayerScore", false)){
			returnval = GetPlayerScore(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetPlayerColor", false)){
			returnval = SetPlayerColor(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "GetPlayerColor", false)){
			returnval = GetPlayerColor(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetPlayerSkin", false)){
			returnval = SetPlayerSkin(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "GetPlayerSkin", false)){
			returnval = GetPlayerSkin(strval(args[0]));
		}
		if(!strcmp(FuncName, "GivePlayerWeapon", false)){
			returnval = GivePlayerWeapon(strval(args[0]), strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "ResetPlayerWeapons", false)){
			returnval = ResetPlayerWeapons(strval(args[0]));
		}
		if(!strcmp(FuncName, "GetPlayerWeaponData", false)){
			new w1, w2, w3;
			returnval = GetPlayerWeaponData(strval(args[0]), w1, w2, w3);
		}
		if(!strcmp(FuncName, "GivePlayerMoney", false)){
			returnval = GivePlayerMoney(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "ResetPlayerMoney", false)){
			returnval = ResetPlayerMoney(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetPlayerName", false)){
			returnval = SetPlayerName(strval(args[0]), args[1]);
		}
		if(!strcmp(FuncName, "GetPlayerMoney", false)){
			returnval = GetPlayerMoney(strval(args[0]));
		}
		if(!strcmp(FuncName, "GetPlayerState", false)){
			returnval = GetPlayerState(strval(args[0]));
		}
		if(!strcmp(FuncName, "GetPlayerIp", false)){
			returnval = GetPlayerIp(strval(args[0]), args[1], strval(args[2]));
		}
		if(!strcmp(FuncName, "GetPlayerPing", false)){
			returnval = GetPlayerPing(strval(args[0]));
		}
		if(!strcmp(FuncName, "GetPlayerWeapon", false)){
			returnval = GetPlayerWeapon(strval(args[0]));
		}
		if(!strcmp(FuncName, "GetPlayerKeys", false)){
			new k1, k2, k3;
			returnval = GetPlayerKeys(strval(args[0]), k1, k2, k3);
		}
		if(!strcmp(FuncName, "GetPlayerName", false)){
			new n[64];
			returnval = GetPlayerName(strval(args[0]), n, strval(args[2]));
		}
		if(!strcmp(FuncName, "SetPlayerTime", false)){
			returnval = SetPlayerTime(strval(args[0]), strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "GetPlayerTime", false)){
			new t1, t2;
			returnval = GetPlayerTime(strval(args[0]), t1, t2);
		}
		if(!strcmp(FuncName, "TogglePlayerClock", false)){
			returnval = TogglePlayerClock(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "SetPlayerWeather", false)){
			returnval = SetPlayerWeather(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "ForceClassSelection", false)){
			returnval = ForceClassSelection(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetPlayerWantedLevel", false)){
			returnval = SetPlayerWantedLevel(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "GetPlayerWantedLevel", false)){
			returnval = GetPlayerWantedLevel(strval(args[0]));
		}
		if(!strcmp(FuncName, "PutPlayerInVehicle", false)){
			returnval = PutPlayerInVehicle(strval(args[0]), strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "GetPlayerVehicleID", false)){
			returnval = GetPlayerVehicleID(strval(args[0]));
		}
		if(!strcmp(FuncName, "RemovePlayerFromVehicle", false)){
			returnval = RemovePlayerFromVehicle(strval(args[0]));
		}
		if(!strcmp(FuncName, "TogglePlayerControllable", false)){
			returnval = TogglePlayerControllable(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "PlayerPlaySound", false)){
			returnval = PlayerPlaySound(strval(args[0]), strval(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]));
		}
		if(!strcmp(FuncName, "ApplyAnimation", false)){
			returnval = ApplyAnimation(strval(args[0]), args[1], args[2], floatstr(args[3]), strval(args[4]), strval(args[5]), strval(args[6]), strval(args[7]), strval(args[8]));
		}
		if(!strcmp(FuncName, "ClearAnimations", false)){
			returnval = ClearAnimations(strval(args[0]));
		}
		if(!strcmp(FuncName, "GetPlayerSpecialAction", false)){
			returnval = GetPlayerSpecialAction(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetPlayerSpecialAction", false)){
			returnval = SetPlayerSpecialAction(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "SetPlayerCheckpoint", false)){
			returnval = SetPlayerCheckpoint(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]));
		}
		if(!strcmp(FuncName, "DisablePlayerCheckpoint", false)){
			returnval = DisablePlayerCheckpoint(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetPlayerRaceCheckpoint", false)){
			returnval = SetPlayerRaceCheckpoint(strval(args[0]), strval(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), floatstr(args[5]), floatstr(args[6]), floatstr(args[7]), floatstr(args[8]));
		}
		//___________________________________
		
		
		if(!strcmp(FuncName, "DisablePlayerRaceCheckpoint", false)){
			returnval = DisablePlayerRaceCheckpoint(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetPlayerWorldBounds", false)){
			returnval = SetPlayerWorldBounds(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]));
		}
		if(!strcmp(FuncName, "SetPlayerMarkerForPlayer", false)){
			returnval = SetPlayerMarkerForPlayer(strval(args[0]), strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "ShowPlayerNameTagForPlayer", false)){
			returnval = ShowPlayerNameTagForPlayer(strval(args[0]), strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "SetPlayerMapIcon", false)){
			returnval = SetPlayerMapIcon(strval(args[0]), strval(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), strval(args[5]), strval(args[6]));
		}
		if(!strcmp(FuncName, "RemovePlayerMapIcon", false)){
			returnval = RemovePlayerMapIcon(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "SetPlayerCameraPos", false)){
			returnval = SetPlayerCameraPos(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]));
		}
		if(!strcmp(FuncName, "SetPlayerCameraLookAt", false)){
			returnval = SetPlayerCameraLookAt(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]));
		}
		if(!strcmp(FuncName, "SetCameraBehindPlayer", false)){
			returnval = SetCameraBehindPlayer(strval(args[0]));
		}
		if(!strcmp(FuncName, "AllowPlayerTeleport", false)){
			returnval = AllowPlayerTeleport(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "IsPlayerConnected", false)){
			returnval = IsPlayerConnected(strval(args[0]));
		}
		if(!strcmp(FuncName, "IsPlayerInVehicle", false)){
			returnval = IsPlayerInVehicle(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "IsPlayerInAnyVehicle", false)){
			returnval = IsPlayerInAnyVehicle(strval(args[0]));
		}
		if(!strcmp(FuncName, "IsPlayerInCheckpoint", false)){
			returnval = IsPlayerInCheckpoint(strval(args[0]));
		}
		if(!strcmp(FuncName, "IsPlayerInRaceCheckpoint", false)){
			returnval = IsPlayerInRaceCheckpoint(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetPlayerVirtualWorld", false)){
			returnval = SetPlayerVirtualWorld(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "GetPlayerVirtualWorld", false)){
			returnval = GetPlayerVirtualWorld(strval(args[0]));
		}
		if(!strcmp(FuncName, "EnableStuntBonusForPlayer", false)){
			returnval = EnableStuntBonusForPlayer(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "EnableStuntBonusForAll", false)){
			returnval = EnableStuntBonusForAll(strval(args[0]));
		}
		if(!strcmp(FuncName, "TogglePlayerSpectating", false)){
			returnval = TogglePlayerSpectating(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "PlayerSpectatePlayer", false)){
			returnval = PlayerSpectatePlayer(strval(args[0]), strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "PlayerSpectateVehicle", false)){
			returnval = PlayerSpectateVehicle(strval(args[0]), strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "SetObjectPos", false)){
			returnval = SetObjectPos(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]));
		}
		if(!strcmp(FuncName, "GetObjectPos", false)){
			new Float:X, Float:Y, Float:Z;
			returnval = GetObjectPos(strval(args[0]), X, Y, Z);
		}
		if(!strcmp(FuncName, "SetObjectRot", false)){
			returnval = SetObjectRot(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]));
		}
		if(!strcmp(FuncName, "GetObjectRot", false)){
			new Float:X, Float:Y, Float:Z;
			returnval = GetObjectRot(strval(args[0]), X, Y, Z);
		}
		if(!strcmp(FuncName, "IsValidObject", false)){
			returnval = IsValidObject(strval(args[0]));
		}
		if(!strcmp(FuncName, "DestroyObject", false)){
			returnval = DestroyObject(strval(args[0]));
		}
		if(!strcmp(FuncName, "MoveObject", false)){
			returnval = MoveObject(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]));
		}
		if(!strcmp(FuncName, "StopObject", false)){
			returnval = StopObject(strval(args[0]));
		}
		if(!strcmp(FuncName, "CreatePlayerObject", false)){
			returnval = CreatePlayerObject(strval(args[0]), strval(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), floatstr(args[5]), floatstr(args[6]), floatstr(args[7]));
		}
		if(!strcmp(FuncName, "SetPlayerObjectPos", false)){
			returnval = SetPlayerObjectPos(strval(args[0]), strval(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]));
		}
		if(!strcmp(FuncName, "GetPlayerObjectPos", false)){
			new Float:X, Float:Y, Float:Z;
			returnval = GetPlayerObjectPos(strval(args[0]), strval(args[1]), X, Y, Z);
		}
		if(!strcmp(FuncName, "SetPlayerObjectRot", false)){
			returnval = SetPlayerObjectRot(strval(args[0]), strval(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]));
		}
		if(!strcmp(FuncName, "GetPlayerObjectRot", false)){
			new Float:X, Float:Y, Float:Z;
			returnval = GetPlayerObjectRot(strval(args[0]), strval(args[1]), X, Y, Z);
		}
		if(!strcmp(FuncName, "IsValidPlayerObject", false)){
			returnval = IsValidPlayerObject(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "DestroyPlayerObject", false)){
			returnval = DestroyPlayerObject(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "MovePlayerObject", false)){
			returnval = MovePlayerObject(strval(args[0]), strval(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), floatstr(args[5]));
		}
		if(!strcmp(FuncName, "StopPlayerObject", false)){
			returnval = StopPlayerObject(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "AttachObjectToPlayer", false)){
			returnval = AttachObjectToPlayer(strval(args[0]), strval(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), floatstr(args[5]), floatstr(args[6]), floatstr(args[7]));
		}
		if(!strcmp(FuncName, "AttachPlayerObjectToPlayer", false)){
			returnval = AttachPlayerObjectToPlayer(strval(args[0]), strval(args[1]), strval(args[2]), floatstr(args[3]), floatstr(args[4]), floatstr(args[5]), floatstr(args[6]), floatstr(args[7]), floatstr(args[8]));
		}
		if(!strcmp(FuncName, "db_open", false)){
   			new DB:variab, frmt[256];
			variab = db_open(args[0]);
			format(frmt, 256, "%d", _:variab);
			returnval = strval(frmt);
		}
		if(!strcmp(FuncName, "db_close", false)){
			returnval = db_close(DB:strval(args[0]));
		}
		if(!strcmp(FuncName, "db_query", false)){
   			new DBResult:variab, frmt[256];
			variab = db_query(DB:strval(args[0]), args[1]);
			format(frmt, 256, "%d", _:variab);
			returnval = strval(frmt);
		}
		if(!strcmp(FuncName, "db_free_result", false)){
			returnval = db_free_result(DBResult:strval(args[0]));
		}
		if(!strcmp(FuncName, "db_num_rows", false)){
			returnval = db_num_rows(DBResult:strval(args[0]));
		}
		if(!strcmp(FuncName, "db_next_row", false)){
			returnval = db_next_row(DBResult:strval(args[0]));
		}
		if(!strcmp(FuncName, "db_num_fields", false)){
			returnval = db_num_fields(DBResult:strval(args[0]));
		}
		if(!strcmp(FuncName, "db_field_name", false)){
			returnval = db_field_name(DBResult:strval(args[0]), strval(args[1]), args[2], strval(args[3]));
		}
		if(!strcmp(FuncName, "db_get_field", false)){
			returnval = db_get_field(DBResult:strval(args[0]), strval(args[1]), args[2], strval(args[3]));
		}
		if(!strcmp(FuncName, "db_get_field_assoc", false)){
			returnval = db_get_field_assoc(DBResult:strval(args[0]), args[1], args[2], strval(args[3]));
		}
		//___________________________________________
		
		if(!strcmp(FuncName, "CreateVehicle", false)){
			returnval = CreateVehicle(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]), floatstr(args[4]), strval(args[5]), strval(args[6]), strval(args[7]));
		}
		if(!strcmp(FuncName, "DestroyVehicle", false)){
			returnval = DestroyVehicle(strval(args[0]));
		}
		if(!strcmp(FuncName, "GetVehiclePos", false)){
			new Float:X, Float:Y, Float:Z;
			returnval = GetVehiclePos(strval(args[0]), X, Y, Z);
		}
		if(!strcmp(FuncName, "SetVehiclePos", false)){
			returnval = SetVehiclePos(strval(args[0]), floatstr(args[1]), floatstr(args[2]), floatstr(args[3]));
		}
		if(!strcmp(FuncName, "GetVehicleZAngle", false)){
			new Float:A;
			returnval = GetVehicleZAngle(strval(args[0]), A);
		}
		if(!strcmp(FuncName, "SetVehicleZAngle", false)){
			returnval = SetVehicleZAngle(strval(args[0]), floatstr(args[1]));
		}
		if(!strcmp(FuncName, "SetVehicleParamsForPlayer", false)){
			returnval = SetVehicleParamsForPlayer(strval(args[0]), strval(args[1]), strval(args[2]), strval(args[3]));
		}
		if(!strcmp(FuncName, "SetVehicleToRespawn", false)){
			returnval = SetVehicleToRespawn(strval(args[0]));
		}
		if(!strcmp(FuncName, "LinkVehicleToInterior", false)){
			returnval = LinkVehicleToInterior(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "AddVehicleComponent", false)){
			returnval = AddVehicleComponent(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "RemoveVehicleComponent", false)){
			returnval = RemoveVehicleComponent(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "ChangeVehicleColor", false)){
			returnval = ChangeVehicleColor(strval(args[0]), strval(args[1]), strval(args[2]));
		}
		if(!strcmp(FuncName, "ChangeVehiclePaintjob", false)){
			returnval = ChangeVehiclePaintjob(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "SetVehicleHealth", false)){
			returnval = SetVehicleHealth(strval(args[0]), floatstr(args[1]));
		}
		if(!strcmp(FuncName, "GetVehicleHealth", false)){
			new Float:X;
			returnval = GetVehicleHealth(strval(args[0]), X);
		}
		if(!strcmp(FuncName, "AttachTrailerToVehicle", false)){
			returnval = AttachTrailerToVehicle(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "DetachTrailerFromVehicle", false)){
			returnval = DetachTrailerFromVehicle(strval(args[0]));
		}
		if(!strcmp(FuncName, "IsTrailerAttachedToVehicle", false)){
			returnval = IsTrailerAttachedToVehicle(strval(args[0]));
		}
		if(!strcmp(FuncName, "GetVehicleTrailer", false)){
			returnval = GetVehicleTrailer(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetVehicleNumberPlate", false)){
			returnval = SetVehicleNumberPlate(strval(args[0]), args[1]);
		}
		if(!strcmp(FuncName, "GetVehicleModel", false)){
			returnval = GetVehicleModel(strval(args[0]));
		}
		if(!strcmp(FuncName, "SetVehicleVirtualWorld", false)){
			returnval = SetVehicleVirtualWorld(strval(args[0]), strval(args[1]));
		}
		if(!strcmp(FuncName, "GetVehicleVirtualWorld", false)){
			returnval = GetVehicleVirtualWorld(strval(args[0]));
		}
		//___________________________________________
		if(strlen(AttVariable))format(Variables, 256, "%s%s %d ", Variables, AttVariable, returnval);
		CallRemoteFunction("OnProcessFile", "ss", file, FuncName);
	}
	fclose(fh);
	CallRemoteFunction("OnProcessEnd", "sddd", file, vehs, objs, picks);
}

stock Aero_strtok(string[], &index ,seperator=' '){
	new length = strlen(string);
	new offset = index;
	new result[256];
	while ((index < length) && (string[index] != seperator) && ((index - offset) < (sizeof(result) - 1))){
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	if ((index < length) && (string[index] == seperator))index++;
	return result;
}

stock strreplace(target[], newstr[], source[]){
	new tmp[256];
	ustaw(tmp, source);
//	new pos = strfind(tmp, target);
//	if(pos == -1)return tmp;
	new pos = strfind(tmp, target, false, 0);
	while(pos !=-1){
		tmp = strdelete(pos, strlen(target), tmp);
	//	strdel(tmp, pos, pos+strlen(target));
		strinject(tmp, pos, newstr);
		pos = strfind(tmp, target, false, pos);
 	}
	return tmp;
}

stock strdelete(pos, lenght, source[]){
	new tmp[256];
	new g=0;
	for(g=0;g<pos;g++)tmp[g] = source[g];
	for(g=pos;g<strlen(source)-lenght;g++)tmp[g] = source[g+lenght];
	tmp[g] = '\0';
//	ustaw(source, tmp);
	return tmp;
}

ustaw(str1[], str2[])for(new g=0;g<strlen(str2);g++)str1[g] = str2[g];

stock strinject(source[], adress, injection[]){// By Luby
	new temp[256];
	ustaw(temp, source);
	new g=adress;
	while(g<strlen(injection)+adress){
		temp[g]=injection[g-adress];
		g++;
	}
	g=adress+strlen(injection);
	while(g<strlen(source)+strlen(injection)){
		temp[g]=source[g-strlen(injection)];
		g++;
	}
	ustaw(source, temp);
	return temp;
}

stock AeroRcon(rcon[]){
	new id=0, file[256], formatted[256];
	Aero_strtok(rcon, id);
	if(!strcmp(rcon, "process", true, 5)){	
		file = Aero_strtok(rcon, id);
		formatted = Aero_strtok(rcon, id);
		Aero_ProcessFile(file, formatted);
		return true;
	}
	if(!strcmp(rcon, "reprocess", true, 7)){
		file = Aero_strtok(rcon, id);
		formatted = Aero_strtok(rcon, id);
		Aero_ProcessFile(file, formatted);
		return true;
	}	
	return false;
}

forward OnProcessFile(file[], function[], args[][]);
forward OnProcessInit(file[]);
forward OnProcessEnd(file[], vehs, objs, picks);
