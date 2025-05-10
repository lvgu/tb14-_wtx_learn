#include "base.h"
#include "computer_facade.h"

int test_facade()
{
	ComputerFacade* computerFacade = new (ComputerFacade);
	computerFacade->start(computerFacade);
	delete (ComputerFacade, computerFacade);
	return 0;
}
