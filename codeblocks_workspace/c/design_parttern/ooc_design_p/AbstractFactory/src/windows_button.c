#include <stdio.h>

#include "../include/ibutton.h"
#include "../include/windows_button.h"

static void WindowsButton_click(IButton*);

extern WindowsButton* WindowsButton_construct(void* addr)
{
	if (addr == NULL)
	{
		return NULL;
	}

	WindowsButton* windowsButton = addr;
	windowsButton->click = WindowsButton_click;

	return windowsButton;
}

extern void WindowsButton_destruct(WindowsButton* windowsButon)
{
}

static void WindowsButton_click(IButton* ibutton)
{
	printf("Windows button!\n");
}
