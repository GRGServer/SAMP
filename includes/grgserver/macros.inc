#define GetStringArg(%0,%1); \
	for(new i_%0 = 0; ; ++i_%0) \
	{ \
		if((%1[i_%0] = getarg((%0), i_%0)) != EOS) \
			continue; \
		else \
			break; \
	}

#define NCMD:%0(%1,%2) COMMAND:%0(%1, %2) if (!IsPlayerNPC(%1)) return COMMAND_NPC_ONLY; else
#define PCMD:%0[%1](%2,%3) COMMAND:%0(%2, %3) if (!permissions[%2][PERMISSION_%1]) return COMMAND_PERMISSION_DENIED; else
#define RCMD:%0(%1) forward rcmd_%0(%1); public rcmd_%0(%1)

#define FormatMoney(%0) FormatNumber(%0, 2, '.', ',')
#define MD5(%0) MD5_Hash(%0, true)

#define IsKeyPressed(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))// Not used yet

#define GetUserDBValue(%0,%1) GetMySQLValue("users", %1, "UserID", val2str(GetPVarInt(%0, "UserID")))
#define SetUserDBValue(%0,%1,%3) SetMySQLValue("users", %1, %3, "UserID", val2str(GetPVarInt(%0, "UserID")))

#define LoadPermission:%0(%1,%2) permissions[%1][PERMISSION_%0] = strval(GetMySQLField(%2))