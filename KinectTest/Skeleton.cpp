#include "Skeleton.h"

Skeleton::Skeleton()
	:Actor{ Transform() }, joints{ NUI_SKELETON_POSITION_COUNT, Skeleton::KinectJoint(Transform()) }
{
	//Create bones from joints
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_HEAD, NUI_SKELETON_POSITION_SHOULDER_CENTER));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_LEFT));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_RIGHT));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SPINE));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_SPINE, NUI_SKELETON_POSITION_HIP_CENTER));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_LEFT));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_RIGHT));

	//Left Arm
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_SHOULDER_LEFT, NUI_SKELETON_POSITION_ELBOW_LEFT));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_ELBOW_LEFT, NUI_SKELETON_POSITION_WRIST_LEFT));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_WRIST_LEFT, NUI_SKELETON_POSITION_HAND_LEFT));

	//Right Arm
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_SHOULDER_RIGHT, NUI_SKELETON_POSITION_ELBOW_RIGHT));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_ELBOW_RIGHT, NUI_SKELETON_POSITION_WRIST_RIGHT));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_WRIST_RIGHT, NUI_SKELETON_POSITION_HAND_RIGHT));

	//Left Leg
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_HIP_LEFT, NUI_SKELETON_POSITION_KNEE_LEFT));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_KNEE_LEFT, NUI_SKELETON_POSITION_ANKLE_LEFT));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_ANKLE_LEFT, NUI_SKELETON_POSITION_FOOT_LEFT));

	//Right Leg
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_HIP_RIGHT, NUI_SKELETON_POSITION_KNEE_RIGHT));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_KNEE_RIGHT, NUI_SKELETON_POSITION_ANKLE_RIGHT));
	bones.push_back(KinectBone(joints, NUI_SKELETON_POSITION_ANKLE_RIGHT, NUI_SKELETON_POSITION_FOOT_RIGHT));
}


void Skeleton::Update(float dt, const NUI_SKELETON_DATA& data)
{
	active = true;
	//Move joints to correct positions
	for (int i = 0; i < joints.size(); ++i)
	{
		joints[i].Update(dt, data.SkeletonPositions[i]);
	}
	//Skeleton's position has no real meaning but I will update it anyway
	Actor::Update(dt);
}

void Skeleton::Render(SDL_Renderer* renderer)
{
	//Don't attempt to draw if there is no data
	if (!active)
		return;

	for (KinectBone& bone : bones)
	{
		bone.Render(renderer);
	}
}

void Skeleton::ResolveCollisions(ParticleArray<Particle>& particles)
{
	if (!active)
		return;
	for (KinectBone& bone : bones)
	{
		for (int i = 0; i < particles.Size(); ++i)
		{
			bone.ResolveCollision(particles[i]);
		}
	}
}


void Skeleton::Deactivate() { active = false; }


//KINECT BONE DEFINITIONS//////////////////////////////////////////////////////////////////////////
Skeleton::KinectBone::KinectBone(std::vector<KinectJoint>& joints, NUI_SKELETON_POSITION_INDEX jointIndex0, NUI_SKELETON_POSITION_INDEX jointIndex1)
	:joint0{ joints[jointIndex0] }, joint1{ joints[jointIndex1] }
{
}

void Skeleton::KinectBone::Render(SDL_Renderer* renderer)
{
	//Get joint positions
	int x1, y1, x2, y2;
	float skeletonScale = 400.0f;
	x1 = int(skeletonScale * joint0.GetTransform().Position().x) + Constants::HALF_SCREEN_WIDTH;
	y1 = -int(skeletonScale * joint0.GetTransform().Position().y) + Constants::HALF_SCREEN_HEIGHT;
	x2 = int(skeletonScale * joint1.GetTransform().Position().x) + Constants::HALF_SCREEN_WIDTH;
	y2 = -int(skeletonScale * joint1.GetTransform().Position().y) + Constants::HALF_SCREEN_HEIGHT;

	//Draw debug lines
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

bool Skeleton::KinectBone::ResolveCollision(Particle& particle)
{
	//Determine if intersection occurred 
	Vector p0 = joint0.GetTransform().Position();
	Vector p1 = joint1.GetTransform().Position();
	Vector boneDirection = p1 - p0;
	Vector normal = glm::normalize(Vector(boneDirection.y, -boneDirection.x));

	float k = glm::dot(normal, joint0.GetTransform().Position());

	Vector b = particle.GetTransform().Position();
	Vector a = particle.PreviousPosition();

	if ((glm::dot(normal, a) - k) * (glm::dot(normal, b) - k) > 0)
		return false;	//a and b are on the same side of the line so there was no intersection

	Vector s = b - a;
	Vector r = p1 - p0;
	float t = math::Cross2D(a - p0, s) / math::Cross2D(r, s);
	float u = math::Cross2D(p0 - a, r) / math::Cross2D(s, r);
	if (u > 1.0f || u < 0 || t > 1.0f || t < 0)
		return false;

	Vector intersectionPt = p0 + t * r;

	particle.SetPosition(a + 0.9f * (intersectionPt - a));

	//Calculate impulse to apply to particle
	Vector impulse = normal * glm::dot(normal, particle.Velocity()) * -2.0f * particle.Mass();
	if (glm::dot(particle.Velocity(), normal) > 0)
	{
		impulse = -impulse;
	}
	particle.ApplyImpulse(impulse);

	//Clearly we made it this far so something must have collided. Let's inform the caller of this
	return true;
}