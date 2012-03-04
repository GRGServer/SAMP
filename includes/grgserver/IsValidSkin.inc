IsValidSkin(skinID)
{
	if (skinID >= 0 && skinID <= 298)
	{
		switch (skinID)
		{
			case 3, 4, 5, 6, 8, 42, 65, 74, 86, 119, 149, 208, 265, 266, 267, 268, 269, 270, 271, 272, 273, 289:
				return false;
		}
		return true;
	}
	return false;
}