ShowDialog:TRUCKER_JOB(playerID)
{
	FormatNew:options[30]("Truckerfirma kaufen");
	Format:options("%s\nBewerben", options);
	CreateDialog(playerID, "TRUCKER_JOB", DIALOG_STYLE_LIST, "Trucker", options, "OK", LanguageString(playerID, 165));
}

DialogResponse:TRUCKER_JOB(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0: // Kaufe Trucker
			{
				// TODO: MySQL Daten bank hinzufügen bei Jobs die OwnerUserID zum kaufen.
				SendClientMessage(playerID, COLOR_SYSTEM, "Work in progress");
			}
			case 1: // Bewerben für den Job Trucker
			{
				if(PVar:playerID[JOBID] >= 0)
				{
					// TODO: MySQL DB erstellen für Bewerbung jeglicher Jobarten.
					// TODO: Diese der Owner des Jobs bearbeiten kann anneehmen kann und ablehnen kann.
					SendClientMessage(playerID, COLOR_SYSTEM, "Work in progress");
				}
				else
				{
					SendClientMessageEx(playerID, COLOR_ERROR, 39);
				}
			}
		}
	}
}