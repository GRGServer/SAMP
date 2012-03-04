strtoupper(string[])
{
	new upperString[256];
	for (new character = 0; character < strlen(string); character++)
	{
		upperString[character] = toupper(string[character]);
	}
	return upperString;
}