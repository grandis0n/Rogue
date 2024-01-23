#include "Map.h"

Map::Map()
{
	std::ifstream file("Settings.json");
	file >> setting;
	file.close();
}

void Map::ReadMap()
{
	std::ifstream file("Map.txt");
	for (int row = 0; row < 18; row++) {
		for (int col = 0; col < 48; col++) {
			char symbol;
			file >> symbol;
			Point position(row, col);
			switch (symbol) {
			case 'K': {
				std::string sym = setting["Knight"]["sym"];
				gameObjects[position] = std::make_shared<Knight>(position,
					sym[0],
					setting["Knight"]["hp"],
					setting["Knight"]["damage"],
					setting["Knight"]["maxHp"]);
				break;
			}
			case 'Z': {
				std::string sym = setting["Zombie"]["sym"];
				gameObjects[position] = std::make_shared<Zombie>(position,
					sym[0],
					setting["Zombie"]["hp"],
					setting["Zombie"]["damage"],
					setting["Zombie"]["maxHp"]);
				break;
			}
			case 'D': {
				std::string sym = setting["Dragon"]["sym"];
				gameObjects[position] = std::make_shared<Dragon>(position,
					sym[0],
					setting["Dragon"]["hp"],
					setting["Dragon"]["damage"],
					setting["Dragon"]["maxHp"]);
				break;
			}
			case 'E': {
				std::string sym = setting["End"]["sym"];
				gameObjects[position] = std::make_shared<End>(position, sym[0],
					setting["End"]["hp"]);
				break;
			}
			case '#': {
				std::string sym = setting["Wall"]["sym"];
				gameObjects[position] = std::make_shared<Wall>(position, sym[0],
					setting["Wall"]["hp"]);
				break;
			}
			case '+': {
				std::string sym = setting["AidKit"]["sym"];
				gameObjects[position] = std::make_shared<AidKit>(position, sym[0],
					setting["AidKit"]["hp"]);
				break;
			}
			default: {
				break;
			}
			}
		}
	}
	file.close();
}

void Map::LoadMap()
{
	clear();
	// dynamic_pointer_cast to go down/across class hierarchy
	std::shared_ptr<Knight> knignt;
	for (const auto& object : gameObjects) {
		if (std::dynamic_pointer_cast<Knight>(object.second)) {
			knignt = std::dynamic_pointer_cast<Knight>(object.second);
			break;
		}
	}
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK); 
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK); 
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_GREEN + 8, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW + 8, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);

	for (int row = 0; row < 18; row++) {
		for (int col = 0; col < 48; col++) {
			Point position = knignt->GetPos();
			if (pow((row - position.x), 2) + pow((col - position.y), 2) < 100) {
				Point place(row, col);
				auto object = gameObjects.find(place);
				if (object != gameObjects.end()) {
					auto temp = object->second->GetSym();
					switch (temp)
					{
					case '#':
						attron(COLOR_PAIR(3));
						break;
					case '<':
					case '>':
					case '^':
					case 'v':
						attron(COLOR_PAIR(4));
						break;
					case '+':
						attron(COLOR_PAIR(1));
						break;
					case 'Z':
						attron(COLOR_PAIR(5));
						break;
					case 'D':
						attron(COLOR_PAIR(6));  // Выберите подходящий номер цветовой пары для темно-оранжевого
						break;
					case 'K':
						attron(COLOR_PAIR(7));  // Выберите подходящий номер цветовой пары для желтого
						break;
					default:
						break;
					}
					mvaddch(row, col, temp);
					attroff(COLOR_PAIR(1));
					attroff(COLOR_PAIR(2));
					attroff(COLOR_PAIR(3));
					attroff(COLOR_PAIR(4));
					attroff(COLOR_PAIR(5));
					attroff(COLOR_PAIR(6));
					attroff(COLOR_PAIR(7));
				}
				else {
					attron(COLOR_PAIR(2));
					mvaddch(row, col, '.');
					attroff(COLOR_PAIR(2));
				}
			}
			else {
				mvaddch(row, col, ' ');
			}
		}
		
	}

	knignt->IncrementCycleCounter();
	
	attron(COLOR_PAIR(1));
	mvprintw(1, 50, ("Health: " + std::to_string(knignt->GetHp())).c_str());
	attroff(COLOR_PAIR(1));

	mvprintw(20, 0, ("Cycle: " + std::to_string(knignt->GetCycleCounter())).c_str());
	if (knignt->GetCycleCounter() <= 10 and knignt->GetLastDamage() > 0) {
		attron(COLOR_PAIR(1));
		mvprintw(21, 00, ("Damage get: " + std::to_string(knignt->GetLastDamage())).c_str());
		attroff(COLOR_PAIR(1));
	}

	if (knignt->GetCycleCounter() >= 10) {
		knignt->ResetCycleCounter();
		knignt->SetLastDamage(0);
	}
	// refresh();
}
