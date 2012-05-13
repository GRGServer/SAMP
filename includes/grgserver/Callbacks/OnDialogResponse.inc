public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		// Accept the selected mission and send a message to the player created the job (If online)
		case DIALOG_ACCEPT:
		{
			if (response)
			{
				new missionID;
				new text[100];
				sscanf(inputtext, "p:ds", missionID, text);
				if (strval(GetMySQLValue("missions", "AcceptUserID", "ID", val2str(missionID))))
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 12);
				}
				else
				{
					SetMySQLValue("missions", "AcceptUserID", val2str(PVar:playerid[USERID]), "ID", val2str(missionID));
					SendClientMessageEx(playerid, COLOR_INFO, 15);
					SendClientMessageEx(GetPlayerByUserID(strval(GetMySQLValue("missions", "CreatorUserID", "ID", val2str(missionID)))), COLOR_INFO, 1, playerid, missionID);
					MySQLQuery("SELECT * FROM `missiondata` WHERE `MissionID` = '%d' AND `Name` = 'VehicleModelID'", missionID);
					mysql_store_result();
					new modelID = strval(GetMySQLField("Value"));
					mysql_free_result();
					CreateVehicleEx(modelID, -1557.4092, 114.7485, 3.0939, 136.5509, 12, 41, -1, false);
				}
			}
		}
		case DIALOG_ADAC:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:
					{
						PVar:playerid[JOBID] = JOB_ADAC;
					}
					case 1:
					{
						PVar:playerid[JOBID] = 0;
					}
				}
			}
		}
		// Add the selected object (Dialog created in command_addobject)
		case DIALOG_ADDOBJECT:
		{
			if (response)
			{
				new modelID;
				new name[STRINGLENGTH_OBJECTNAME];
				if (!sscanf(inputtext, "p:ds", modelID, name))
				{
					if (modelID)
					{
						AddObject(playerid, modelID);
					}
				}
			}
		}
		case DIALOG_ADDNAVILOCATION_NEWTYPE:
		{
			if (response)
			{
				if (strlen(inputtext))
				{
					MySQLQuery("INSERT INTO `navigationlocationtypes` (`Name`) VALUES('%s')", MySQLEscapeString(inputtext));
					new typeID = mysql_insert_id();
					if (typeID)
					{
						new Float:posX;
						new Float:posY;
						new Float:posZ;
						GetPlayerPos(playerid, posX, posY, posZ);
						MySQLQuery("INSERT INTO `navigationlocations` (`Type`, `PosX`, `PosY`, `PosZ`) VALUES('%d', '%f', '%f', '%f')", typeID, posX, posY, posZ);
						SendClientMessageEx(playerid, COLOR_INFO, 383);
					}
					else
					{
						SendClientMessageEx(playerid, COLOR_ERROR, 143);
					}
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 379);
					ShowDialog(playerid, DIALOG_ADDNAVILOCATION_NEWTYPE);
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_ADDNAVILOCATION_TYPE);
			}
		}
		case DIALOG_ADDNAVILOCATION_TYPE:
		{
			if (response)
			{
				if (IsStr(inputtext, LanguageString(playerid, 378)))
				{
					ShowDialog(playerid, DIALOG_ADDNAVILOCATION_NEWTYPE);
				}
				else
				{
					new typeID = GetNavigationLocationTypeByName(playerid, inputtext);
					if (typeID)
					{
						new Float:posX;
						new Float:posY;
						new Float:posZ;
						GetPlayerPos(playerid, posX, posY, posZ);
						MySQLQuery("INSERT INTO `navigationlocations` (`Type`, `PosX`, `PosY`, `PosZ`) VALUES('%d', '%f', '%f', '%f')", typeID, posX, posY, posZ);
						SendClientMessageEx(playerid, COLOR_INFO, 383);
					}
					else
					{
						SendClientMessageEx(playerid, COLOR_ERROR, 143);
					}
				}
			}
		}
		// Asked for the name of the new building
		case DIALOG_ADDPROPERTY_NAME:
		{
			if (response)
			{
				new Float:posX;
				new Float:posY;
				new Float:posZ;
				new pickupID;
				GetPlayerPos(playerid, posX, posY, posZ);
				pickupID = AddPickup(-1, PVar:playerid[ADDPROPERTY_TYPE], posX, posY, posZ, true);
				if (pickupID > 0)
				{
					MySQLQuery("INSERT INTO `properties` (`PickupID`, `InteriorID`, `Name`, `Price`) VALUES ('%d', '%d', '%s', '%f')", pickupID, PVar:playerid[ADDPROPERTY_INTERIORID], MySQLEscapeString(inputtext), PVar:playerid[ADDPROPERTY_PRICE]);
					SendClientMessageEx(playerid, COLOR_INFO, 10, inputtext, PVar:playerid[ADDPROPERTY_PRICE], mysql_insert_id());
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 6);
				}
			}
			else
			{
				ShowInteriorDialog(playerid, INTERIORDIALOG_ADDPROPERTY);
			}
		}
		// Asked for the type of the new building
		case DIALOG_ADDPROPERTY_TYPE:
		{
			if (response)
			{
				new type[STRINGLENGTH_PROPERTYTYPE];
				if (IsStr(inputtext, LanguageString(playerid, 173)))
				{
					type = "BANK";
				}
				if (IsStr(inputtext, LanguageString(playerid, 174)))
				{
					type = "HOTEL";
				}
				if (IsStr(inputtext, LanguageString(playerid, 175)))
				{
					type = "HOUSE";
				}
				if (IsStr(inputtext, LanguageString(playerid, 397)))
				{
					type = "PLACE";
				}
				if (IsStr(inputtext, LanguageString(playerid, 176)))
				{
					type = "POLICE";
				}
				SetPVarStr:playerid[ADDPROPERTY_TYPE][STRINGLENGTH_PROPERTYTYPE](type);
				if (IsStr(type, "HOTEL") || IsStr(type, "PLACE"))
				{
					PVar:playerid[ADDPROPERTY_INTERIORID] = 0;
					ShowDialog(playerid, DIALOG_ADDPROPERTY_NAME);
					return true;
				}
				ShowInteriorDialog(playerid, INTERIORDIALOG_ADDPROPERTY);
			}
		}
		case DIALOG_ARMY:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:
					{
						PVar:playerid[JOBID] = JOB_ARMEE;
					}
					case 1:
					{
						PVar:playerid[JOBID] = 0;
					}
				}
			}
		}
		case DIALOG_AMBULANCE:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:
					{
						PVar:playerid[JOBID] = JOB_AMBULANCE;
					}
					case 1:
					{
						PVar:playerid[JOBID] = 0;
					}
				}
			}
		}
		// Cancel the bank account
		case DIALOG_BANK_CANCELACCOUNT:
		{
			if (response)
			{
				SetUserDBValue(playerid, "BankID", "0");
				LeaveProperty(playerid);
			}
			else
			{
				ShowDialog(playerid, DIALOG_BANK_HASACCOUNT);
			}
		}
		// Deposit money to bank account
		case DIALOG_BANK_DEPOSITMONEY:
		{
			if (response)
			{
				if (!strlen(inputtext))
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 19);
					ShowDialog(playerid, DIALOG_BANK_DEPOSITMONEY);
				}
				else
				{
					new Float:money = floatstr(inputtext);
					if(money > PVar:playerid[MONEY])
					{
						SendClientMessageEx(playerid, COLOR_ERROR, 14);
						ShowDialog(playerid, DIALOG_BANK_DEPOSITMONEY);
					}
					else
					{
						SetPlayerMoney(playerid, MONEY_BANK, floatadd(PVar:playerid[BANKMONEY], money));
						SetPlayerMoney(playerid, MONEY_CASH, floatsub(PVar:playerid[MONEY], money));
						SendClientMessageEx(playerid, COLOR_INFO, 21, money);
						ShowDialog(playerid, DIALOG_BANK_HASACCOUNT);
					}
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_BANK_HASACCOUNT);
			}
		}
		// Do selected action for a player with a bank account
		case DIALOG_BANK_HASACCOUNT:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:// Bank balance
					{
						SendClientMessageEx(playerid, COLOR_INFO, 23, PVar:playerid[BANKMONEY]);
						ShowDialog(playerid, DIALOG_BANK_HASACCOUNT);
					}
					case 1:// Withdraw money
					{
						ShowDialog(playerid, DIALOG_BANK_WITHDRAWMONEY);
					}
					case 2:// Deposit money
					{
						ShowDialog(playerid, DIALOG_BANK_DEPOSITMONEY);
					}
					case 3:// Cancel account
					{
						if (PVar:playerid[BANKMONEY] > 0)
						{
							SendClientMessageEx(playerid, COLOR_ERROR, 215);
							ShowDialog(playerid, DIALOG_BANK_HASACCOUNT);
						}
						else
						{
							ShowDialog(playerid, DIALOG_BANK_CANCELACCOUNT);
						}
					}
				}
			}
			else
			{
				LeaveProperty(playerid);
			}
		}
		// Create a new bank account
		case DIALOG_BANK_NEWACCOUNT:
		{
			if (response)
			{
				new bankID = strval(GetMySQLValue("bankbranches", "BankID", "PropertyID", val2str(PVar:playerid[CURRENTPROPERTYID])));
				SetUserDBValue(playerid, "BankID", val2str(bankID));
				SendClientMessageEx(playerid, COLOR_INFO, 216, GetMySQLValue("banks", "Name", "ID", val2str(bankID)));
				ShowDialog(playerid, DIALOG_BANK_HASACCOUNT);
			}
			else
			{
				LeaveProperty(playerid);
			}
		}
		// Withdraw money from bank account
		case DIALOG_BANK_WITHDRAWMONEY:
		{
			if (response)
			{
				if (!strlen(inputtext))
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 19);
					ShowDialog(playerid, DIALOG_BANK_WITHDRAWMONEY);
				}
				else
				{
					new Float:money = floatstr(inputtext);
					if(money > PVar:playerid[BANKMONEY])
					{
						SendClientMessageEx(playerid, COLOR_ERROR, 25);
						ShowDialog(playerid, DIALOG_BANK_WITHDRAWMONEY);
					}
					else
					{
						SetPlayerMoney(playerid, MONEY_BANK, floatsub(PVar:playerid[BANKMONEY], money));
						SetPlayerMoney(playerid, MONEY_CASH, floatadd(PVar:playerid[MONEY], money));
						SendClientMessageEx(playerid, COLOR_INFO, 26, money);
						ShowDialog(playerid, DIALOG_BANK_HASACCOUNT);
					}
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_BANK_HASACCOUNT);
			}
		}
		case DIALOG_BUYHOUSE:
		{
			if (response)
			{
				new buildingID = PVar:playerid[DIALOGPROPERTYID];
				new Float:price = floatstr(GetMySQLValue("properties", "Price", "ID", val2str(buildingID)));
				if (price <= PVar:playerid[BANKMONEY])
				{
					TogglePlayerControllable(playerid, false);
					PlayAudioStreamForPlayer(playerid, "http://audio.grgserver.net/mission_complete2.ogg");
					MySQLQuery("SELECT * FROM `properties` LEFT JOIN `pickups` ON `properties`.`PickupID` = `pickups`.`ID` WHERE `properties`.`ID` = '%d'", buildingID);
					mysql_store_result();
					SetPlayerCameraPos(playerid, floatstr(GetMySQLField("CameraPosX")), floatstr(GetMySQLField("CameraPosY")), floatstr(GetMySQLField("CameraPosZ")));
					SetPlayerCameraLookAt(playerid, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")));
					mysql_free_result();
					GameTextForPlayer(playerid, LanguageString(playerid, 28), 8000, 1);
					SetMySQLValue("properties", "OwnerUserID", val2str(PVar:playerid[USERID]), "ID", val2str(buildingID));
					GivePlayerMoneyEx(playerid, MONEY_BANK, -price);
					ReloadPickup(strval(GetMySQLValue("properties", "PickupID", "ID", val2str(buildingID))));
					SetTimerEx("Timer_ScreenFader", 8000, false, "ddddddd", playerid, 0, 0, 0, 5, 0, FADE_PROPERTYBOUGHT_BLACK);
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 29, price, PVar:playerid[BANKMONEY]);
				}
			}
		}
		case DIALOG_BUYVEHICLE:
		{
			if (response)
			{
				new saveID = vehicles[GetPlayerVehicleID(playerid)][VEHICLE_SAVEID];
				new Float:price = floatstr(GetMySQLValue("vehicles", "Price", "ID", val2str(saveID)));
				if (price <= PVar:playerid[BANKMONEY])
				{
					GivePlayerMoneyEx(playerid, MONEY_CASH, -price);
					SetMySQLValue("vehicles", "OwnerUserID", val2str(PVar:playerid[USERID]), "ID", val2str(saveID));
					SavePlayer(playerid);
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 27, price, PVar:playerid[BANKMONEY]);
					RemovePlayerFromVehicle(playerid);
				}
			}
			else
			{
				RemovePlayerFromVehicle(playerid);
			}
		}
		case DIALOG_CHANGEPASSWORD_STEP1:
		{
			if (response)
			{
				if (!strcmp(GetUserDBValue(playerid, "Password"), MD5(inputtext), true))
				{
					ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP2);
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 30);
					ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP1);
				}
			}
		}
		case DIALOG_CHANGEPASSWORD_STEP2:
		{
			if (response)
			{
				if (strlen(inputtext) >= REGISTER_PASSWORD_MIN && strlen(inputtext) <= REGISTER_PASSWORD_MAX)
				{
					SetPVarStr:playerid[CHANGEPASSWORD][REGISTER_PASSWORD_MAX](inputtext);
					ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP3);
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 31, REGISTER_PASSWORD_MIN, REGISTER_PASSWORD_MAX);
					ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP2);
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP1);
			}
		}
		case DIALOG_CHANGEPASSWORD_STEP3:
		{
			if (response)
			{
				if (!strcmp(PVar:playerid[CHANGEPASSWORD], inputtext))
				{
					SetUserDBValue(playerid, "Password", MD5(inputtext));
					SendClientMessageEx(playerid, COLOR_INFO, 20);
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 32);
					ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP3);
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP2);
			}
		}
		case DIALOG_CHATMODE:
		{
			if (response)
			{
				if (IsStr(inputtext, LanguageString(playerid, 311)))
				{
					PVar:playerid[CHATMODE] = CHATMODE_INRANGE;
				}
				if (IsStr(inputtext, LanguageString(playerid, 310)))
				{
					PVar:playerid[CHATMODE] = CHATMODE_ALL;
				}
				if (IsStr(inputtext, "Job"))
				{
					PVar:playerid[CHATMODE] = CHATMODE_JOB;
				}
				if (IsStr(inputtext, "Admins"))
				{
					PVar:playerid[CHATMODE] = CHATMODE_ADMINS;
				}
				SendClientMessageEx(playerid, COLOR_INFO, 313, GetChatModeName(playerid, PVar:playerid[CHATMODE]));
			}
		}
		case DIALOG_ESTATEAGENTS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:
					{
						PVar:playerid[JOBID] = JOB_ESTATEAGENTS;
					}
					case 1:
					{
						PVar:playerid[JOBID] = 0;
					}
				}
			}
		}
		case DIALOG_FUNACTION:
		{
			if (response)
			{
				new action;
				switch (listitem)
				{
					case 0:// Stop
						action = SPECIAL_ACTION_NONE;
					case 1:// Dance 1
						action = SPECIAL_ACTION_DANCE1;
					case 2:// Dance 2
						action = SPECIAL_ACTION_DANCE2;
					case 3:// Dance 3
						action = SPECIAL_ACTION_DANCE3;
					case 4:// Dance 4
						action = SPECIAL_ACTION_DANCE4;
					case 5:// Hands Up
						action = SPECIAL_ACTION_HANDSUP;
					case 6:// Setting
						action = SPECIAL_ACTION_SITTING;
					case 7:// Drink Beer
						action = SPECIAL_ACTION_DRINK_BEER;
					case 8:// Smoke Ciggy
						action = SPECIAL_ACTION_SMOKE_CIGGY;
					case 9:// Drink Wine
						action = SPECIAL_ACTION_DRINK_WINE;
					case 10:// Drink Sprunk
						action = SPECIAL_ACTION_DRINK_SPRUNK;
					case 11:// Pissing
						action = SPECIAL_ACTION_PISSING;
				}
				SetPlayerSpecialAction(playerid, action);
			}
		}
		case DIALOG_GIVEWEAPON:
		{
			if (response)
			{
				new weaponID;
				new name[STRINGLENGTH_WEAPONNAME];
				sscanf(inputtext, "p:ds", weaponID, name);
				if (GivePlayerWeaponEx(playerid, weaponID))
				{
					SendClientMessageEx(playerid, COLOR_INFO, 69, weapons[weaponID][WEAPON_NAME]);
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 68);
				}
			}
		}
		case DIALOG_HOTEL_HASROOM:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:// Enter hotel room
					{
						TeleportToInterior(playerid, HOTEL_ROOM_INTERIOR);
						SetPlayerVirtualWorld(playerid, playerid);
					}
					case 1:// Cancel hotel room
					{
						MySQLQuery("UPDATE `hotelrooms` SET `OwnerUserID` = '0' WHERE `PropertyID` = '%d' AND `RoomID` = '%d'", PVar:playerid[CURRENTPROPERTYID], PVar:playerid[HOTEL_ROOMID]);
						SendClientMessageEx(playerid, COLOR_INFO, 321);
						LeaveProperty(playerid);
					}
					case 2:// Room information
					{
						MySQLQuery("SELECT * FROM `hotelrooms` WHERE `PropertyID` = '%d' AND `RoomID` = '%d'", PVar:playerid[CURRENTPROPERTYID], PVar:playerid[HOTEL_ROOMID]);
						mysql_store_result();
						new Float:price = floatstr(GetMySQLField("Price"));
						mysql_free_result();
						SendClientMessageEx(playerid, COLOR_INFO, 320, price);
						ShowDialog(playerid, DIALOG_HOTEL_HASROOM);
					}
				}
			}
			else
			{
				LeaveProperty(playerid);
			}
		}
		case DIALOG_HOTEL_ROOMLIST:
		{
			if (response)
			{
				new string[256];
				sscanf(inputtext, "p:ds", PVar:playerid[HOTEL_ROOMID], string);
				MySQLQuery("UPDATE `hotelrooms` SET `OwnerUserID` = '%d' WHERE `PropertyID` = '%d' AND `RoomID` = '%d'", PVar:playerid[USERID], PVar:playerid[CURRENTPROPERTYID], PVar:playerid[HOTEL_ROOMID]);
				TeleportToInterior(playerid, HOTEL_ROOM_INTERIOR);
				SetPlayerVirtualWorld(playerid, playerid);
			}
			else
			{
				LeaveProperty(playerid);
			}
		}
		case DIALOG_HOUSE:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:// Enter
					{
						TeleportToProperty(playerid, PVar:playerid[DIALOGPROPERTYID]);
					}
					case 1:// Sell
					{
						MySQLQuery("UPDATE `properties` SET `OwnerUserID` = '0' WHERE `ID` = '%d'", PVar:playerid[DIALOGPROPERTYID]);
						GivePlayerMoneyEx(playerid, MONEY_BANK, floatstr(GetMySQLValue("properties", "Price", "ID", val2str(PVar:playerid[DIALOGPROPERTYID]))));
						ReloadPickup(strval(GetMySQLValue("properties", "PickupID", "ID", val2str(PVar:playerid[DIALOGPROPERTYID]))));
						SendClientMessageEx(playerid, COLOR_INFO, 330);
					}
				}
			}
		}
		case DIALOG_LOGIN:
		{
			if (response)
			{
				if (strlen(inputtext))
				{
					MySQLQuery("SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
					mysql_store_result();
					if (!strcmp(MD5(inputtext), GetMySQLField("Password"), true))
					{
						PVar:playerid[USERID] = strval(GetMySQLField("ID"));
					}
					else
					{
						SendClientMessageEx(playerid, COLOR_ERROR, 30);
						ShowDialog(playerid, DIALOG_LOGIN);
					}
					mysql_free_result();
					if (PVar:playerid[USERID])
					{
						MySQLQuery("UPDATE `users` SET `LoginTime` = NOW(), `ClientVersion` = '%s' WHERE `ID` = '%d'", GetPlayerVersionEx(playerid), PVar:playerid[USERID]);
						printf("Player logged in: %s (UserID: %d)", GetPlayerNameEx(playerid), PVar:playerid[USERID]);
						TogglePlayerSpectating(playerid, false);
						LoadPlayer(playerid);
						ReloadTextDraws(playerid);
						PVar:playerid[SPAWNAFTERLOGIN] = true;
						SendClientMessageEx(playerid, COLOR_INFO, 35);
					}
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 36);
					ShowDialog(playerid, DIALOG_LOGIN);
				}
			}
			else
			{
				SendClientMessageEx(playerid, COLOR_INFO, 37);
				Kick(playerid);
			}
			return true;
		}
		case DIALOG_NAVITARGET:
		{
			if (response)
			{
				new Float:target[3];
				if (IsStr(inputtext, LanguageString(playerid, 173)))// Bank
				{
					new pickupID = GetClosestPickup(playerid, "BANK");
					target[0] = pickups[pickupID][PICKUP_POSX];
					target[1] = pickups[pickupID][PICKUP_POSY];
					target[2] = pickups[pickupID][PICKUP_POSZ];
				}
				if (IsStr(inputtext, LanguageString(playerid, 384)))// Gas station
				{
					new pickupID = GetClosestPickup(playerid, "GASSTATION");
					target[0] = pickups[pickupID][PICKUP_POSX];
					target[1] = pickups[pickupID][PICKUP_POSY];
					target[2] = pickups[pickupID][PICKUP_POSZ];
				}
				if (IsStr(inputtext, LanguageString(playerid, 174)))// Hotel
				{
					new pickupID = GetClosestPickup(playerid, "HOTEL");
					target[0] = pickups[pickupID][PICKUP_POSX];
					target[1] = pickups[pickupID][PICKUP_POSY];
					target[2] = pickups[pickupID][PICKUP_POSZ];
				}
				if (IsStr(inputtext, LanguageString(playerid, 175)))// House
				{
					new pickupID = GetClosestPickup(playerid, "HOUSE");
					target[0] = pickups[pickupID][PICKUP_POSX];
					target[1] = pickups[pickupID][PICKUP_POSY];
					target[2] = pickups[pickupID][PICKUP_POSZ];
				}
				if (IsStr(inputtext, LanguageString(playerid, 342)))// Target on map
				{
					if (PVar:playerid[MAP_POSX] && PVar:playerid[MAP_POSY] && PVar:playerid[MAP_POSZ])
					{
						target[0] = PVar:playerid[MAP_POSX];
						target[1] = PVar:playerid[MAP_POSY];
						target[2] = PVar:playerid[MAP_POSZ];
					}
					else
					{
						SendClientMessageEx(playerid, COLOR_ERROR, 264);
						return false;
					}
				}
				if (!target[0] && !target[1] && !target[2])
				{
					new typeID = GetNavigationLocationTypeByName(playerid, inputtext);
					if (typeID)
					{
						GetClosestNavigationLocation(playerid, typeID, target[0], target[1], target[2]);
					}
				}
				if (target[0] || target[1] || target[2])
				{
					SetPlayerCheckpointEx(playerid, CHECKPOINT_NAVITARGET, target[0], target[1], target[2], 5.0);
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 343);
				}
			}
		}
		case DIALOG_ORDERVEHICLE:
		{
			if (response)
			{
				new modelID = strval(GetMySQLValue("vehiclemodels", "ID", "Name", inputtext));
				if (modelID)
				{
					new missionID = CreateJob(playerid, JOB_VEHICLEDEALER);
					if (missionID)
					{
						AddJobData(missionID, "Type", "GetOrderedVehicle");
						AddJobData(missionID, "VehicleModelID", val2str(modelID));
						SendClientMessageEx(playerid, COLOR_INFO, 38, missionID);
					}
				}
			}
		}
		case DIALOG_POLICE_JOB:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Buy police
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Work in progress");
					}
					case 1: // Apply to police
					{
						if(PVar:playerid[JOBID] >= 0)
						{
							SendClientMessage(playerid, COLOR_SYSTEM, "Work in progress");
						}
						else
						{
							SendClientMessageEx(playerid, COLOR_ERROR, 39);
						}
					}
					case 2: // Enter
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Work in progress");
					}
				}
			}
		}
		case DIALOG_POLICE_OPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Accept jobs
					{
						ShowDialog(playerid, DIALOG_ACCEPT);
					}
					case 1: // Finanzen
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Work in progress");
					}
					case 2: // Applications overview
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Work in progress");
					}
					case 3: // Cancel job
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Work in progress");
					}
					case 4: // Enter
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Work in progress");
					}
				}
			}
		}
		case DIALOG_PREVIEWINFO:
		{
			if (PVar:playerid[REGISTERED])
			{
				ShowDialog(playerid, DIALOG_LOGIN);
			}
			else
			{
				ShowDialog(playerid, DIALOG_REGISTER_PASSWORD1);
			}
		}
		case DIALOG_REFUEL:
		{
			if (response && strlen(inputtext))
			{
				new Float:amount = floatstr(inputtext);
				new vehicleID = GetPlayerVehicleID(playerid);
				new modelID = GetVehicleModel(vehicleID);
				if (modelID >= 400 && modelID <= 611)
				{
					new Float:maximum = floatsub(vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL], vehicles[vehicleID][VEHICLE_CURRENTFUEL]);
					if (amount > maximum)
					{
						amount = maximum;
					}
					TogglePlayerControllable(playerid, false);
					SetVehicleEngineState(vehicleID, false);
					GameTextForPlayer(playerid, LanguageString(playerid, 265), 3000, 4);
					Timer_RefuelVehicle(playerid, amount);
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 146);
				}
			}
		}
		case DIALOG_REGISTER_BIRTHDATE:
		{
			if (response)
			{
				new day;
				new month;
				new year;
				if (sscanf(inputtext, "p.ddd", day, month, year))
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 40);
					ShowDialog(playerid, DIALOG_REGISTER_BIRTHDATE);
				}
				else
				{
					if (day > 0 && day <= 31 && month > 0 && month <=12 && year > 1900 && year < 2100)
					{
						SetPVarStr:playerid[BIRTHDATE][STRINGLENGTH_DATETIME]("%d-%02d-%02d", year, month, day);
						ShowDialog(playerid, DIALOG_REGISTER_LOCATION);
					}
					else
					{
						SendClientMessageEx(playerid, COLOR_ERROR, 41);
						ShowDialog(playerid, DIALOG_REGISTER_BIRTHDATE);
					}
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_REGISTER_GENDER);
			}
		}
		case DIALOG_REGISTER_GENDER:
		{
			if (response)
			{
				if (listitem)
				{
					PVar:playerid[GENDER] = 'F';// Female
					PVar:playerid[SKIN] = REGISTER_SKIN_FEMALE;
				}
				else
				{
					PVar:playerid[GENDER] = 'M';// Male
					PVar:playerid[SKIN] = REGISTER_SKIN_MALE;
				}
				SetPlayerSkin(playerid, PVar:playerid[SKIN]);
				ShowDialog(playerid, DIALOG_REGISTER_BIRTHDATE);
			}
			else
			{
				ShowDialog(playerid, DIALOG_REGISTER_PASSWORD2);
			}
		}
		case DIALOG_REGISTER_LOCATION:
		{
			if (response)
			{
				SetPVarStr:playerid[REGISTERLOCATION][STRINGLENGTH_LOCATION](inputtext);
				PVar:playerid[REGISTER_SELECTSKIN] = true;
			}
			else
			{
				ShowDialog(playerid, DIALOG_REGISTER_GENDER);
			}
		}
		case DIALOG_REGISTER_PASSWORD1:
		{
			if (response)
			{
				if (strlen(inputtext) >= REGISTER_PASSWORD_MIN && strlen(inputtext) <= REGISTER_PASSWORD_MAX)
				{
					SetPVarStr:playerid[REGISTERPASSWORD][REGISTER_PASSWORD_MAX](inputtext);
					ShowDialog(playerid, DIALOG_REGISTER_PASSWORD2);
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 31, REGISTER_PASSWORD_MIN, REGISTER_PASSWORD_MAX);
					ShowDialog(playerid, DIALOG_REGISTER_PASSWORD1);
				}
			}
			else
			{
				SendClientMessageEx(playerid, COLOR_INFO, 37);
				Kick(playerid);
			}
		}
		case DIALOG_REGISTER_PASSWORD2:
		{
			if (response)
			{
				if (!strcmp(inputtext, PVar:playerid[REGISTERPASSWORD]))
				{
					ShowDialog(playerid, DIALOG_REGISTER_GENDER);
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 32);
					ShowDialog(playerid, DIALOG_REGISTER_PASSWORD1);
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_REGISTER_PASSWORD1);
			}
			return true;
		}
		case DIALOG_REPAIR:
		{
			if (response)
			{
				new vehicleID = GetPlayerVehicleID(playerid);
				if (vehicleID)
				{
					RepairVehicle(vehicleID);
					GivePlayerMoneyEx(playerid, MONEY_CASH, -PVar:playerid[REPAIR_PRICE]);
					GivePlayerMoneyEx(PVar:playerid[REPAIR_EXECUTOR], MONEY_CASH, PVar:playerid[REPAIR_PRICE]);
					SendClientMessageEx(playerid, COLOR_INFO, 304);
					SendClientMessageEx(PVar:playerid[REPAIR_EXECUTOR], COLOR_INFO, 305, GetPlayerNameEx(playerid), FormatMoney(PVar:playerid[REPAIR_PRICE]));
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 146);
				}
			}
			else
			{
				SendClientMessageEx(PVar:playerid[REPAIR_EXECUTOR], COLOR_ERROR, 306, GetPlayerNameEx(playerid));
			}
			return true;
		}
		case DIALOG_RESTARTGAMEMODE:
		{
			if (response)
			{
				PlayerLoop(playerID)
				{
					SavePlayer(playerID);
				}
				SendClientMessageEx(playerid, COLOR_INFO, 42);
				PlayerLoop(playerID)
				{
					if (playerID != playerid && IsPlayerConnected(playerID))
					{
						SendClientMessageEx(playerID, COLOR_INFO, 43, playerid);
					}
				}
				printf("%s has restarted the gamemode", GetPlayerNameEx(playerid));
				SendRconCommand("gmx");
			}
		}
		case DIALOG_SCHOOLDRIVER:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:
					{
						PVar:playerid[JOBID] = JOB_SCHOOLDRIVER;
					}
					case 1:
					{
						PVar:playerid[JOBID] = 0;
					}
				}
			}
		}
		case DIALOG_SELECTINTERIOR:
		{
			new interiorDialogID = PVar:playerid[INTERIORDIALOGID];
			new interiorID;
			if (!response)
			{
				OnInteriorDialogSelect(playerid, interiorDialogID, 0);
				return true;
			}
			if (!strcmp(inputtext, LanguageString(playerid, 171), true))
			{
				ShowDialog(playerid, DIALOG_SELECTINTERIOR, interiorDialogID, 0);
				return true;
			}
			if (!strcmp(inputtext, LanguageString(playerid, 177), true))
			{
				ShowDialog(playerid, DIALOG_SELECTINTERIOR, interiorDialogID, 75);
				return true;
			}
			interiorID = strval(GetMySQLValue("interiors", "ID", "Name", inputtext));
			OnInteriorDialogSelect(playerid, interiorDialogID, interiorID);
		}
		case DIALOG_SPAWNVEHICLE:
		{
			if (response)
			{
				new modelID;
				new name[STRINGLENGTH_VEHICLENAME];
				if (!sscanf(inputtext, "p:ds", modelID, name))
				{
					if (modelID)
					{
						SpawnVehicle(playerid, modelID, PVar:playerid[SPAWNVEHICLE_COLOR1], PVar:playerid[SPAWNVEHICLE_COLOR1], true);
					}
				}
			}
		}
		case DIALOG_STATS:
		{
			if (response)
			{
				return COMMAND_OK;
			}
		}
		case DIALOG_TAXI:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:
					{
						PVar:playerid[JOBID] = JOB_TAXI;
					}
					case 1:
					{
						PVar:playerid[JOBID] = 0;
					}
				}
			}
		}
		case DIALOG_TELEPORTLOCATIONS:
		{
			if (response)
			{
				MySQLQuery("SELECT * FROM `teleports` WHERE `Name` = '%s'", MySQLEscapeString(inputtext));
				mysql_store_result();
				if (mysql_num_rows())
				{
					Teleport(playerid, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), floatstr(GetMySQLField("Angle")), strval(GetMySQLField("Interior")), 0);
				}
				mysql_free_result();
			}
		}
		case DIALOG_TRUCKER_JOB:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Kaufe Trucker
					{
						// TODO: MySQL Daten bank hinzufügen bei Jobs die OwnerUserID zum kaufen.
						SendClientMessage(playerid, COLOR_SYSTEM, "Work in progress");
					}
					case 1: // Bewerben für den Job Trucker
					{
						if(PVar:playerid[JOBID] >= 0)
						{
							// TODO: MySQL DB erstellen für Bewerbung jeglicher Jobarten.
							// TODO: Diese der Owner des Jobs bearbeiten kann anneehmen kann und ablehnen kann.
							SendClientMessage(playerid, COLOR_SYSTEM, "Work in progress");
						}
						else
						{
							SendClientMessageEx(playerid, COLOR_ERROR, 39);
						}
					}
				}
			}
		}
		case DIALOG_TRUCKER_OPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Aufträge
					{
						ShowDialog(playerid, DIALOG_ACCEPT);
					}
					case 1: // Finanzen
					{
						// TODO: Finanzen für jeden Job erstellen: Job Guthaben
						SendClientMessage(playerid, COLOR_SYSTEM, "Work in progress");
					}
					case 2: // Kündigen
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Work in progress");
					}
					case 3: // Bewerbungs übersicht
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Work in progress");
					}
				}
			}
		}
		case DIALOG_UPGRADEVEHICLE:
		{
			if (!strcmp(inputtext, LanguageString(playerid, 395)))// Front headlights
			{
				PVar:playerid[UPGRADEVEHICLE_LIGHTTYPE] = 1;
				ShowDialog(playerid, DIALOG_UPGRADEVEHICLE_LIGHT);
			}
			if (!strcmp(inputtext, LanguageString(playerid, 375)))// Neon lights
			{
				PVar:playerid[UPGRADEVEHICLE_LIGHTTYPE] = 2;
				ShowDialog(playerid, DIALOG_UPGRADEVEHICLE_LIGHT);
			}
		}
		case DIALOG_UPGRADEVEHICLE_LIGHT:
		{
			if (response)
			{
				new vehicleID = GetPlayerVehicleID(playerid);
				if (vehicleID)
				{
					switch (PVar:playerid[UPGRADEVEHICLE_LIGHTTYPE])
					{
						case 1:
						{
							AddNeonLight(vehicleID, NEONTYPE_FRONT_LEFT, listitem);
							AddNeonLight(vehicleID, NEONTYPE_FRONT_RIGHT, listitem);
							VehicleProperty:vehicleID[FRONTLIGHTID] = listitem + 1;
						}
						case 2:
						{
							AddNeonLight(vehicleID, NEONTYPE_LEFT, listitem);
							AddNeonLight(vehicleID, NEONTYPE_RIGHT, listitem);
							VehicleProperty:vehicleID[NEONLIGHTID] = listitem + 1;
						}
					}
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 146);
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_UPGRADEVEHICLE);
			}
		}
		case DIALOG_VEHICLEDEALER_JOB:
		{
			if (response)
			{
				PVar:playerid[JOBID] = JOB_VEHICLEDEALER;
				SendClientMessageEx(playerid, COLOR_INFO, 355);
			}
		}
		case DIALOG_VEHICLEDEALER_OPTIONS:
		{
			if (response)
			{
				if (!strcmp(inputtext, LanguageString(playerid, 356)))// End work
				{
					PVar:playerid[ATWORK] = false;
					new time = gettime() - PVar:playerid[WORKSTARTTIME];
					SendClientMessageEx(playerid, COLOR_INFO, 360, time / 60 / 60);
				}
				if (!strcmp(inputtext, LanguageString(playerid, 357)))// Start work
				{
					PVar:playerid[ATWORK] = true;
					PVar:playerid[WORKSTARTTIME] = gettime();
				}
				if (!strcmp(inputtext, LanguageString(playerid, 358)))// Cancel job
				{
					PVar:playerid[JOBID] = JOB_UNEMPLOYED;
					SendClientMessageEx(playerid, COLOR_INFO, 359);
				}
			}
		}
	}
	return false;
}