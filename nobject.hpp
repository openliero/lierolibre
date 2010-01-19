#ifndef LIERO_NOBJECT_HPP
#define LIERO_NOBJECT_HPP

#include "math.hpp"
#include "objectList.hpp"
#include "exactObjectList.hpp"

struct Worm;
struct Game;

struct NObjectType
{
	void create1(Game& game, fixed velX, fixed velY, int x, int y, int color, Worm* owner);
	void create2(Game& game, int angle, fixed velX, fixed velY, fixed x, fixed y, int color, Worm* owner);

	int detectDistance;
	fixed gravity;
	int speed;
	int speedV;
	int distribution;
	int blowAway;
	int bounce;
	int hitDamage;
	bool wormExplode;
	bool explGround;
	bool wormDestroy;
	int bloodOnHit;
	int startFrame;
	int numFrames;
	bool drawOnMap;
	int colorBullets;
	int createOnExp;
	bool affectByExplosions;
	int dirtEffect;
	int splinterAmount;
	int splinterColour;
	int splinterType;
	bool bloodTrail;
	int bloodTrailDelay;
	int leaveObj;
	int leaveObjDelay;
	int timeToExplo;
	int timeToExploV;
	
	int id;
};

struct NObject : ExactObjectListBase
{
	void process(Game& game);
	
	fixed x, y;
	fixed velX, velY;
	int timeLeft;
	int id;
	Worm* owner;
	int curFrame;
};

#endif // LIERO_NOBJECT_HPP
