#define GetStringArg(%0,%1); \
	for(new i_%0 = 0; ; ++i_%0) \
	{ \
		if((%1[i_%0] = getarg((%0), i_%0)) != EOS) \
			continue; \
		else \
			break; \
	}

#define ACMD:%1(%2) \
			COMMAND:%1(%2)

#define NCMD:%1(%2) \
			COMMAND:%1(%2)

#define MD5(%0) MD5_Hash(%0, true)

#define GetUserDBValue(%0,%1) GetMySQLValue("users", %1, "UserID", val2str(GetPVarInt(%0, "UserID")))
#define SetUserDBValue(%0,%1,%3) SetMySQLValue("users", %1, %3, "UserID", val2str(GetPVarInt(%0, "UserID")))