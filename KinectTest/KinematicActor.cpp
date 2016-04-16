#include "KinematicActor.h"


KinematicActor::KinematicActor()
	:Actor{ Transform() }
{

}

KinematicActor::KinematicActor(Transform t)
	:Actor{ t }
{
}

void KinematicActor::SetPosition(Vector p) { transform.SetPosition(p); }
void KinematicActor::Translate(Vector offset) { transform.Translate(offset); }

void KinematicActor::Rotate(float angle) { transform.Rotate(angle); }
void KinematicActor::SetRotation(float angle) { transform.SetRotation(angle); }

KinematicActor::~KinematicActor()
{
}
