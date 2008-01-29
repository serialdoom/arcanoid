/* header file for the Ball. */

#ifndef __BALL_H__
#define __BALL_H__

#include "Sprite.h"
#include "SpriteType.h"
#include "AnimationFilm.h"


class Ball : public Sprite {
private:
	int speedX, speedY;
	spritetype_t spriteType;
	
public:
	
	spritetype_t GetType(void) const { return spriteType; }

	void SetSpeedX(int _newspeed);
	void SetSpeedY(int _newspeed);
	int GetSpeedX(void);
	int GetSpeedY(void);
	void Move(const int dx, const int dy);
	virtual void Collide(Sprite *s);
	
	Ball(int start_x, int start_y, AnimationFilm *af, const char *ball_string);
	~Ball();
};


#endif