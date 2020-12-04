#include <AntsLib/BoardEntities/Ant/AntState.hpp>

const float AntState::FOOD_FROM_TILE_PER_BITE = 0.1f;

void AntState::setHp(int hp)
{
	this->hp = RangeCalculator::trim(hp).toInbetweenInclusive(0, MAX_HP);
}

void AntState::setEnergy(int energy)
{
	this->energy = RangeCalculator::trim(energy).toInbetweenInclusive(0, MAX_ENERGY);
}

void AntState::setStoredFood(int storedFood)
{
	this->storedFood = RangeCalculator::trim(storedFood).toInbetweenInclusive(0, MAX_STORED_FOOD);
}

AntState::AntState(int hp, int energy, int storedFood)
{
	setHp(hp);
	setEnergy(energy);
	setStoredFood(storedFood);
}

AntState AntState::MaxStats()
{
	return AntState(MAX_HP, MAX_ENERGY, MAX_STORED_FOOD);
}

AntState AntState::MaxHpAndEnergyStats()
{
	return AntState(MAX_HP, MAX_ENERGY, 0);
}

int AntState::getHp() const
{
	return hp;
}

int AntState::getEnergy() const
{
	return energy;
}

int AntState::getStoredFood() const
{
	return storedFood;
}
