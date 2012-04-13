ReloadLanguageStrings()
{
	print("* Unloading language strings...");
	Count(id, LANGUAGE_MAXSTRINGS)
	{
		strdel(languageStrings[id][LANGUAGESTRING_ENGLISH], 0, STRINGLENGTH_LANGUAGESTRING);
		strdel(languageStrings[id][LANGUAGESTRING_GERMAN], 0, STRINGLENGTH_LANGUAGESTRING);
	}
	print("* Loading language strings...");
	new XMLNode:xml = XML_LoadDocument("languagestrings.xml");
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
				strcat(languageStrings[stringID][LANGUAGESTRING_ENGLISH], value, STRINGLENGTH_LANGUAGESTRING);
			}
			else
			{
				printf("Missing English language string for string %d", stringID);
			}
			translationNode = XML_GetFirstChild(stringNode, "de");
			if (translationNode)
			{
				XML_GetValue(XML_GetFirstChild(translationNode), value);
				value = str_replace("\\n", "\n", value);
				strcat(languageStrings[stringID][LANGUAGESTRING_GERMAN], value, STRINGLENGTH_LANGUAGESTRING);
			}
			else
			{
				printf("Missing German language string for string %d", stringID);
			}
		}
		else
		{
			printf("Language string ID %d is greater than language array size (%d)", stringID, LANGUAGE_MAXSTRINGS);
			break;
		}
		stringNode = XML_GetNextSibling(stringNode, "string");
	}
	XML_UnloadDocument(xml);
}