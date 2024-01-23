#include "Knight.h"
#include <string>
#include <chrono>
#include <future>

Knight::Knight(Point position, char sym, int hp, int damage, int maxHp) :
	ShootCharacter(position, sym, hp, damage, maxHp) {}

bool Knight::GetEndGame()
{
    return endGame;
}

void Knight::SetEndGame(bool endGame)
{
    this->endGame = endGame;
}

Point Knight::Move(std::map<Point, std::shared_ptr<GameObject>>& gameObjects)
{
    int x = 0, y = 0;
    int choice = getch();
    switch (choice)
    {
    case KEY_UP: {
        SetDirection(0);
        x--;
        break;
    }
    case KEY_DOWN: {
        SetDirection(1);
        x++;
        break;
    }
    case KEY_LEFT: {
        SetDirection(2);
        y--;
        break;
    }
    case KEY_RIGHT: {
        SetDirection(3);
        y++;
        break;
    }
    case 10: {
        Shoot(gameObjects);
        break;
    }
    default:
        break;
    }

    while (getch() > 0) {}

    Point position = GetPos();
    Point positionNew(position.x + x, position.y + y);

    auto object = gameObjects.find(positionNew);
    if (object == gameObjects.end()) {
        gameObjects[positionNew] = gameObjects[position];
        SetPos(positionNew);
    }
    else {
        Collide(object->second.get());
    }
    return GetPos();
}

void Knight::Shoot(std::map<Point, std::shared_ptr<GameObject>>& gameObjects)
{
    int x = 0, y = 0;
    switch (GetDirection())
    {
    case 0: {
        x--;
        break;
    }
    case 1: {
        x++;
        break;
    }
    case 2: {
        y--;
        break;
    }
    case 3: {
        y++;
        break;
    }
    default:
        break;
    }

    Point positionNew(GetPos().x + x, GetPos().y + y);
    auto object = gameObjects.find(positionNew);
    if (object == gameObjects.end()) {
        gameObjects[positionNew] = std::make_shared<Projectile>(positionNew, '*', 1, GetDamage(), 1, GetDirection());
    }
}

void Knight::Collide(GameObject* object)
{
    object->Collide(this);
}

void Knight::Collide(Wall*) {}

void Knight::Collide(Knight*) {}

void Knight::Collide(Zombie* object) {
    object->Collide(this);
}

void Knight::Collide(Dragon*) {}

void Knight::Collide(End* object)
{
    SetEndGame(true);
}

void Knight::Collide(AidKit* object)
{
    if (GetHp() != GetMaxHp()) {
        SetHp(std::min(GetMaxHp(), GetHp() + object->GetHp()));
        object->SetHp(0);
    }
}

void Knight::Collide(Projectile* object)
{
    SetHp(std::max(0, GetHp() - object->GetDamage()));
    object->SetHp(0);
    SetLastDamage(object->GetDamage());
    ResetCycleCounter();
}

int Knight::GetLastDamage() const {
    return lastDamage;
}

void Knight::SetLastDamage(int damage) {
    lastDamage = damage;
}

void Knight::IncrementCycleCounter() {
    cycleCounter++;
}

int Knight::GetCycleCounter() const {
    return cycleCounter;
}

void Knight::ResetCycleCounter() {
    cycleCounter = 0;
}