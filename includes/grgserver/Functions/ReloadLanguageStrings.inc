ReloadLanguageStrings()
{
	print("* Unloading language strings...");
	Count(id, LANGUAGE_MAXSTRINGS)
	{
		strdel(languageStrings[id][LANGUAGESTRING_ENGLISH], 0, STRINGLENGTH_LANGUAGESTRING);
		strdel(languageStrings[id][LANGUAGESTRING_GERMAN], 0, STRINGLENGTH_LANGUAGESTRING);
	}
	print("* Loading language strings...");
	mysql_query("SELECT * FROM `languagestrings`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new id = strval(GetMySQLField("ID"));
		format(languageStrings[id][LANGUAGESTRING_ENGLISH], STRINGLENGTH_LANGUAGESTRING, GetMySQLField("English"));
		format(languageStrings[id][LANGUAGESTRING_GERMAN], STRINGLENGTH_LANGUAGESTRING, GetMySQLField("German"));
	}
}