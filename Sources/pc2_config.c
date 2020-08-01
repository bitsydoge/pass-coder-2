#include "pc2_config.h"

int pc2_is_verbose = 0;
void pc2_set_verbose(const int p_value)
{
	pc2_is_verbose = p_value;
}
int pc2_get_verbose()
{
	return pc2_is_verbose;
}