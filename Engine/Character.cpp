#include "Character.h"

Character::Character(const Vec2 & pos)
	:
	sprite( "link90x90.bmp" ),
	pos(pos)
{
	for (int i = 0; i < (int)Sequence::StandingLeft; ++i)
	{
		animations.emplace_back( Animation(90, 90 * i, 90, 90, 4, sprite, 0.13f) );
	}

	for (int i = (int)Sequence::StandingLeft; i < (int)Sequence::Count; ++i)
	{
		animations.emplace_back( Animation(0 , 90 * (i - (int)Sequence::StandingLeft), 90, 90, 1, sprite, 0.13f) );
	}
}

void Character::Draw(Graphics & gfx) const
{
	if (effectActive)
	{
		animations[(int)iCurSequence].DrawColor((Vei2)pos, gfx, Colors::Red);
	}
	else
	{
		//animations[(int)iCurSequence].DrawGhost((Vei2)pos, gfx);
		//animations[(int)iCurSequence].Draw((Vei2)pos, gfx);
		animations[(int)iCurSequence].DrawNegative((Vei2)pos, gfx);
	}
	
}

void Character::SetDirection(const Vec2 & dir)
{
	if (dir.x > 0)
	{
		iCurSequence = Sequence::WalkingRight;
	}
	else if (dir.x < 0)
	{
		iCurSequence = Sequence::WalkingLeft;
	}
	else if (dir.y < 0)
	{
		iCurSequence = Sequence::WalkingUp;
	}
	else if (dir.y > 0)
	{
		iCurSequence = Sequence::WalkingDown;
	}
	else
	{
		if(vel.x > 0)
		{
			iCurSequence = Sequence::StandingRight;
		}
		else if (vel.x < 0)
		{
			iCurSequence = Sequence::StandingLeft;
		}
		else if (vel.y < 0)
		{
			iCurSequence = Sequence::StandingUp;
		}
		else if (vel.y > 0)
		{
			iCurSequence = Sequence::StandingDown;
		}
	}

	vel = dir * speed;
}

void Character::Update(float dt)
{
	pos += vel * dt;
	animations[(int)iCurSequence].Update(dt);

	if (effectActive)
	{
		effectTime += dt;
		if (effectTime >= effectDuration)
		{
			effectActive = false;
		}
	}
}

void Character::ActivateEffetc()
{
	effectActive = true;
	effectTime = 0.0f;
}
