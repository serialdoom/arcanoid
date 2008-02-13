#include "Explosion.h"

Explosion::Explosion(Point point, AnimationFilm* film) : Sprite(point, film){
}

Explosion::Explosion(int x, int y, AnimationFilm* film) : Sprite(x, y, film){
}
