#include "OkCancel.h"

OkCancel::OkCancel(void)
{
	imageHeight = imageWidth = 0;
	pushOk = pushCancel = false;

}

OkCancel::~OkCancel(void)
{
}

BITMAP *OkCancel::LoadBitmapOkCancel(BITMAP *source){
	if( !(source = load_bitmap(imageFileName.c_str(), NULL)) ){
		allegro_message(imageFileName.c_str());
		exit(-1);
	}
	return source;
}

void OkCancel::BlitOkCancel(BITMAP *source, BITMAP *dest){
	assert(source);
	assert(dest);
	masked_blit(source, dest, 0, 0, imageCort.GetX(), imageCort.GetY(), imageWidth, imageHeight);
	return;
}

