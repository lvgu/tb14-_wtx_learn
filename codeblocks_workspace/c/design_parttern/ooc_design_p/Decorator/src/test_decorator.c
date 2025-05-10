#include "base.h"
#include "window.h"
#include "border_decorator.h"

int test_decorator()
{
	Window* window = new (Window, 10, 20);
	IWindow* iwindow = &window->iwindow;
	iwindow->draw(iwindow);

	BorderDecorator* borderDecorator = new (BorderDecorator, iwindow);
	iwindow = &borderDecorator->iwindow;
	iwindow->draw(iwindow);

	delete (BorderDecorator, borderDecorator);
	delete (Window, window);

	return 0;
}
