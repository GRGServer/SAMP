public GPS_WhenRouteIsCalculated(routeid, node_id_array[], amount_of_nodes, distance)
{
	FormatNew:string[100]("Route calculated! Distance: %d", distance);
	SendClientMessage(routeid, COLOR_INFO, string);
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
	ShowGPSCheckpoint(routeid, 0);
	return true;
}