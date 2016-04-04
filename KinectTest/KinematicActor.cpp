#include "KinematicActor.h"


KinematicActor::KinematicActor()
	:Actor{ Transform() }
{

}

KinematicActor::KinematicActor(Transform t)
	:Actor{ t }
{
}

void KinematicActor::setPosition(Vector p) { transform.moveTo(p); }
void KinematicActor::translate(Vector offset) { transform.move(offset); }

void KinematicActor::rotate(float angle) { transform.rotate(angle); }
void KinematicActor::setRotation(float angle) { transform.setRotation(angle); }

KinematicActor::~KinematicActor()
{
}
