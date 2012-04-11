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
		case DIALOG_ARMEE:
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
		// Asked for the name of the new building
		case DIALOG_ADDBUILDING_NAME:
		{
			if (response)
			{
				new Float:posX;
				new Float:posY;
				new Float:posZ;
				new pickupID;
				GetPlayerPos(playerid, posX, posY, posZ);
				pickupID = AddPickup(-1, PVar:playerid[ADDBUILDING_TYPE], posX, posY, posZ, true);
				if (pickupID > 0)
				{
					MySQLQuery("INSERT INTO `buildings` (`PickupID`, `InteriorID`, `Name`, `Price`) VALUES ('%d', '%d', '%s', '%f')", pickupID, PVar:playerid[ADDBUILDING_INTERIORID], MySQLEscapeString(inputtext), PVar:playerid[ADDBUILDING_PRICE]);
					SendClientMessageEx(playerid, COLOR_INFO, 10, inputtext, PVar:playerid[ADDBUILDING_PRICE], mysql_insert_id());
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 6);
				}
			}
			else
			{
				ShowInteriorDialog(playerid, INTERIORDIALOG_ADDBUILDING);
			}
		}
		// Asked for the type of the new building
		case DIALOG_ADDBUILDING_TYPE:
		{
			if (response)
			{
				new type[STRINGLENGTH_BUILDINGTYPE];
				switch (listitem)
				{
					case 0:
						type = "BANK";
					case 1:
						type = "HOTEL";
					case 2:
						type = "HOUSE";
					case 3:
						type = "POLICE";
				}
				SetPVarStr:playerid[ADDBUILDING_TYPE][STRINGLENGTH_BUILDINGTYPE](type);
				ShowInteriorDialog(playerid, INTERIORDIALOG_ADDBUILDING);
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
		// ???
		case DIALOG_APPLICATION_PLAYER:
		{
			if (response)
			{
				SendClientMessage(playerid, COLOR_INFO, "Work in process!");
			}
		}
		// Cancel the bank account
		case DIALOG_BANK_CANCELACCOUNT:
		{
			if (response)
			{
				SetUserDBValue(playerid, "BankID", "0");
				LeaveBuilding(playerid);
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
				LeaveBuilding(playerid);
			}
		}
		// Create a new bank account
		case DIALOG_BANK_NEWACCOUNT:
		{
			if (response)
			{
				new bankID = strval(GetMySQLValue("bankbranches", "BankID", "BuildingID", val2str(PVar:playerid[CURRENTBUILDINGID])));
				SetUserDBValue(playerid, "BankID", val2str(bankID));
				SendClientMessageEx(playerid, COLOR_INFO, 216, GetMySQLValue("banks", "Name", "ID", val2str(bankID)));
				ShowDialog(playerid, DIALOG_BANK_HASACCOUNT);
			}
			else
			{
				LeaveBuilding(playerid);
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
		case DIALOG_BUYVEHICLE:
		{
			if (response)
			{
				new saveID = vehicles[GetPlayerVehicleID(playerid)][VEHICLE_SAVEID];
				new Float:price = floatstr(GetMySQLValue("savedvehicles", "Price", "ID", val2str(saveID)));
				if (price <= PVar:playerid[MONEY])
				{
					GivePlayerMoneyEx(playerid, MONEY_CASH, -price);
					SetMySQLValue("savedvehicles", "OwnerUserID", val2str(PVar:playerid[USERID]), "ID", val2str(saveID));
					SavePlayer(playerid);
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 27, price, PVar:playerid[MONEY]);
					RemovePlayerFromVehicle(playerid);
				}
			}
			else
			{
				RemovePlayerFromVehicle(playerid);
			}
		}
		case DIALOG_BUYHOUSE:
		{
			if (response)
			{
				new buildingID = PVar:playerid[DIALOGBUILDINGID];
				new Float:price = floatstr(GetMySQLValue("buildings", "Price", "ID", val2str(buildingID)));
				if (price <= PVar:playerid[MONEY])
				{
					GivePlayerMoneyEx(playerid, MONEY_CASH, -price);
					SetMySQLValue("buildings", "OwnerUserID", val2str(PVar:playerid[USERID]), "ID", val2str(buildingID));
					ReloadPickup(strval(GetMySQLValue("buildings", "PickupID", "ID", val2str(buildingID))));
					SendClientMessageEx(playerid, COLOR_INFO, 28);
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_ERROR, 29, price, PVar:playerid[MONEY]);
				}
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
		case DIALOG_HOTEL_MAIN_AVAILABLE:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Buy
					{
						new buildingID = PVar:playerid[DIALOGBUILDINGID];
						new Float:price = floatstr(GetMySQLValue("buildings", "Price", "ID", val2str(buildingID)));
						if (price <= PVar:playerid[MONEY])
						{
							GivePlayerMoneyEx(playerid, MONEY_CASH, -price);
							SetMySQLValue("buildings", "OwnerUserID", val2str(PVar:playerid[USERID]), "ID", val2str(buildingID));
							ReloadPickup(strval(GetMySQLValue("buildings", "PickupID", "ID", val2str(buildingID))));
							SendClientMessageEx(playerid, COLOR_INFO, 33);
							ShowDialog(playerid, DIALOG_HOTEL_MAIN_OWNER);
						}
						else
						{
							SendClientMessageEx(playerid, COLOR_ERROR, 34, price, PVar:playerid[MONEY]);
							ShowDialog(playerid, DIALOG_HOTEL_MAIN_AVAILABLE);
						}
					}
					case 1: // Rent
					{
						ShowDialog(playerid, DIALOG_HOTEL_MAIN_AVAILABLE);
					}
					case 2: // Enter
					{
						TeleportToBuilding(playerid, PVar:playerid[DIALOGBUILDINGID]);
					}
				}
			}
			else
			{
				SetPlayerPosEx(playerid, PVar:playerid[HOTEL_PREVIOUSPOSITION_X], PVar:playerid[HOTEL_PREVIOUSPOSITION_Y], PVar:playerid[HOTEL_PREVIOUSPOSITION_Z]);
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
			}
		}
		case DIALOG_HOTEL_MAIN_BOUGHT:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Enter
					{
						ShowDialog(playerid, DIALOG_HOTEL_MAIN_BOUGHT);
					}
					case 1: // Rent
					{
						ShowDialog(playerid, DIALOG_HOTEL_MAIN_BOUGHT);
					}
					case 2: // Stop contract
					{
						ShowDialog(playerid, DIALOG_HOTEL_MAIN_BOUGHT);
					}
				}
			}
			else
			{
				SetPlayerPosEx(playerid, PVar:playerid[HOTEL_PREVIOUSPOSITION_X], PVar:playerid[HOTEL_PREVIOUSPOSITION_Y], PVar:playerid[HOTEL_PREVIOUSPOSITION_Z]);
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
			}
		}
		case DIALOG_HOTEL_MAIN_OWNER:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Enter
					{
						TeleportToBuilding(playerid, PVar:playerid[DIALOGBUILDINGID]);
					}
					case 1: // Sell
					{
						ShowDialog(playerid, DIALOG_HOTEL_MAIN_OWNER);
					}
					case 2: // Incoming (Money)
					{
						ShowDialog(playerid, DIALOG_HOTEL_MAIN_OWNER);
					}
					case 3: // Room options
					{
						ShowDialog(playerid, DIALOG_HOTEL_ROOMS_LIST);
					}
				}
			}
			else
			{
				SetPlayerPosEx(playerid, PVar:playerid[HOTEL_PREVIOUSPOSITION_X], PVar:playerid[HOTEL_PREVIOUSPOSITION_Y], PVar:playerid[HOTEL_PREVIOUSPOSITION_Z]);
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
			}
		}
		case DIALOG_HOTEL_ROOMS_FREEOPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:// Set room rent price
					{
						ShowDialog(playerid, DIALOG_HOTEL_ROOMS_SETPRICE);
					}
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_HOTEL_ROOMS_LIST);
			}
		}
		case DIALOG_HOTEL_ROOMS_LIST:
		{
			if (response)
			{
				new playerName[MAX_PLAYER_NAME];
				new roomID;
				if (!sscanf(inputtext, "p:ds", roomID, playerName))
				{
					PVar:playerid[HOTEL_OPTIONS_ROOMID] = roomID;
					if (strval(GetMySQLValue("hotelrooms", "OwnerUserID", "RoomID", val2str(roomID))))
					{
						ShowDialog(playerid, DIALOG_HOTEL_ROOMS_OWNEDOPTIONS);
					}
					else
					{
						ShowDialog(playerid, DIALOG_HOTEL_ROOMS_FREEOPTIONS);
					}
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_HOTEL_MAIN_OWNER);
			}
		}
		case DIALOG_HOTEL_ROOMS_OWNEDOPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:// Kick renter
					{
						// Kick
					}
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_HOTEL_ROOMS_LIST);
			}
		}
		case DIALOG_HOTEL_ROOMS_SETPRICE:
		{
			if (response)
			{
				MySQLQuery("UPDATE `hotelrooms` SET `Price` = '%s' WHERE `BuildingID` = '%d' AND `RoomID` = '%d'", MySQLEscapeString(inputtext), PVar:playerid[DIALOGBUILDINGID], PVar:playerid[HOTEL_OPTIONS_ROOMID]);
			}
			ShowDialog(playerid, DIALOG_HOTEL_ROOMS_LIST);
		}
		case DIALOG_HOUSEOPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:// Enter
					{
						TeleportToBuilding(playerid, PVar:playerid[DIALOGBUILDINGID]);
					}
					case 1:// Sell
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Haus verkaufen");
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
						PVar:playerid[USERID] = strval(GetMySQLField("UserID"));
					}
					else
					{
						SendClientMessageEx(playerid, COLOR_ERROR, 30);
						ShowDialog(playerid, DIALOG_LOGIN);
					}
					mysql_free_result();
					if (PVar:playerid[USERID])
					{
						MySQLQuery("UPDATE `users` SET `LoginTime` = NOW(), `ClientVersion` = '%s' WHERE `UserID` = '%d'", GetPlayerVersionEx(playerid), PVar:playerid[USERID]);
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
					case 0: // Buy Police
					{
						SendClientMessage(playerid, COLOR_INFO, "Kaufen noch in Bearbeitung!");
					}
					case 1: // Bewerben by Police
					{
						if(PVar:playerid[JOBID] >= 0)
						{
							SendClientMessage(playerid, COLOR_INFO, "Bewerben noch in Bearbeitung!");
						}
						else
						{
							SendClientMessageEx(playerid, COLOR_ERROR, 39);
						}
					}
					case 2: // Betreten
					{
						SendClientMessage(playerid, COLOR_INFO, "Betreten noch in Bearbeitung.");
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
					case 0: // Aufträge annehmen
					{
						ShowDialog(playerid, DIALOG_ACCEPT);
					}
					case 1: // Finanzen
					{
						SendClientMessage(playerid, COLOR_INFO, "Finanzen noch in Bearbeitung!");
					}
					case 2: // bewerbungs übersicht
					{
						SendClientMessage(playerid, COLOR_INFO, "bewerbung noch in Bearbeitung!");
					}
					case 3: // Job Kündigen
					{
						SendClientMessage(playerid, COLOR_INFO, "Kündigung noch in Bearbeitung!");
					}
					case 4: // Betreten
					{
						SendClientMessage(playerid, COLOR_INFO, "Betreten noch in Bearbeitung!");
					}
				}
			}
		}
		case DIALOG_RADIO:
		{
			if (response)
			{
				PlayRadioStation(playerid, strval(GetMySQLValue("radiostations", "ID", "Name", inputtext)));
			}
		}
		case DIALOG_REFUEL:
		{
			if (response && strlen(inputtext))
			{
				new Float:amount = floatstr(inputtext);
				new vehicleID = GetPlayerVehicleID(playerid);
				new Float:maximum = floatsub(vehicleModels[GetVehicleModel(vehicleID) - 400][VEHICLEMODEL_MAXFUEL], vehicles[vehicleID][VEHICLE_CURRENTFUEL]);
				if (amount > maximum)
				{
					amount = maximum;
				}
				TogglePlayerControllable(playerid, false);
				SetVehicleEngineState(vehicleID, false);
				GameTextForPlayer(playerid, "Dein Fahrzeug wird getankt. Bitte warten...", 3000, 4);
				Timer_RefuelVehicle(playerid, amount);
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
				switch (listitem)
				{
					case 0:
					{
						PVar:playerid[GENDER] = 'M';// Male
						SetPlayerSkin(playerid, REGISTER_SKIN_MALE);
					}
					case 1:
					{
						PVar:playerid[GENDER] = 'F';// Female
						SetPlayerSkin(playerid, REGISTER_SKIN_FEMALE);
					}
				}
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
						SendClientMessageEx(playerID, COLOR_INFO, 43);
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
			if (!strcmp(inputtext, "Zurück", true))
			{
				ShowDialog(playerid, DIALOG_SELECTINTERIOR, interiorDialogID, 0);
				return true;
			}
			if (!strcmp(inputtext, "Weiter", true))
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
						SendClientMessage(playerid, COLOR_INFO, "Kaufen in Bearbeitung!");
					}
					case 1: // Bewerben für den Job Trucker
					{
						if(PVar:playerid[JOBID] >= 0)
						{
							// TODO: MySQL DB erstellen für Bewerbung jeglicher Jobarten.
							// TODO: Diese der Owner des Jobs bearbeiten kann anneehmen kann und ablehnen kann.
							SendClientMessage(playerid, COLOR_INFO, "Bewerben noch in Bearbeitung!");
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
						SendClientMessage(playerid, COLOR_INFO, "Finanzen in Bearbeitung");
					}
					case 2: // Kündigen
					{
						SendClientMessage(playerid, COLOR_INFO, "KÜndigung noch in Bearbeitung!");
					}
					case 3: // Bewerbungs übersicht
					{
						SendClientMessage(playerid, COLOR_INFO, "Bewerbungs übersicht in bearbeitung!");
					}
				}
			}
		}
		case DIALOG_VEHICLEDEALER_JOB:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Kaufe Autohändler
					{
						// TODO: MySQL Daten bank hinzufügen bei Jobs die OwnerUserID zum kaufen.
						new pickupID = PVar:playerid[CURRENTPICKUPID];
						new ownerUserID = strval(GetMySQLValue("pickups", "OwnerUserID", "ID", val2str(pickupID)));
						if (ownerUserID)
						{
							if (ownerUserID == PVar:playerid[USERID])
							{
								SendClientMessageEx(playerid, COLOR_INFO, 44);
							}
							else
							{
								SendClientMessageEx(playerid, COLOR_INFO, 45);
							}
						}
						else
						{
							new Float:price = floatstr(GetMySQLValue("buildings", "Price", "ID", val2str(pickupID)));
							if (price <= PVar:playerid[MONEY])
							{
								GivePlayerMoneyEx(playerid, MONEY_CASH, -price);
								SetMySQLValue("pickups", "OwnerUserID", val2str(PVar:playerid[USERID]), "ID", val2str(pickupID));
								SendClientMessageEx(playerid, COLOR_INFO, 46);
							}
							else
							{
								SendClientMessageEx(playerid, COLOR_ERROR, 47, price, PVar:playerid[MONEY]);
							}
						}
					}
					case 1: // Bewerben für den job
					{
						if(PVar:playerid[JOBID] >= 0)
						{
							// TODO: MySQL DB erstellen für Bewerbung jeglicher Jobarten.
							// TODO: Diese der Owner des Jobs bearbeiten kann anneehmen kann und ablehnen kann.
							SendClientMessage(playerid, COLOR_INFO, "Bewerben noch in Bearbeitung!");
						}
						else
						{
							SendClientMessageEx(playerid, COLOR_ERROR, 39);
						}
					}
					case 2:
					{
						// TODO: noch am überlegen wie es gestaltet werden soll. 
						// TODO: eventuel Wen auto nicht da anfordern beim Autohändler zum bestellen.
						SendClientMessage(playerid, COLOR_INFO, "Fahrzeug kaufen in Bearbeitung!");
					}
				}
			}
		}
		case DIALOG_VEHICLEDEALER_OPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Fahrzeug Bestellen
					{
						ShowDialog(playerid, DIALOG_ORDERVEHICLE);
					}
					case 1: // Finazübersicht
					{
						// TODO: Jeder Job hat eine Job Kasse in der DB diese hier abgerufen wird.
						SendClientMessage(playerid, COLOR_INFO, "Finanzen in Bearbeitung!");
					}
					case 2: // Kündigen
					{
						// TODO: Kündigung seines Jobs
						SendClientMessage(playerid, COLOR_INFO, "Kündigen in Bearbeitung!");
					}
					case 3: // Bewerbungs übrsicht
					{
						// TODO: MySQL DB abrufen für Bewerbungen vom AUtohändler dort kann man Annehmen/Ablehnen ist angenommen wird invitet ist abgelehnt bleibt user so.
						SendClientMessage(playerid, COLOR_INFO, "Bewerbung in bearbeitung!");
					}
				}
			}
		}
	}
	return false;
}