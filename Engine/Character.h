#pragma once
#include "Animation.h"
#include "Vec2.h"

class Character
{
private:
	enum class Sequence
	{
		WalkingLeft,
		WalkingRight,
		WalkingUp,
		WalkingDown,
		StandingLeft,
		StandingRight,
		StandingUp,
		StandingDown,
		Count
	};
public:
	Character(const Vec2& pos);
	void Draw(Graphics& gfx) const;
	void SetDirection(const Vec2& dir);
	void Update(float dt);
	// damage visual effect
	void ActivateEffetc();
private:
	Surface sprite;
	Vec2 pos;
	Vec2 vel = { 0.0f, 0.0f };
	std::vector<Animation> animations;
	Sequence iCurSequence = Sequence::StandingDown;
	float speed = 110.0f;
	static constexpr float effectDuration = 0.04f;
	float effectTime = 0.0f;
	bool effectActive = false;
};