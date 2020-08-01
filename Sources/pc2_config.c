#include "pc2_config.h"

int pc2_is_verbose = 0;
void set_verbose(const int p_value)
{
	pc2_is_verbose = p_value;
}
int get_verbose()
{
	return pc2_is_verbose;
}