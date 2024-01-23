#pragma once
#include "ShootCharacter.h"
#include "Knight.h"
#include "Zombie.h"
#include "Dragon.h"
#include "Projectile.h"
#include "End.h"
#include "AidKit.h"
#include "Wall.h"

class Dragon : public ShootCharacter
{
public:
	Dragon(Point, char, int, int, int);

	~Dragon() = default;

	Point Move(std::map<Point, std::shared_ptr<GameObject>>&) override;

	void Shoot(std::map<Point, std::shared_ptr<GameObject>>&) override;

	void Collide(GameObject*) override;

	void Collide(Wall*) override;

	void Collide(Knight*) override;

	void Collide(Zombie*) override;

	void Collide(Dragon*) override;

	void Collide(End*) override;

	void Collide(AidKit*) override;

	void Collide(Projectile*) override;
};

