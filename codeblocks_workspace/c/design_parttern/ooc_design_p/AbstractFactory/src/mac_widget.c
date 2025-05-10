#include <stdio.h>

#include "../include/iwidget.h"
#include "../include/mac_widget.h"

static void MacWidget_show(IWidget*);

MacWidget* MacWidget_construct(void* addr)
{
	if (addr == NULL)
	{
		return NULL;
	}

	MacWidget* macWidget = addr;
	macWidget->show = MacWidget_show;

	return macWidget;
}

void MacWidget_destruct(MacWidget* macWidget)
{
}

void MacWidget_show(IWidget* iwidget)
{
	printf("Mac widget!\n");
}
