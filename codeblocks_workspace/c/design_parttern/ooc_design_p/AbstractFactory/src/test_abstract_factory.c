#include "base.h"

#include "../include/iwidget.h"
#include "../include/ibutton.h"
#include "../include/ifactory.h"
#include "../include/linux_widget.h"
#include "../include/linux_button.h"
#include "../include/linux_factory.h"
#include "../include/mac_widget.h"
#include "../include/mac_button.h"
#include "../include/mac_factory.h"
#include "../include/windows_widget.h"
#include "../include/windows_button.h"
#include "../include/windows_factory.h"

int test_abstract_factory()
{
	LinuxFactory* linuxFactory = new (LinuxFactory);
	IFactory* ifactory = &linuxFactory->ifactory;
	IWidget* iwidget = ifactory->createWidget(ifactory);
	iwidget->show(iwidget);
	IButton* ibutton = ifactory->createButton(ifactory);
	ibutton->click(ibutton);
	delete (LinuxWidget, container_of(iwidget, LinuxWidget, iwidget));
	delete (LinuxButton, container_of(ibutton, LinuxButton, ibutton));

	MacFactory* macFactory = new (MacFactory);
	ifactory = &macFactory->ifactory;
	iwidget = ifactory->createWidget(ifactory);
	iwidget->show(iwidget);
	ibutton = ifactory->createButton(ifactory);
	ibutton->click(ibutton);
	delete (MacWidget, container_of(iwidget, MacWidget, iwidget));
	delete (MacButton, container_of(ibutton, MacButton, ibutton));

	WindowsFactory* windowsFactory = new (WindowsFactory);
	ifactory = &windowsFactory->ifactory;
	iwidget = ifactory->createWidget(ifactory);
	iwidget->show(iwidget);
	ibutton = ifactory->createButton(ifactory);
	ibutton->click(ibutton);
	delete (WindowsWidget, container_of(iwidget, WindowsWidget, iwidget));
	delete (WindowsButton, container_of(ibutton, WindowsButton, ibutton));

	delete (LinuxFactory, linuxFactory);
	delete (MacFactory, macFactory);
	delete (WindowsFactory, windowsFactory);

	return 0;
}
