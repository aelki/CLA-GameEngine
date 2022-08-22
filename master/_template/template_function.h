#include "../debug/CLA.h"

void someFunction()
{
	// IO
	cla::start(__func__, *this, ED);

	// IO
	cla::end(ED);
}