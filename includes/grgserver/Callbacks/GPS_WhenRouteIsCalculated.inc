/**
 * <summary>
 *	This callback gets called as soon as the route is calculated.
 * </summary>
 *
 * <param name="routeid">
 *	A unique ID which is used to identify the entry in the route processing queue.
 *	In this gamemode routeid is the ID of the player for which this route has been processed.
 * </param>
 *
 * <param name="node_id_array">
 *	The array containing all nodes of the calculated route in the correct order (From the start to the end).
 * </param>
 *
 * <param name="amount_of_nodes">
 *	The number of nodes in the node_id_array.
 * </param>
 *
 * <param name="distance">
 *	The distance from the starting node to the end node in GTA SA units
 * </param>
 */

public GPS_WhenRouteIsCalculated(routeid, node_id_array[], amount_of_nodes, distance)
{
	if (!PVar:routeid[GPS_ENABLED])
	{
		return true;
	}
	Count(node, MAX_GPS_NODES)
	{
		if (node < amount_of_nodes)
		{
			PVar:routeid[GPS_NODES][node] = node_id_array[node];
		}
		else
		{
			PVar:routeid[GPS_NODES][node] = 0;
		}
	}
	PVar:routeid[GPS_NODESCOUNT] = amount_of_nodes;
	PVar:routeid[GPS_ISCALCULATING] = false;
	ShowGPSCheckpoint(routeid, 0);
	return true;
}