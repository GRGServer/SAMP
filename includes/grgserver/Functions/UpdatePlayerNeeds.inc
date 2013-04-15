/**
 * <summary>
 *	Called every 5 seconds for each connected player to update the player needs (bladder, hunger and thirst)
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 */

UpdatePlayerNeeds(playerID)
{
	PVar:playerID[NEEDS_BLADDER] = PVar:playerID[NEEDS_BLADDER] - NEEDS_BLADDER;
	PVar:playerID[NEEDS_ENERGY] = PVar:playerID[NEEDS_ENERGY] - NEEDS_ENERGY;
	PVar:playerID[NEEDS_HUNGER] = PVar:playerID[NEEDS_HUNGER] - NEEDS_HUNGER;
	PVar:playerID[NEEDS_THIRST] = PVar:playerID[NEEDS_THIRST] - NEEDS_THIRST;

	new bladderBarColor = 'g';
	new energyBarColor = 'g';
	new hungerBarColor = 'g';
	new thirstBarColor = 'g';

	// Fix values which may be < 0
	if (PVar:playerID[NEEDS_BLADDER] <= 0)
	{
		PVar:playerID[NEEDS_BLADDER] = 0;
	}
	if (PVar:playerID[NEEDS_ENERGY] <= 0)
	{
		PVar:playerID[NEEDS_ENERGY] = 0;
	}
	if (PVar:playerID[NEEDS_HUNGER] <= 0)
	{
		PVar:playerID[NEEDS_HUNGER] = 0;
	}
	if (PVar:playerID[NEEDS_THIRST] <= 0)
	{
		PVar:playerID[NEEDS_THIRST] = 0;
	}

	if (PVar:playerID[NEEDS_BLADDER] <= NEEDS_CRITICAL)
	{
		bladderBarColor = 'r';
	}
	else
	{
		if (PVar:playerID[NEEDS_BLADDER] <= NEEDS_WARNING)
		{
			bladderBarColor = 'y';
		}
	}

	if (PVar:playerID[NEEDS_ENERGY] <= NEEDS_CRITICAL)
	{
		energyBarColor = 'r';
	}
	else
	{
		if (PVar:playerID[NEEDS_ENERGY] <= NEEDS_WARNING)
		{
			energyBarColor = 'y';
		}
	}

	if (PVar:playerID[NEEDS_HUNGER] <= NEEDS_CRITICAL)
	{
		hungerBarColor = 'r';
	}
	else
	{
		if (PVar:playerID[NEEDS_HUNGER] <= NEEDS_WARNING)
		{
			hungerBarColor = 'y';
		}
	}

	if (PVar:playerID[NEEDS_THIRST] <= NEEDS_CRITICAL)
	{
		thirstBarColor = 'r';
	}
	else
	{
		if (PVar:playerID[NEEDS_THIRST] <= NEEDS_WARNING)
		{
			thirstBarColor = 'y';
		}
	}

	FormatNew:string[200]("~%c~%s", hungerBarColor, RepeatCharacter('l', floatround(PVar:playerID[NEEDS_HUNGER] / 10)));
	Format:string("%s~n~~%c~%s", string, thirstBarColor, RepeatCharacter('l', floatround(PVar:playerID[NEEDS_THIRST] / 10)));
	Format:string("%s~n~~%c~%s", string, bladderBarColor, RepeatCharacter('l', floatround(PVar:playerID[NEEDS_BLADDER] / 10)));
	Format:string("%s~n~~%c~%s", string, energyBarColor, RepeatCharacter('l', floatround(PVar:playerID[NEEDS_ENERGY] / 10)));

	PlayerTextDrawSetString(playerID, PTextDraw:playerID[NEEDS_COLUMN2], string);

	PlayerTextDrawShow(playerID, PTextDraw:playerID[NEEDS_COLUMN1]);
	PlayerTextDrawShow(playerID, PTextDraw:playerID[NEEDS_COLUMN2]);
}