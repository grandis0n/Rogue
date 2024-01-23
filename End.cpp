#include "End.h"

End::End(Point position, char sym, int hp) :
	GameObject(position, sym, hp) {}

Point End::Move(std::map<Point, std::shared_ptr<GameObject>>&)
{
	return GetPos();
}

void End::Collide(GameObject* object)
{
	object->Collide(this);
}

void End::Collide(Wall*) {}

void End::Collide(Knight* object)
{
	object->Collide(this);
}

void End::Collide(Zombie*) {}

void End::Collide(Dragon*) {}

void End::Collide(End*) {}

void End::Collide(AidKit*) {}

void End::Collide(Projectile* object) {
	object->Collide(this);
}