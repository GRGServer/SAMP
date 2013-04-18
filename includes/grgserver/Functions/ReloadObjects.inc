ReloadObjects(playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Destroying objects...");
	DestroyAllDynamicObjects();

	// Unset all objects
	Count(objectID, sizeof(dynamicObjects))
	{
		Count(enumField, sizeof(dynamicObjects[]))
		{
			dynamicObjects[objectID][enum_object:enumField] = 0;
		}
	}

	AdminPrint(playerID, COLOR_INFO, "* Loading objects...");
	new item[100];
	new type;
	new dir:dirHandle = dir_open("scriptfiles/objects");
	while (dir_list(dirHandle, item, type))
	{
		if (type == FM_FILE)
		{
			AdminPrint(playerID, COLOR_INFO, "  Loading objects from '%s'...", item);
			new count = LoadObjectsFromFile(item);
			AdminPrint(playerID, COLOR_INFO, "  %d objects loaded", count);
		}
	}

	UpdateObjectsForAllPlayers();
}