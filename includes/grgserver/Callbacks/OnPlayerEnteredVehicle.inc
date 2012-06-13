/**
 * <summary>
 *	This callback gets called every time a player entered a vehicle.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which entered the vehicle.
 * </param>
 *
 * <param name="vehicleID">
 *	The ID of the vehicle which was entered by the player.
 * </param>
 *
 * <param name="isPassenger">
 *	<item name="true">The player entered the vehicle as a passenger</item>
 *	<item name="false">The player entered the vehicle as the driver</item>
 * </param>
 *
 * <remarks>
 *	<title>Difference between OnPlayerEnterVehicle and OnPlayerEnteredVehicle:</title>
 *	<item name="OnPlayerEnterVehicle">The player is while entering the vehicle (Not already in the vehicle)</item>
 *	<item name="OnPlayerEnteredVehicle">The player is already in the vehicle</item>
 * </remarks>
 */

OnPlayerEnteredVehicle(playerID, vehicleID, isPassenger)
{
	if (IsPlayerNPC(playerID))
	{
		return true;
	}
	if (!isPassenger)
	{
		MySQLQuery("SELECT `CarLicense`, `BikeLicense`, `TruckLicense`, `SailingLicense`, `FlyLicense` FROM `users` WHERE `id` = '%d'", PVar:playerID[USERID]);
		mysql_store_result();
		new licenseCar = strval(GetMySQLField("CarLicense"));
		new licenseBike = strval(GetMySQLField("BikeLicense"));
		new licenseTruck = strval(GetMySQLField("TruckLicense"));
		new licenseSailing = strval(GetMySQLField("SailingLicense"));
		new licenseFly = strval(GetMySQLField("FlyLicense"));
		mysql_free_result();
		new modelID = GetVehicleModel(vehicleID);
		if (modelID >= 399 || modelID <= 402 || modelID == 404 || modelID == 405 || modelID >= 409 || modelID <= 415 || modelID == 416 || modelID >= 418 || modelID <= 424)
		{
			if (modelID == 426 || modelID == 429 || modelID == 434 || modelID >= 436 || modelID <= 442 || modelID == 444 || modelID == 445 || modelID == 475)
			{
				if (modelID == 451 || modelID >= 457 || modelID <= 459 || modelID == 466 || modelID == 467 || modelID == 470 || modelID == 471 || modelID == 474)
				{	
					if (modelID >= 477 || modelID <= 480 || modelID == 482 || modelID == 483 || modelID == 485 || modelID >= 489 || modelID <= 492 || modelID >= 494 || modelID <= 496)
					{
						if (modelID >= 498 || modelID <= 508 || modelID >= 516 || modelID <= 518 || modelID >= 525 || modelID <= 543 || modelID >= 545 || modelID <= 547 || modelID >= 549 || modelID <= 552)
						{
							if(modelID >= 554 || modelID <= 562 || modelID >= 565 || modelID <= 568 || modelID == 571 || modelID == 572 || modelID >= 574 || modelID <= 576 || modelID >= 579 || modelID <= 580)
							{
								if (modelID >= 582 || modelID <= 591 || modelID >= 596 || modelID <= 611)
								{
									if (!licenseCar)
									{
										SendClientMessageEx(playerID, COLOR_ERROR, 514);
										return false;
									}
								}
							}
						}
					}
				}
			}
		}
		if (modelID >= 461 || modelID <= 465 || modelID == 448 || modelID >= 521 || modelID <= 523 || modelID == 468 || modelID == 581)
		{
			if(!licenseBike)
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 534);
				return false;
			}
		}
		if (modelID >= 406 || modelID <= 408 || modelID == 403 || modelID == 427 || modelID == 428|| modelID >= 431 || modelID <= 433)
		{
			if ( modelID == 437 || modelID == 446 || modelID == 443 || modelID == 514 || modelID == 515 || modelID == 524 || modelID == 573 || modelID == 578)
			{
				if(!licenseTruck)
				{
					SendClientMessageEx(playerID, COLOR_ERROR, 535);
					return false;
				}
			}
		}
		if (modelID >= 452 || modelID <= 454 || modelID == 430 || modelID == 446 || modelID == 595 || modelID == 493 || modelID == 472 || modelID == 473 || modelID == 484)
		{
			if(!licenseSailing)
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 536);
				return false;
			}
		}
		if (modelID == 476 || modelID == 487 || modelID == 417 || modelID == 488 || modelID == 497 || modelID == 425 || modelID >= 511 || modelID <= 513 || modelID == 460 || modelID == 469)
		{
			if (modelID == 519 || modelID == 520 || modelID == 548 || modelID == 553 || modelID == 563 || modelID == 577 || modelID == 592 || modelID == 593)
			{
				if(!licenseFly)
				{
					SendClientMessageEx(playerID, COLOR_ERROR, 537);
					return false;
				}
			}
		}
	}
	new modelID = GetVehicleModel(vehicleID);
	if (modelID == 420)
	{
		new npcPlayerID;
		MySQLQuery("SELECT * FROM `npcs` WHERE `vehicleId` = '%d'", VehicleProperty:vehicleID[SAVEID]);
		mysql_store_result();
		if (mysql_num_rows())
		{
			npcPlayerID = GetPlayerID(GetMySQLField("name"));
		}
		mysql_free_result();
		if (npcPlayerID != INVALID_PLAYER_ID)
		{
			if (isPassenger)
			{
				SendNPCCommand(npcPlayerID, "start");
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	if (!isPassenger && !GetVehicleEngineState(vehicleID))
	{
		SendClientMessageEx(playerID, COLOR_INFO, 424);
	}
	return true;
}