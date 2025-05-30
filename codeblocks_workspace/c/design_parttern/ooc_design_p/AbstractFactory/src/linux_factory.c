#include <stdio.h>

#include "base.h"


#include "../include/iwidget.h"
#include "../include/ibutton.h"
#include "../include/ifactory.h"
#include "../include/linux_widget.h"
#include "../include/linux_button.h"
#include "../include/linux_factory.h"

static IWidget* LinuxFactory_createWidget(IFactory*);
static IButton* LinuxFactory_createButton(IFactory*);

LinuxFactory* LinuxFactory_construct(void* addr)
{
	if (addr == NULL)
	{
		return NULL;
	}

	LinuxFactory* linuxFactory = addr;
	linuxFactory->createWidget = LinuxFactory_createWidget;
	linuxFactory->createButton = LinuxFactory_createButton;

	return linuxFactory;
}

void LinuxFactory_destruct(LinuxFactory* linuxFactory)
{
}

IWidget* LinuxFactory_createWidget(IFactory* ifactory)
{
	return &new (LinuxWidget)->iwidget;
}

IButton* LinuxFactory_createButton(IFactory* ifactory)
{
	return &new (LinuxButton)->ibutton;
}
