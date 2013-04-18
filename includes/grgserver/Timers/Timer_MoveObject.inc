/**
 * <summary>
 *	Move an object using a timer.
 * </summary>
 *
 * <param name="objectID">
 *	The ID of the object
 * </param>
 *
 * <param name="newState">
 *	<title>The new state</title>
 *	<item name="true">Move the object to the move target</item>
 *	<item name="false">Move the object back to the original position</item>
 * </param>
 */

Timer:MoveObject(objectID, newState)
{
	MoveObjectEx(objectID, newState);
}