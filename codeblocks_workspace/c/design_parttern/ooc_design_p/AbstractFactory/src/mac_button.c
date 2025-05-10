#include <stdio.h>

#include "../include/ibutton.h"
#include "../include/mac_button.h"

static void MacButton_click(IButton*);

MacButton* MacButton_construct(void* addr)
{
	if (addr == NULL)
	{
		return NULL;
	}

	MacButton* macButton = addr;
	macButton->click = MacButton_click;

	return macButton;
}

void MacButton_destruct(MacButton* macButton)
{
}

void MacButton_click(IButton* ibutton)
{
	printf("Mac button!\n");
}
