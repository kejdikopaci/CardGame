//------------------------------------------------------------------------------
// CreatureCard.cpp
//------------------------------------------------------------------------------


#include "CreatureCard.hpp"

using Oop::CreatureCard;

//------------------------------------------------------------------------------
CreatureCard::CreatureCard(const std::string name,  int mana_cost,
                  int damage_points, int life_points, bool shield,
                  bool mana_drain, bool speedy) :
  Card(name, mana_cost, Card::CardType::CREATURE),
  damage_points_(damage_points),
  life_points_(life_points),
  current_life_points_(life_points),
  shield_(shield),
  mana_drain_(mana_drain),
  ready_to_fight_(false),
  already_attacked_(false),
  speedy_(speedy)
{
}

//------------------------------------------------------------------------------
CreatureCard::~CreatureCard()
{
}

//------------------------------------------------------------------------------
int CreatureCard::getLifePoints() const
{
  return life_points_;
}

//------------------------------------------------------------------------------
int CreatureCard::getDamagePoints() const
{
  return damage_points_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getManaDrain() const
{
  return mana_drain_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getShield() const
{
  return shield_;
}

//------------------------------------------------------------------------------
int CreatureCard::getCurrentLifePoints() const
{
  return current_life_points_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getReadyToFight() const
{
  return ready_to_fight_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getAlreadyAttacked() const
{
  return already_attacked_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getSpeedy() const
{
  return speedy_;
}

//------------------------------------------------------------------------------
void CreatureCard::setAlreadyAttackedToTrue()
{
  already_attacked_ = true;
}

//------------------------------------------------------------------------------
void CreatureCard::setAlreadyAttackedToFalse()
{
  already_attacked_ = false;
}

//------------------------------------------------------------------------------
void CreatureCard::reduceCurrentLifePoints(int damage_value)
{
  if (damage_value >= current_life_points_)
  {
    current_life_points_ = 0;
  }
  else
    current_life_points_ -= damage_value;
}

//------------------------------------------------------------------------------

void CreatureCard::setCreatureReadyToFight()
{
  ready_to_fight_ = true;
}

//------------------------------------------------------------------------------
void CreatureCard::addCurrentLifePoints()
{
  if (current_life_points_ == 9)
    current_life_points_ = 9;
  else
    current_life_points_++;

}

//------------------------------------------------------------------------------
void CreatureCard::setCurrentLifePoints()
{
  current_life_points_ = getLifePoints();
}
//------------------------------------------------------------------------------
void CreatureCard::setReadyToFightFalse()
{
  ready_to_fight_ = false;
}
