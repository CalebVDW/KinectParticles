#pragma once

#include <SDL.h>
#include <vector>

#include "KinematicActor.h"
#include "ParticleArray.h"
#include "Particle.h"

//This class stores Kinect data 
class Skeleton : public Actor
{
public:
	Skeleton();

	void Update(float dt, const NUI_SKELETON_DATA& data);
	void Render(SDL_Renderer* renderer);
	void Deactivate();
	void ResolveCollisions(ParticleArray<Particle>& particles);

private:
	//This simple private class stores a little extra data for joints
	//Not making a separate file because it is so simple
	class KinectJoint : public KinematicActor {
	public:
		KinectJoint(Transform t) :KinematicActor{ t } {}
		void Update(float dt, Vector4 position) { transform.SetPosition(math::MakeVector(position)); depth = position.z; }
	private:
		float depth;
	};

	//Another very simple private class to simplify working with Kinect data
	class KinectBone {
	public:
		KinectBone(std::vector<KinectJoint> joints, NUI_SKELETON_POSITION_INDEX joint0, NUI_SKELETON_POSITION_INDEX joint1);
		void Render(SDL_Renderer* renderer);
		bool ResolveCollision(Particle& p);
	private:
		const KinectJoint& joint0;
		const KinectJoint& joint1;
	};

	//This vector will have the same amount of elements as the skeleton has
	//Update order does not matter. The NUI_SKELETON_POSITION_INDEX enum can be used to access them
	std::vector<KinectJoint> joints;
	std::vector<KinectBone> bones;
	bool active = false;

};