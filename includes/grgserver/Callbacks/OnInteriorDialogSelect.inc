OnInteriorDialogSelect(playerID, dialogID, interiorID)
{
	switch (dialogID)
	{
		case INTERIORDIALOG_ADDPROPERTY:
		{
			if (interiorID)
			{
				PVar:playerID[ADDPROPERTY_INTERIORID] = interiorID;
				ShowDialog:ADDPROPERTY_NAME(playerID);
			}
			else
			{
				ShowDialog:ADDPROPERTY_TYPE(playerID);
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