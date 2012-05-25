/**
 * <summary>
 *	This callback gets called once a player places or removes the target marker on the map.
 * </summary>
 *
 * <param name="playerid">
 *	The ID of the player which placed or removed the target marker.
 * </param>
 *
 * <param name="fX">
 *	The X float coordinate where the player clicked.
 * </param>
 *
 * <param name="fY">
 *	The Y float coordinate where the player clicked.
 * </param>
 *
 * <param name="fZ">
 *	The Z float coordinate where the player clicked (Is inaccurate).
 * </param>
 *
 * <remarks>
 *	This callback sets the MAP_POS(X/Y/Z) PVar of the player.
 * </remarks>
 */

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	PVar:playerid[MAP_POSX] = fX;
	PVar:playerid[MAP_POSY] = fY;
	PVar:playerid[MAP_POSZ] = fZ;
}