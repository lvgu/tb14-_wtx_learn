#include "base.h"
#include "iimage.h"
#include "proxy_image.h"

int test_proxy()
{
	ProxyImage* proxyImage = new (ProxyImage);
	IImage* iimage = &proxyImage->iimage;

	iimage->display(iimage);

	delete (ProxyImage, proxyImage);
	return 0;
}
