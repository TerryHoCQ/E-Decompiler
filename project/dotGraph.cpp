#include "dotGraph.h"

dotGraph::dotGraph()
{
	
}

ssize_t idaapi gr_callback(void* ud, int code, va_list va)
{

	switch (code)
	{
	case grcode_user_refresh:
	{
		mutable_graph_t* g = va_arg(va, mutable_graph_t*);

	}
	break;
	default:
		break;
	}
		
	return true;
}

void dotGraph::show()
{
	
}

