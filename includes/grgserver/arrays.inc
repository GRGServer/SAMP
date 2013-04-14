// Available sound IDs (Played randomly in register progress)
new musicSoundIDs[] =
{
	1062,
	1068,
	1076,
	1097,
	1183,
	1185,
	1187
};

// Available radio stations (Used in vehicles)
new radioStations[][enum_radioStation] =
{
	{"", ""},// 0 should be "Radio off"
	{"Tortoise 107.9", "http://selfcoders.com:8000/listen.pls?sid=1"},
	{"Super Natural 98.3", "http://selfcoders.com:8000/listen.pls?sid=2"},
	{"Rise FM", "http://selfcoders.com:8000/listen.pls?sid=11"},
	{"Techno4ever", "http://node03.t4e.dj:7000/listen.pls"},
	{"Technobase.fm", "http://listen.technobase.fm/dsl.pls"},
	{"Blackbeats.FM", "http://stream.blackbeatslive.de/;stream.nsv&type=mp3"},
	{"HyperSheep FM", "http://selfcoders.com:8000/listen.pls?sid=3"},
	{"Hot 108 Jamz", "http://scfire-mtc-aa05.stream.aol.com:80/stream/1071"}
};

// Removed standard objects (GTA San Andreas objects)
new removedStandardObjects[][enum_stdObj] =
{
	{985, 2497.41, 2777.07, 11.5312, 1.0},
	{986, 2497.41, 2769.11, 11.5312, 1.0},
	{7172, 2546.03, 2828.73, 11.5391, 1.0},
	{960, 2580.0, 2830.0, 10.0, 70.0},
	{961, 2580.0, 2830.0, 10.0, 70.0},
	{16094, 191.141, 1870.04, 21.4766, 1.0},

	// All saints general hospital (Los Santos)
	{5708, 1134.25, -1338.08, 23.1562, 1.0},// hospital_law
	{5930, 1134.25, -1338.08, 23.1562, 1.0},// LODpital_law
	{620, 1184.01, -1353.5, 12.5781, 1.0},// veg_palm04
	{620, 1184.01, -1343.27, 12.5781, 1.0},// veg_palm04
	{617, 1178.6, -1332.07, 12.8906, 1.0},
	{618, 1177.73, -1315.66, 13.2969, 1.0},
	{620, 1184.81, -1303.15, 12.5781, 1.0},// veg_palm04
	{620, 1184.81, -1292.91, 12.5781, 1.0},// veg_palm04

	// Small stuff
	{1440, 1141.98, -1346.11, 13.2656, 1.0},// DYN_BOX_PILE_3
	{1440, 1085.7, -1361.02, 13.2656, 1.0},// DYN_BOX_PILE_3
	{1440, 1148.68, -1385.19, 13.2656, 1.0},// DYN_BOX_PILE_3
	{1529, 1098.81, -1292.55, 17.1406, 1.0},// tag_temple

	// Misc buildings
	{5810, 1114.31, -1348.1, 17.9844, 1.0},// lawnmalstrip
	{5931, 1114.31, -1348.1, 17.9844, 1.0},// LODnmalstrip
	{5811, 1131.2, -1380.42, 17.0703, 1.0},// lawnmallsign1
	{5993, 1110.9, -1328.81, 13.8516, 1.0},// lawnmalstripTR
	{5731, 1076.71, -1358.09, 15.4453, 1.0},// MelBlok05_LAwN
	{5934, 1076.71, -1358.09, 15.4453, 1.0},// LODBlok05_LAwN
	{5787, 1090.05, -1310.53, 17.5469, 1.0},// MelBlok01_LAwN
	{5936, 1090.05, -1310.53, 17.5469, 1.0},// LODBlok01_LAwN
	{5788, 1080.98, -1305.52, 16.3594, 1.0},// MelBlok01T_LAwN
	{5737, 1120.16, -1303.45, 18.5703, 1.0},// archshop07_laW02
	{5935, 1120.16, -1303.45, 18.5703, 1.0}// LODhshop07_laW02
};

// Skins
new maleSkins[] =
{
	2,
	6,
	7,
	21,
	98
};
new femaleSkins[] =
{
	131,
	150,
	169,
	190,
	193
};