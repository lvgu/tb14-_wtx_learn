#include <stdio.h>

#include "singleton.h"

int test_singleton()
{
	Singleton* singleton = getSingleton();
	printf("%lu\n", singleton->currentTime);

	singleton = getSingleton();
	printf("%lu\n", singleton->currentTime);

	return 0;
}
