#pragma once
#include <Utils.hpp>

class AntState {
private:
	int hp;
	int energy;
	int storedFood;

	AntState() = default;
public:
	int cyclesAlive = 0;
	static const int MAX_HP = 100;
	static const int MAX_ENERGY = 1000;
	static const int MAX_STORED_FOOD = 100;
	static const int FOOD_ENERGY_VALUE = 10;
	static const int MAX_FOOD_ON_TILE = 200;
	static const float FOOD_FROM_TILE_PER_BITE;
	static const int FOOD_TRANSFERED_TO_ANTHILL_PER_TICK = 10;
	static const int FOOD_CONVERTED_PER_TICK = 1;

	AntState(int hp, int energy, int storedFood);

	static AntState MaxStats();
	static AntState MaxHpAndEnergyStats();

	int getHp() const;
	int getEnergy() const;
	int getStoredFood() const;
	void setHp(int hp);
	void setEnergy(int energy);
	void setStoredFood(int storedFood);
};