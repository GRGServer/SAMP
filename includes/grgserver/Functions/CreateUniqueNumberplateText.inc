CreateUniqueNumberplateText()
{
	new string[STRINGLENGTH_NUMBERPLATE];
	new found;
	do
	{
		Format:string("%c%c-%d", 65 + random(25), 65 + random(25), random(9999));
		MySQLQuery("SELECT `ID` FROM `vehicles` WHERE `NumberPlate` = '%s'", string);
		mysql_store_result();
		if (mysql_num_rows())
		{
			found = true;
		}
		mysql_free_result();
	}
	while (found);
	return string;
}