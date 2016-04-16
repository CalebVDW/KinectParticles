#include "Skeleton.h"

Skeleton::Skeleton()
	:Actor{ Transform() }, joints{ NUI_SKELETON_POSITION_COUNT, Skeleton::KinectJoint(Transform()) }
{

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
	Actor::update(dt);
}

void Skeleton::Render(SDL_Renderer* renderer)
{
	//Don't attempt to draw if there is no data
	if (!active)
		return;

	drawBone(renderer, NUI_SKELETON_POSITION_HEAD, NUI_SKELETON_POSITION_SHOULDER_CENTER);
	drawBone(renderer, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_LEFT);
	drawBone(renderer, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_RIGHT);
	drawBone(renderer, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SPINE);
	drawBone(renderer, NUI_SKELETON_POSITION_SPINE, NUI_SKELETON_POSITION_HIP_CENTER);
	drawBone(renderer, NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_LEFT);
	drawBone(renderer, NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_RIGHT);

	//Left Arm
	drawBone(renderer, NUI_SKELETON_POSITION_SHOULDER_LEFT, NUI_SKELETON_POSITION_ELBOW_LEFT);
	drawBone(renderer, NUI_SKELETON_POSITION_ELBOW_LEFT, NUI_SKELETON_POSITION_WRIST_LEFT);
	drawBone(renderer, NUI_SKELETON_POSITION_WRIST_LEFT, NUI_SKELETON_POSITION_HAND_LEFT);

	//Right Arm
	drawBone(renderer, NUI_SKELETON_POSITION_SHOULDER_RIGHT, NUI_SKELETON_POSITION_ELBOW_RIGHT);
	drawBone(renderer, NUI_SKELETON_POSITION_ELBOW_RIGHT, NUI_SKELETON_POSITION_WRIST_RIGHT);
	drawBone(renderer, NUI_SKELETON_POSITION_WRIST_RIGHT, NUI_SKELETON_POSITION_HAND_RIGHT);

	//Left Leg
	drawBone(renderer, NUI_SKELETON_POSITION_HIP_LEFT, NUI_SKELETON_POSITION_KNEE_LEFT);
	drawBone(renderer, NUI_SKELETON_POSITION_KNEE_LEFT, NUI_SKELETON_POSITION_ANKLE_LEFT);
	drawBone(renderer, NUI_SKELETON_POSITION_ANKLE_LEFT, NUI_SKELETON_POSITION_FOOT_LEFT);

	//Right Leg
	drawBone(renderer, NUI_SKELETON_POSITION_HIP_RIGHT, NUI_SKELETON_POSITION_KNEE_RIGHT);
	drawBone(renderer, NUI_SKELETON_POSITION_KNEE_RIGHT, NUI_SKELETON_POSITION_ANKLE_RIGHT);
	drawBone(renderer, NUI_SKELETON_POSITION_ANKLE_RIGHT, NUI_SKELETON_POSITION_FOOT_RIGHT);
}

void Skeleton::drawBone(SDL_Renderer* renderer, NUI_SKELETON_POSITION_INDEX joint0, NUI_SKELETON_POSITION_INDEX joint1)
{
	//Get joint positions
	int x1, y1, x2, y2;
	float skeletonScale = 400.0f;
	x1 = int(skeletonScale * joints[joint0].getTransform().Position().x) + Constants::HALF_SCREEN_WIDTH;
	y1 = -int(skeletonScale * joints[joint0].getTransform().Position().y) + Constants::HALF_SCREEN_HEIGHT;
	x2 = int(skeletonScale * joints[joint1].getTransform().Position().x) + Constants::HALF_SCREEN_WIDTH;
	y2 = -int(skeletonScale * joints[joint1].getTransform().Position().y) + Constants::HALF_SCREEN_HEIGHT;

	//Draw debug lines
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Skeleton::Deactivate() { active = false; }
