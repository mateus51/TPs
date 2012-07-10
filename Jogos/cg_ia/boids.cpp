#include "irrlicht/irrlicht.h"
using namespace irr;

class Boids {

public:

	Boids(scene::ISceneManager* smgr, scene::ISceneNode* leader) {
		rotation = smgr->createRotationAnimator(core::vector3df(0.f, 0.2875f, 0.f)); // rotationSpeed
		MIN_DIST = 1000;
		num_boids = 0;
		this->smgr = smgr;
		this->leader = leader;
		for (s32 i; i < 5; i++)
			boids[i] = NULL;
	}


	void addBoid(scene::ISceneNode* boid) {
		if (num_boids < 5) {
			boids[num_boids] = boid;
			boid->addAnimator(rotation);
			num_boids++;
		}
	}



//	Vector pcJ
//	FOR EACH BOID b
//		IF b != bJ THEN
//			pcJ = pcJ + b.position
//		END IF
//	END
//	pcJ = pcJ / N-1
//	RETURN (pcJ - bJ.position) / 100
	core::vector3df getAveragePosition(s32 boid) {
		core::vector3df pos = leader->getPosition();
		for (s32 i=0; i < num_boids; i++) {
			if (i != boid)
				pos += boids[i]->getPosition();
		}
		pos = pos / num_boids;
		return (pos - boids[boid]->getPosition()) / 100;
//		return core::vector3df(pos.X/num_boids, pos.Y/num_boids, pos.Z/num_boids);
	}


//		FOR EACH BOID b
//			IF b != bJ THEN
//				IF |b.position - bJ.position| < 100 THEN
//					c = c - (b.position - bJ.position)
//				END IF
//			END IF
//		END
	core::vector3df getAverageDistance(s32 boid) {
		core::vector3df dist = core::vector3df(0);
		core::vector3df boid_pos = boids[boid]->getPosition();
		core::vector3df other_boid_pos;
		for (s32 i=0; i < num_boids; i++) {
			if (i != boid) {
				other_boid_pos = boids[i]->getPosition();
				if (boid_pos.getDistanceFrom(other_boid_pos) < MIN_DIST) {
					dist = dist - (other_boid_pos - boid_pos);
				}
			}
		}
		return dist;
	}




//	Vector pvJ
//	FOR EACH BOID b
//		IF b != bJ THEN
//			pvJ = pvJ + b.velocity
//		END IF
//	END
//	pvJ = pvJ / N-1
//	RETURN (pvJ - bJ.velocity) / 8
//	core::vector3df getAverageSpeed(s32 boid) {
//		core::vector3df speed = 0;
//		for (s32 i=0; i < num_boids; i++) {
//			if (i != boid) {
////				boids[i]->getA
//			}
//
////				pos += boids[i]->getPosition();
//		}
//		pos = pos / num_boids;
//		return (pos - boids[boid]->getPosition()) / 100;
//	}

	void update() {
		core::vector3df avg_pos, avg_dist;
		scene::ISceneNodeAnimator* anim;
		for (s32 i=0; i < num_boids; i++) {
			avg_pos = getAverageDistance(i);
			avg_dist = getAverageDistance(i);
			anim = smgr->createFlyStraightAnimator(boids[i]->getPosition(), // start point
												  leader->getPosition() + avg_pos + avg_dist,	// end point
												  1000,						// time for way
												  false,					// loop
												  false);					// pingpong
			boids[i]->addAnimator(anim);
			anim->drop();
		}

	}

private:
	scene::ISceneManager* smgr;
	scene::ISceneNode* leader;
	scene::ISceneNode* boids[5];
	s32 num_boids;
	s32 MIN_DIST;
	scene::ISceneNodeAnimator* rotation;
};
