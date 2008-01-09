#ifndef OKCANCEL_H
#define OKCANCEL_H

#include <iostream>
#include <allegro.h>
#include <cassert>
#include <string.h>
#include "Point.h"

using namespace std;

class OkCancel {
private:
	friend class LoadData;

	Point imageCort;
	Point okUpCort;
	Point okDownCort;
	Point cancelUpCort;
	Point cancelDownCort;

	bool pushOk, pushCancel;
	int imageHeight;
	int imageWidth;
	string imageFileName;

public:
	OkCancel(void);
	~OkCancel(void);

	string GetImageFileName(void)	const { return imageFileName; }
	Point GetImageCort(void)		const { return imageCort; }
	Point GetOkUpCort(void)			const { return okUpCort; }
	Point GetOkDownCort(void)		const { return okDownCort;}
	Point GetCancelUpCort(void)		const { return cancelUpCort; }
	Point GetCancelDownCort(void)	const { return cancelDownCort; }
	bool PushOk(void)				const { return pushOk; }
	bool PushCancel(void)			const { return pushCancel; }

	void SetPushOk(bool choice)		{ pushOk = choice; }
	void SetPushCancel(bool choice)	{ pushCancel = choice; }

	/* @target: Na kanei load to bitmap gia to ok cancel. An den mporesei stamata h 
	 *		  :diadikasia h ektelesh.
	 * @param : To bitmap sto opoio 8a ginei ti load
	 * @return: To source pou 8a exei plewn ginei to load.
	 */
	BITMAP *LoadBitmapOkCancel(BITMAP *source);

	/* @target: kanei blit to bitmap tou ok cancel
	 * @input : source einai to bitmap pou exei thn pliroforia gia to ok cancel
	 *		  :dest einai se poio shmeio 8a ginei to blit.
	 */
	void BlitOkCancel(BITMAP *source, BITMAP *dest);
};

#endif