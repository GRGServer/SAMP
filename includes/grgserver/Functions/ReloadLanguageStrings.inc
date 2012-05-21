ReloadLanguageStrings(playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Unloading language strings...");
	Count(stringID, LANGUAGE_MAXSTRINGS)
	{
		strdel(languageStrings[stringID][LANGUAGESTRING_ENGLISH], 0, STRINGLENGTH_LANGUAGESTRING);
		strdel(languageStrings[stringID][LANGUAGESTRING_GERMAN], 0, STRINGLENGTH_LANGUAGESTRING);
	}
	AdminPrint(playerID, COLOR_INFO, "* Loading language strings...");
	new count;
	new highestStringID;
	new XMLNode:xml = XML_LoadDocument(FILE_LANGUAGESTRINGS);
	xml = XML_GetFirstChild(xml, "languagestrings");
	new XMLNode:stringNode = XML_GetFirstChild(xml, "string");
	while (stringNode)
	{
		new value[256];
		new stringIDstr[16];
		XML_GetAttribute(stringNode, "id", stringIDstr);
		new stringID = strval(stringIDstr);
		if (stringID < LANGUAGE_MAXSTRINGS)
		{
			new XMLNode:translationNode;
			translationNode = XML_GetFirstChild(stringNode, "en");
			if (translationNode)
			{
				XML_GetValue(XML_GetFirstChild(translationNode), value);
				value = str_replace("\\n", "\n", value);
				value = str_replace("\\t", "\t", value);
				strcat(languageStrings[stringID][LANGUAGESTRING_ENGLISH], value, STRINGLENGTH_LANGUAGESTRING);
			}
			else
			{
				AdminPrint(playerID, COLOR_ERROR, "  Missing English language string for string %d", stringID);
			}
			translationNode = XML_GetFirstChild(stringNode, "de");
			if (translationNode)
			{
				XML_GetValue(XML_GetFirstChild(translationNode), value);
				value = str_replace("\\n", "\n", value);
				value = str_replace("\\t", "\t", value);
				strcat(languageStrings[stringID][LANGUAGESTRING_GERMAN], value, STRINGLENGTH_LANGUAGESTRING);
			}
			else
			{
				AdminPrint(playerID, COLOR_ERROR, "  Missing German language string for string %d", stringID);
			}
			if (stringID > highestStringID)
			{
				highestStringID = stringID;
			}
			count++;
		}
		else
		{
			AdminPrint(playerID, COLOR_ERROR, "  Language string ID %d is greater than language array size (%d)", stringID, LANGUAGE_MAXSTRINGS);
			break;
		}
		stringNode = XML_GetNextSibling(stringNode, "string");
	}
	XML_UnloadDocument(xml);
	Count(stringID, highestStringID + 1)
	{
		if (!strlen(languageStrings[stringID][LANGUAGESTRING_ENGLISH]) && !strlen(languageStrings[stringID][LANGUAGESTRING_GERMAN]))
		{
			AdminPrint(playerID, COLOR_ERROR, "  Unused language string ID %d", stringID);
		}
	}
	AdminPrint(playerID, COLOR_INFO, "  %d language strings loaded", count);
}