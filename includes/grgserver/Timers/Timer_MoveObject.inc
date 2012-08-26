/**
 * <summary>
 *	Move an object using a timer.
 * </summary>
 *
 * <param name="dbObjectID">
 *	The ID of the object (From objects table in database)
 * </param>
 *
 * <param name="newState">
 *	<title>The new state</title>
 *	<item name="true">Move the object to the position defined in the moveobject table</item>
 *	<item name="false">Move the object back to the normal position (As defined in the objects table)</item>
 * </param>
 */

Timer:MoveObject(dbObjectID, newState)
{
	MoveObjectEx(dbObjectID, newState);
}