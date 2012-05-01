OnInteriorDialogSelect(playerID, dialogID, interiorID)
{
	switch (dialogID)
	{
		case INTERIORDIALOG_ADDPROPERTY:
		{
			if (interiorID)
			{
				PVar:playerID[ADDPROPERTY_INTERIORID] = interiorID;
				ShowDialog(playerID, DIALOG_ADDPROPERTY_NAME);
			}
			else
			{
				ShowDialog(playerID, DIALOG_ADDPROPERTY_TYPE);
			}
		}
		case INTERIORDIALOG_SHOWINTERIOR:
		{
			if (interiorID)
			{
				if (TeleportToInterior(playerID, interiorID))
				{
					SetPlayerVirtualWorld(playerID, 0);
				}
			}
		}
	}
}