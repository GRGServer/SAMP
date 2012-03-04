Str2Val(string[])
{
	new index;
	new length = strlen(string);
	new number[30];
	Count(character, length)
	{
		if (string[character] >= 48 && string[character] <= 57)
		{
			number[index] = string[character];
			index++;
		}
	}
	return strval(number);
}