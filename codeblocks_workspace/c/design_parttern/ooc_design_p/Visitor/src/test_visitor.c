#include "base.h"
#include "car_element_run_visitor.h"
#include "car.h"

int test_visitor()
{
	CarElementRunVisitor* carElementRunVisitor = new (CarElementRunVisitor);
	Car* car = new (Car);

	car->accept(car, &carElementRunVisitor->icarElementVisitor);

	delete (CarElementRunVisitor, carElementRunVisitor);
	delete (Car, car);
	return 0;
}
