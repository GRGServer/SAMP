stock str_replace(search[], replace[], source[])
{
	new newnick[256];
	new newlen;
	for (new i; i < strlen(source); i++)
	{
		if (strlen(search) > 1 && i != (strlen(source) - 1))
		{
			new matched = 1;
			new start = i;
			for (new s=0; s < strlen(search) && matched == 1; s++)
			{
				if (source[i] != search[s] && s == 0)
				{
					newnick[newlen] = source[i];
					matched = 0;
				} else
				{
					if (source[i] == search[s])
					{
						i++;
					} else
					{
						matched = 0;
					}
				}
			}
			if (matched == 0)
			{
				for (start=start; start <= i; start++)
				{
					newnick[newlen] = source[start];
					newlen++;
				}
			} else
			{
				for (new r; r < strlen(replace); r++)
				{
					newnick[newlen] = replace[r];
					newlen++;
				}
				i = (start + (strlen(search) - 1));
			}
		} else
		{
			if (strlen(search) == 1 && source[i] == search[0])
			{
				for (new r; r < strlen(replace); r++)
				{
					newnick[newlen] = replace[r];
					newlen++;
				}
			} else
			{
				newnick[newlen] = source[i];
				newlen++;
			}
		}
	}
	newnick[newlen] = EOS;
	return newnick;
}

stock val2str(value)
{
	new string[256];
	Format:string("%d", value);
	return string;
}

stock strtoupper(string[])
{
	new upperString[256];
	for (new character = 0; character < strlen(string); character++)
	{
		upperString[character] = toupper(string[character]);
	}
	return upperString;
}

stock explode(string[], dest[][], token = ' ', max = sizeof (dest), ml = sizeof (dest[]))
{
	new len = strlen(string);
	new idx;
	new i;
	new cur;
	while (idx < len)
	{
		if (string[idx] == token)
		{
			dest[cur][i] = '\0';
			cur++;
			if (cur == max)
			{
					return;
			}
			i = 0;
			while (idx < len && string[idx] == token)
			{
				idx++;
			}
		}
		else
		{
			dest[cur][i++] = string[idx++];
			if (i == ml)
			{
				dest[cur][--i] = '\0';
				while (idx < len && string[idx] != token)
				{
					idx++;
				}
			}
		}
	}
	dest[cur][i] = '\0';
}