cell_t glider[5][5] = {
	{0,0,0,0,0},
	{0,0,1,0,0},
	{0,0,0,1,0},
	{0,1,1,1,0},
	{0,0,0,0,0}
};

cell_t bottle[20][20] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0},
	{0,0,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,0,0},
	{0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0},
	{0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0},
	{0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0},
	{0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
	{0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0},
	{0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0},
	{0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0},
	{0,0,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,0,0},
	{0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0},
	{0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

cell_t schickengine[13][22] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0},
	{0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
	{0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

cell_t hammerhead[18][20] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,0},
	{0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,0},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0},
	{0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

cell_t gospersgun[11][38] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
	{0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};