
Vtx _alienred_rock_small_vtx[42] = {
	{{{192, 206, -183},0, {-828, 2115},{0x5A, 0x1E, 0xAC, 0xFF}}},
	{{{244, 210, -30},0, {-795, 2492},{0x7E, 0x11, 0x4, 0xFF}}},
	{{{209, 0, -208},0, {-250, 1940},{0x5B, 0xF9, 0xA7, 0xFF}}},
	{{{20, 217, -252},0, {-914, 1269},{0x1, 0x11, 0x82, 0xFF}}},
	{{{-210, 0, -214},0, {-250, 149},{0xA6, 0x4, 0xA7, 0xFF}}},
	{{{-159, 222, -174},0, {-938, 523},{0xAE, 0x21, 0xA5, 0xFF}}},
	{{{16, 426, -197},0, {-1497, 1344},{0x9, 0x5D, 0xA9, 0xFF}}},
	{{{-135, 426, -129},0, {-1500, 713},{0xC3, 0x5C, 0xC1, 0xFF}}},
	{{{193, 426, -12},0, {-1424, 2318},{0x58, 0x5B, 0xFD, 0xFF}}},
	{{{193, 426, -12},0, {39, 883},{0x58, 0x5B, 0xFD, 0xFF}}},
	{{{244, 210, -30},0, {690, 934},{0x7E, 0x11, 0x4, 0xFF}}},
	{{{192, 206, -183},0, {658, 541},{0x5A, 0x1E, 0xAC, 0xFF}}},
	{{{108, 426, 144},0, {-114, 1662},{0x40, 0x5A, 0x3F, 0xFF}}},
	{{{156, 213, 152},0, {513, 1809},{0x5B, 0x22, 0x51, 0xFF}}},
	{{{21, 426, 190},0, {-250, 2059},{0x3, 0x5C, 0x57, 0xFF}}},
	{{{14, 217, 239},0, {277, 2492},{0x10, 0x11, 0x7D, 0xFF}}},
	{{{206, 0, 208},0, {1167, 2188},{0x5A, 0xA, 0x5A, 0xFF}}},
	{{{156, 213, 152},0, {513, 1809},{0x5B, 0x22, 0x51, 0xFF}}},
	{{{14, 217, 239},0, {277, 2492},{0x10, 0x11, 0x7D, 0xFF}}},
	{{{244, 210, -30},0, {690, 934},{0x7E, 0x11, 0x4, 0xFF}}},
	{{{209, 0, -208},0, {1167, 744},{0x5B, 0xF9, 0xA7, 0xFF}}},
	{{{21, 426, 190},0, {2410, -460},{0x3, 0x5C, 0x57, 0xFF}}},
	{{{108, 426, 144},0, {2262, -877},{0x40, 0x5A, 0x3F, 0xFF}}},
	{{{193, 426, -12},0, {1724, -1303},{0x58, 0x5B, 0xFD, 0xFF}}},
	{{{-135, 426, -129},0, {1258, 201},{0xC3, 0x5C, 0xC1, 0xFF}}},
	{{{16, 426, -197},0, {1043, -519},{0x9, 0x5D, 0xA9, 0xFF}}},
	{{{-190, 426, -11},0, {1668, 479},{0xAA, 0x5D, 0x4, 0xFF}}},
	{{{-193, 199, 200},0, {2410, 541},{0xA9, 0x1D, 0x58, 0xFF}}},
	{{{14, 217, 239},0, {246, -846},{0x10, 0x11, 0x7D, 0xFF}}},
	{{{21, 426, 190},0, {-250, -929},{0x3, 0x5C, 0x57, 0xFF}}},
	{{{-193, 199, 200},0, {213, 143},{0xA9, 0x1D, 0x58, 0xFF}}},
	{{{-209, 0, 211},0, {1043, 541},{0xA6, 0xFC, 0x59, 0xFF}}},
	{{{14, 217, 239},0, {246, -846},{0x10, 0x11, 0x7D, 0xFF}}},
	{{{-209, 0, 211},0, {1043, 541},{0xA6, 0xFC, 0x59, 0xFF}}},
	{{{206, 0, 208},0, {1043, -1500},{0x5A, 0xA, 0x5A, 0xFF}}},
	{{{-237, 218, -35},0, {1992, 1674},{0x83, 0x11, 0xF1, 0xFF}}},
	{{{-193, 199, 200},0, {1167, 1788},{0xA9, 0x1D, 0x58, 0xFF}}},
	{{{-190, 426, -11},0, {2014, 2492},{0xAA, 0x5D, 0x4, 0xFF}}},
	{{{-209, 0, 211},0, {1375, 657},{0xA6, 0xFC, 0x59, 0xFF}}},
	{{{-210, 0, -214},0, {2478, 657},{0xA6, 0x4, 0xA7, 0xFF}}},
	{{{-159, 222, -174},0, {2492, 1634},{0xAE, 0x21, 0xA5, 0xFF}}},
	{{{-135, 426, -129},0, {2434, 2431},{0xC3, 0x5C, 0xC1, 0xFF}}},
};

Gfx _alienred_rock_small_tri[] = {
	gsSPVertex(_alienred_rock_small_vtx + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(2, 4, 3, 0),
	gsSP1Triangle(4, 5, 3, 0),
	gsSP1Triangle(5, 6, 3, 0),
	gsSP1Triangle(5, 7, 6, 0),
	gsSP1Triangle(0, 3, 6, 0),
	gsSP1Triangle(6, 8, 0, 0),
	gsSP1Triangle(9, 10, 11, 0),
	gsSP1Triangle(10, 9, 12, 0),
	gsSP1Triangle(10, 12, 13, 0),
	gsSP1Triangle(13, 12, 14, 0),
	gsSP1Triangle(13, 14, 15, 0),
	gsSPVertex(_alienred_rock_small_vtx + 16, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 1, 0, 0),
	gsSP1Triangle(3, 0, 4, 0),
	gsSP1Triangle(5, 6, 7, 0),
	gsSP1Triangle(7, 8, 5, 0),
	gsSP1Triangle(7, 9, 8, 0),
	gsSP1Triangle(8, 10, 5, 0),
	gsSP1Triangle(5, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(_alienred_rock_small_vtx + 32, 10, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(6, 4, 3, 0),
	gsSP1Triangle(3, 7, 6, 0),
	gsSP1Triangle(3, 8, 7, 0),
	gsSP1Triangle(3, 9, 8, 0),
	gsSP1Triangle(3, 5, 9, 0),
	gsSPEndDisplayList(),
};