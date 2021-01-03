//------------------------------------------------------------------------------
// Player.cpp
//------------------------------------------------------------------------------

#include "Player.hpp"
#include "Card.hpp"
#include "CreatureCard.hpp"
#include "Random.hpp"
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <fstream>
#include <cstdio>
#include <iostream>

using Oop::Player;

//------------------------------------------------------------------------------
Player::Player(std::string name) : name_(name),
                                   life_points_(30),
                                   mana_points_(0),
                                   game_field_{nullptr}
{
  hand_.reserve(7);
}

//------------------------------------------------------------------------------
Player::Player() : name_(""),
                   life_points_(30),
                   mana_points_(0),
                   game_field_{nullptr}
{
  hand_.reserve(7);
}

//------------------------------------------------------------------------------
Player::~Player()
{
  for (size_t stack_position = 0; stack_position < pick_up_stack_.size();
              stack_position++)
  {
    delete pick_up_stack_.at(stack_position);
  }
  pick_up_stack_.clear();

  for (size_t hand_position = 0; hand_position < hand_.size(); hand_position++)
  {
    delete hand_.at(hand_position);
  }
  hand_.clear();

  for (size_t graveyard_position = 0; graveyard_position < graveyard_.size();
              graveyard_position++)
  {
    delete graveyard_.at(graveyard_position);
  }
  graveyard_.clear();

  game_field_[1] = nullptr;
  game_field_[0] = nullptr;
  game_field_[2] = nullptr;
  game_field_[3] = nullptr;
  game_field_[4] = nullptr;
  game_field_[5] = nullptr;
  game_field_[6] = nullptr;
}

//------------------------------------------------------------------------------
std::string Player::getName() const
{
  return name_;
}

//------------------------------------------------------------------------------
int Player::getLifePoints() const
{
  return life_points_;
}

//------------------------------------------------------------------------------
void Player::setName(std::string name)
{
  name_ = name;
}

//------------------------------------------------------------------------------
void Player::addLifePoints(int points)
{
  life_points_ += points;
}

//------------------------------------------------------------------------------
void Player::reduceLifePoints(int points)
{
  life_points_ -= points;
}

//------------------------------------------------------------------------------
int Player::getManaPoints() const
{
  return mana_points_;
}

//------------------------------------------------------------------------------
void Player::addMana(int mana)
{
  mana_points_ += mana;
  if (mana_points_ > 15)
    mana_points_ = 15;
}

//------------------------------------------------------------------------------
void Player::reduceMana(int mana)
{
  if (mana_points_ >= mana)
    mana_points_ -= mana;
}

//------------------------------------------------------------------------------
const std::vector<Oop::Card*> Player::getHandCards() const
{
  return hand_;
}

//------------------------------------------------------------------------------
int Player::getHandSize() const
{
  return hand_.size();
}

//------------------------------------------------------------------------------
const Oop::CreatureCard *const *Player::getGameField() const
{
  return static_cast<const CreatureCard *const*>(game_field_);
}

//------------------------------------------------------------------------------
void Player::setPickUpStack(std::vector<Card*> card_stack)
{
  pick_up_stack_ = card_stack;
}

//------------------------------------------------------------------------------
std::vector<Oop::Card*> Player::shufflePickUpStack()
{
  Oop::Random &instance = Oop::Random::getInstance();
  instance.shufflePickupstack(pick_up_stack_);
  return pick_up_stack_;
}

//------------------------------------------------------------------------------
const std::vector<Oop::Card*> Player::getPickUpStack() const
{
  return pick_up_stack_;
}

//------------------------------------------------------------------------------
void Player::getStartingCards()
{
  for (int iterator = 0; iterator < 3; ++iterator)
  {
    hand_.push_back(pick_up_stack_.back());
    pick_up_stack_.pop_back();
  }
}

//------------------------------------------------------------------------------
bool Player::addCardToHand()
{
  if ((pick_up_stack_.size() == 0) || (hand_.size() == 7))
    return false;
  else
  {
    hand_.push_back(pick_up_stack_.back());
    pick_up_stack_.pop_back();
    return true;
  }
}

//------------------------------------------------------------------------------
void Player::setNewHandCards(int set_card)
{
  std::vector<Card*> hand = getHandCards();
  hand.erase(hand.begin() + set_card - 1);
  hand_ = hand;
}

//------------------------------------------------------------------------------
int Player::setNewGameField(int set_card, int hand_card)
{
  unsigned long hand_card_ = static_cast<unsigned long>(hand_card);

  if (getHandSize() < hand_card)
    return -1;
  else if (hand_.at(hand_card_ - 1)->getManaCost() > getManaPoints())
    return 1;

  if (game_field_[set_card - 1] == 0 &&
      hand_.at(hand_card_ - 1)->getType() == Card::CardType::CREATURE)
  {
    game_field_[set_card - 1] =
               static_cast<CreatureCard*>(hand_.at(hand_card_ - 1));

    reduceMana(hand_.at(hand_card_ - 1)->getManaCost());
    return 2;
  }
  return -1;
}

//------------------------------------------------------------------------------
bool Player::checkPosForAttack(int position)
{
  if ((game_field_[position - 1] != nullptr) &&
      !game_field_[position - 1]->getAlreadyAttacked() &&
       game_field_[position - 1]->getReadyToFight())
  {
    game_field_[position - 1]->setAlreadyAttackedToTrue();
    return true;
  }
  else
    return false;
}

//------------------------------------------------------------------------------
void Player::nowAlreadyAttackedFalse(int position)
{
  game_field_[position - 1]->setAlreadyAttackedToFalse();
}

//------------------------------------------------------------------------------
bool Player::checkPosForDefend(int position)
{
  if (position == 0)
  {
    return true;
  }
  else if (game_field_[position - 1] != nullptr)
  {
    return true;
  }
  else
    return false;
}

//------------------------------------------------------------------------------
bool Player::checkForShieldCreatures(int position)
{
  std::vector<int> position_with_shields;

  for (int current_position = 0; current_position < 7; current_position++)
  {
    if (game_field_[current_position] == nullptr)
      continue;

    if (game_field_[current_position]->getShield())
    {
      position_with_shields.push_back(current_position);
    }
  }
  if (position_with_shields.size() > 0)
  {
    std::vector<int>::iterator it = std::find(position_with_shields.begin(),
                                  position_with_shields.end(), (position - 1));

    if (it != position_with_shields.end())
      return true;
    else
      return false;
  }
  else
    return true;
}

//------------------------------------------------------------------------------
void Player::setAllreadyAttackedToFalse()
{
  for (int position = 0; position < 7; ++position)
  {
    if (game_field_[position] == nullptr)
      continue;
    else
      game_field_[position]->setAlreadyAttackedToFalse();
  }
}

//------------------------------------------------------------------------------
void Player::reduceCreatureLife(int position, int damage_amount)
{
  game_field_[position]->reduceCurrentLifePoints(damage_amount);
}

//------------------------------------------------------------------------------
void Player::setFieldCreaturesToReadyToFight()
{
  for (int position = 0; position < 7; ++position)
  {
    if (game_field_[position] == nullptr)
      continue;
    else
      game_field_[position]->setCreatureReadyToFight();
  }
}

//------------------------------------------------------------------------------
void Player::deleteCreatureFromGameField(int position)
{
  graveyard_.push_back(game_field_[position]);
  game_field_[position] = nullptr;
}

//------------------------------------------------------------------------------
void Player::drainAllMana()
{
  mana_points_ = 0;
}


//------------------------------------------------------------------------------
void Player::addCreatureLife(int position)
{
  game_field_[position]->addCurrentLifePoints();
}

//------------------------------------------------------------------------------
void Player::handleSacrificeCard(int position)
 {
   unsigned long hand_position = static_cast<unsigned long>(position);

   if (hand_.at(hand_position - 1)->getType() == Card::CardType::CREATURE)
   {
     graveyard_.push_back(
                static_cast<CreatureCard*>(hand_.at(hand_position - 1)));
     hand_.erase(hand_.begin() + position - 1);
   }
   else
   {
     delete hand_.at(hand_position - 1);
     hand_.erase(hand_.begin() + position - 1);
   }
   addLifePoints(1);
 }

 //------------------------------------------------------------------------------
 void Player::deleteCardFromHand(int position)
 {
   unsigned long hand_position = static_cast<unsigned long>(position);
   delete hand_.at(hand_position - 1);
   hand_.erase(hand_.begin() + position - 1);
 }

//------------------------------------------------------------------------------
const std::vector<Oop::CreatureCard*> Player::getGraveyard() const
{
  return graveyard_;
}

//------------------------------------------------------------------------------
bool Player::addCardFromGraveyard()
{
  int position = 0;
  std::vector<CreatureCard*> graveyard = getGraveyard();

  for (position = 0; position < 7; position++)
  {
    if (getGameField()[position] == nullptr)
      break;
  }

  int size_of_graveyard = graveyard.size();
  unsigned long size_graveyard = static_cast<unsigned long>(size_of_graveyard);
  graveyard.at(size_graveyard - 1)->setCurrentLifePoints();
  game_field_[position] = graveyard.at(size_graveyard - 1);
  game_field_[position]->setReadyToFightFalse();
  graveyard.erase(graveyard.begin() + size_of_graveyard - 1);
  graveyard_ = graveyard;
  return true;
}



//------------------------------------------------------------------------------
void Player::handleMemoryLeaks()
{
  //
  for (int position = 0; position < 7; position++)
  {
    if (game_field_[position] == nullptr)
      continue;
    graveyard_.push_back(game_field_[position]);
    game_field_[position] = nullptr;
  }
}

//------------------------------------------------------------------------------
void Player::setShielCreaturesReadyToFight()
{
  for (int position = 0; position < 7; ++position)
  {
    if (game_field_[position] == nullptr)
      continue;
    else
    {
      if (game_field_[position]->getShield())
        game_field_[position]->setCreatureReadyToFight();
    }
  }
}
