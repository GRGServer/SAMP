/**
 * <summary>
 *	Move an object
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

MoveObjectEx(objectID, newState)
{
	StopDynamicObject(objectID);

	new arrayIndex = objectID - 1;

	if (newState)
	{
		MoveDynamicObject(objectID, dynamicObjects[arrayIndex][OBJECT_MOVEPOS][0], dynamicObjects[arrayIndex][OBJECT_MOVEPOS][1], dynamicObjects[arrayIndex][OBJECT_MOVEPOS][2], dynamicObjects[arrayIndex][OBJECT_MOVESPEED], dynamicObjects[arrayIndex][OBJECT_MOVEROT][0], dynamicObjects[arrayIndex][OBJECT_MOVEROT][1], dynamicObjects[arrayIndex][OBJECT_MOVEROT][2]);
	}
	else
	{
		MoveDynamicObject(objectID, dynamicObjects[arrayIndex][OBJECT_POS][0], dynamicObjects[arrayIndex][OBJECT_POS][1], dynamicObjects[arrayIndex][OBJECT_POS][2], dynamicObjects[arrayIndex][OBJECT_MOVESPEED], dynamicObjects[arrayIndex][OBJECT_ROT][0], dynamicObjects[arrayIndex][OBJECT_ROT][1], dynamicObjects[arrayIndex][OBJECT_ROT][2]);
	}

	return true;
}