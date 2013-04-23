/**
 * <summary>
 *	Refuel the current vehicle of the player up to the specific amount.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 *
 * <param name="totalAmount">
 *	The amount in liters
 * </param>
 *
 * <remarks>
 *	The vehicle gets refuelled till the given amount or maximum of the vehicle has been reached.
 * </remarks>
 */

Timer:RefuelVehicle(playerID, Float:totalAmount)
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (vehicleID)
	{
		if (PVar:playerID[MONEY] >= PVar:playerID[CURRENTGASPRICE])
		{
			new modelID = GetVehicleModel(vehicleID);
			if (modelID >= 400 && modelID <= 611)
			{
				new Float:maximum = floatsub(vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL], VehicleProperty:vehicleID[CURRENTFUEL]);
				if (totalAmount > 0 && maximum > 0)
				{
					new Float:amount;
					if (maximum < 1)
					{
						amount = maximum;
					}
					else
					{
						amount = 1.0;
					}
					VehicleProperty:vehicleID[CURRENTFUEL] = floatadd(VehicleProperty:vehicleID[CURRENTFUEL], amount);
					GivePlayerMoneyEx(playerID, MONEY_CASH, -floatmul(PVar:playerID[CURRENTGASPRICE], amount));// TODO: Do not get money at this point, instead use real life stuff (Pay after refuelling)
					SetTimerEx("Timer_RefuelVehicle", GASSTATION_REFUELSPEED, false, "df", playerID, floatsub(totalAmount, amount));
					return true;
				}
				SendClientMessageEx(playerID, COLOR_INFO, StringID:91(""));
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:146(""));
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:92(""));
		}
	}
	TogglePlayerControllable(playerID, true);
	return true;
}