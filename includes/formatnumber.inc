#if defined _formatnumber_included
	#endinput
#else
	#define _formatnumber_included
#endif

#if !defined DEFAULT_DECIMAL_COUNT
	#define DEFAULT_DECIMAL_COUNT  8
#endif

#if !defined DEFAULT_THOUSAND_SEP
	#define DEFAULT_THOUSAND_SEP  ' '
#endif

#if !defined DEFAULT_DECIMAL_POINT
	#define DEFAULT_DECIMAL_POINT  '.'
#endif

stock FormatNumber( { _, Float, Text3D, Menu, Text, DB, DBResult, bool, File, hex, bit, bit_byte, Bit }:xVariable, iDecimals = -1, iThousandSeparator = DEFAULT_THOUSAND_SEP, iDecimalPoint = DEFAULT_DECIMAL_POINT, iTag = tagof( xVariable ) )
{
	static
		s_szReturn[ 32 ],
		s_szThousandSeparator[ 2 ] = { ' ', EOS },
		s_iDecimalPos,
		s_iChar,
		s_iSepPos
	;
	
	if ( iTag == tagof( bool: ) )
	{
		if ( xVariable )
			memcpy( s_szReturn, "true", 0, 5 * ( cellbits / 8 ) );
		else
			memcpy( s_szReturn, "false", 0, 6 * ( cellbits / 8 ) );
		
		return s_szReturn;
	}
	else if ( iTag == tagof( Float: ) )
	{
		if ( iDecimals == -1 )
			iDecimals = DEFAULT_DECIMAL_COUNT;
		
		format( s_szReturn, sizeof( s_szReturn ), "%.*f", iDecimals, xVariable );
	}
	else if ( iTag == tagof( hex: ) || iTag == tagof( Hex: ) )
	{
		format( s_szReturn, sizeof( s_szReturn ), "0x%04h%04h", ( xVariable & ( 0xFFFF0000 ) ) >>> 16, xVariable & ( 0x0000FFFF ) );
		
		return s_szReturn;
	}
	else if ( iTag == tagof( bit: ) || iTag == tagof( Bit: ) )
	{
		format( s_szReturn, sizeof( s_szReturn ), "0b%08b%08b%08b%08b", ( xVariable & 0xFF000000 ) >>> 24, ( xVariable & 0x00FF0000 ) >>> 16, ( xVariable & 0x0000FF00 ) >>> 8, ( xVariable & 0x000000FF ) );
		
		return s_szReturn;
	}
	else if ( iTag == tagof( bit_byte: ) )
	{
		format( s_szReturn, sizeof( s_szReturn ), "0b%08b", ( xVariable & 0x000000FF ) );
		
		return s_szReturn;
	}
	else
	{
		format( s_szReturn, sizeof( s_szReturn ), "%d", xVariable );
		
		if ( iDecimals > 0 )
		{
			strcat( s_szReturn, "." );
			
			while ( iDecimals-- )
				strcat( s_szReturn, "0" );
		}
	}
	
	s_iDecimalPos = strfind( s_szReturn, "." );
	
	if ( s_iDecimalPos == -1 )
		s_iDecimalPos = strlen( s_szReturn );
	else
		s_szReturn[ s_iDecimalPos ] = iDecimalPoint;
	
	if ( s_iDecimalPos >= 4 && iThousandSeparator )
	{
		s_szThousandSeparator[ 0 ] = iThousandSeparator;
		
		s_iChar = s_iDecimalPos;
		s_iSepPos = 0;
		
		while ( --s_iChar > 0 )
		{
			if ( ++s_iSepPos == 3 )
			{
				strins( s_szReturn, s_szThousandSeparator, s_iChar );
				
				s_iSepPos = 0;
			}
		}
	}
	
	return s_szReturn;
}