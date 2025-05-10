#include <stdio.h>

#include "base.h"
#include "../include/itarget.h"
#include "../include/target.h"
#include "../include/iadaptee.h"
#include "../include/adaptee.h"
#include "../include/adapter.h"

int test_adapter()
{
	Adaptee* adaptee = new (Adaptee);
	IAdaptee* iadaptee = &adaptee->iadaptee;

	Adapter* adapter = new (Adapter, iadaptee);
	Target* target = new (Target);

	ITarget* itarget = &adapter->itarget;
	printf("%ld\n", itarget->powerOf2(itarget, 10));

	itarget = &target->itarget;
	printf("%ld\n", itarget->powerOf2(itarget, 10));

	delete (Adapter, adapter);
	delete (Target, target);
	delete (Adaptee, adaptee);

	return 0;
}
