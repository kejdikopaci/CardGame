//------------------------------------------------------------------------------
// Game.cpp
//------------------------------------------------------------------------------

#include "Game.hpp"
#include "Interface.hpp"
#include "CreatureCard.hpp"
#include "SpellCard.hpp"
#include "Player.hpp"
#include <stdlib.h>
#include <iostream>
#include <vector>

using Oop::Game;

//------------------------------------------------------------------------------
Game::Game(Oop::Interface &io) : io_(io)
{
  player_1_ = new Oop::Player("Not Defined");
  player_2_ = new Oop::Player("Not Defined");
}

//------------------------------------------------------------------------------
Game::~Game()
{

  delete player_1_;
  delete player_2_;

  player_1_ = nullptr;
  player_2_ = nullptr;
}

//------------------------------------------------------------------------------
bool Game::validateConfigFile(std::string &config_file)
{
  std::ifstream file(config_file);
  if (file.is_open())
  {
    rapidjson::IStreamWrapper stream_file(file);
    rapidjson::Document document;
    document.ParseStream(stream_file);

    if((!document.IsObject()) ||
       (document.MemberCapacity() != 2) ||
       (!document.GetObject().HasMember("Spells")) ||
       (!document.GetObject().HasMember("Creatures")))
    {
      return false;
    }

    const rapidjson::Value &creature = document["Creatures"];
    const rapidjson::Value &spell = document["Spells"];

    if (!spell.IsArray() ||
        !creature.IsArray() ||
        ((document["Creatures"].Capacity() + document["Spells"].Capacity()) < 10))
    {
      return false;
    }
    else
    {
      for (unsigned int iterator = 0; iterator < creature.Size(); iterator++)
      {
        if (creature[iterator].GetObject().MemberCapacity() != 6         ||
            !creature[iterator].HasMember("name")                        ||
            !creature[iterator].GetObject()["name"].IsString()           ||
            (std::string(creature[iterator].GetObject()["name"].
              GetString()).length() > 8) ||
            (std::string(creature[iterator].GetObject()["name"].
              GetString()).length() < 1) ||

            !creature[iterator].HasMember("mana_cost")                     ||
            !creature[iterator].GetObject()["mana_cost"].IsUint()          ||
            (creature[iterator].GetObject()["mana_cost"].GetUint() > 15)   ||
            (creature[iterator].GetObject()["mana_cost"].GetUint() < 1)    ||


            !creature[iterator].HasMember("damage_points")                 ||
            !creature[iterator].GetObject()["damage_points"].IsUint()      ||
            (creature[iterator].GetObject()["damage_points"].GetUint() > 9)||

            !creature[iterator].HasMember("life_points")                   ||
            !creature[iterator].GetObject()["life_points"].IsUint()        ||
            (creature[iterator].GetObject()["life_points"].GetInt() > 9)   ||
            (creature[iterator].GetObject()["life_points"].GetInt() < 1)   ||

            !creature[iterator].HasMember("shield")                        ||
            !creature[iterator].GetObject()["shield"].IsBool()             ||

            !creature[iterator].HasMember("mana_drain")                    ||
            !creature[iterator].GetObject()["mana_drain"].IsBool())
          return false;
      }

      for (unsigned int iterator = 0; iterator < spell.Size(); iterator++)
      {
        if ((spell[iterator].GetObject().MemberCapacity() != 1) ||
            !spell[iterator].HasMember("name"))
          return false;

        std::string healer_name = spell[iterator]["name"].GetString();
        if ((healer_name!= Interface::STRING_HEALER) &&
           (healer_name!= Interface::STRING_RELIEF)  &&
           (healer_name!= Interface::STRING_REBIRTH) &&
           (healer_name!= Interface::STRING_DRACULA))
          return false;
      }
    }
    if (!checkForDoubles(config_file))
      return false;

    file.close();
    return true;
  }
  else
    return false;
}

//------------------------------------------------------------------------------
bool Game::checkForDoubles(std::string &config_file)
{
  std::ifstream if_stream(config_file);
  rapidjson::IStreamWrapper i_stream_wrapper(if_stream);

  rapidjson::Document config;
  config.ParseStream(i_stream_wrapper);
  assert(config.IsObject());

  const rapidjson::Value &creature = config["Creatures"];

  for (unsigned int iterator = 0; iterator < creature.Size() - 1; iterator++)
  {
    for (unsigned int iterator_2 = 1 + iterator; iterator_2 < creature.Size();
        iterator_2++)
    {
      std::string card_before = creature[iterator]["name"].GetString();
      std::string card_after = creature[iterator_2]["name"].GetString();
      if (card_before == card_after)
      {
        if ((creature[iterator]["mana_cost"].GetInt() !=
            creature[iterator_2]["mana_cost"].GetInt()) ||
            (creature[iterator]["life_points"].GetInt() !=
            creature[iterator_2]["life_points"].GetInt()) ||
            (creature[iterator]["damage_points"].GetInt() !=
            creature[iterator_2]["damage_points"].GetInt()) ||
            (creature[iterator]["shield"].GetBool() !=
            creature[iterator_2]["shield"].GetBool()) ||
            (creature[iterator]["mana_drain"].GetBool() !=
            creature[iterator_2]["mana_drain"].GetBool()))
        {
          return false;
        }
      }
    }
  }
  return true;
}

//------------------------------------------------------------------------------
std::vector<Oop::Card*> Game::readCreatureCards(std::string &config_file)
{
  std::ifstream if_stream(config_file);
  rapidjson::IStreamWrapper i_stream_wrapper(if_stream);

  rapidjson::Document config;
  config.ParseStream(i_stream_wrapper);
  assert(config.IsObject());

  const rapidjson::Value &creature = config["Creatures"];

  std::vector<Card*> creature_cards;
  Card *temp_creature_card;

  for (unsigned int iterator = 0; iterator < creature.Size(); iterator++)
  {
    std::string temp_creature_name = creature[iterator]["name"].GetString();
    temp_creature_card = new CreatureCard(temp_creature_name,
                                 creature[iterator]["mana_cost"].GetInt(),
                                 creature[iterator]["damage_points"].GetInt(),
                                 creature[iterator]["life_points"].GetInt(),
                                 creature[iterator]["shield"].GetBool(),
                                 creature[iterator]["mana_drain"].GetBool(),
                                 false);
    creature_cards.push_back(temp_creature_card);
  }

  return creature_cards;
}

//------------------------------------------------------------------------------
std::vector<Oop::Card*> Game::readSpellCards(std::string &config_file)
{
  std::ifstream if_stream(config_file);
  rapidjson::IStreamWrapper i_stream_wrapper(if_stream);

  rapidjson::Document config;
  config.ParseStream(i_stream_wrapper);
  assert(config.IsObject());

  const rapidjson::Value &spells = config["Spells"];

  std::vector<Card*> spell_cards;
  std::string spell_type;

  for (size_t iterator = 0; iterator < spells.Size(); iterator++)
  {
    SpellCard *card;
    spell_type = spells[iterator]["name"].GetString();

    if (Interface::STRING_HEALER == spell_type)
      card = new SpellCard(SpellCard::HEALER);

    if (Interface::STRING_RELIEF == spell_type)
      card = new SpellCard(SpellCard::RELIEF);

    if (Interface::STRING_REBIRTH == spell_type)
      card = new SpellCard(SpellCard::REBIRTH);

    if (Interface::STRING_DRACULA == spell_type)
      card = new SpellCard(SpellCard::DRACULA);

    spell_cards.push_back(card);
  }

  return spell_cards;
}

//------------------------------------------------------------------------------
bool Game::loadConfig(std::string config_file)
{
  bool valid_config = validateConfigFile(config_file);

  if (!valid_config)
  {
    io_.out(Interface::ERROR, Interface::ERROR_INVALID_CONFIG);
    return false;
  }

  std::vector<Card*> all_cards_1;
  std::vector<Card*> spell_cards_1;

  std::vector<Card*> all_cards_2;
  std::vector<Card*> spell_cards_2;

  all_cards_1 = readCreatureCards(config_file);
  spell_cards_1 = readSpellCards(config_file);

  all_cards_2 = readCreatureCards(config_file);
  spell_cards_2 = readSpellCards(config_file);

  for (unsigned int iterator = 0; iterator < spell_cards_1.size(); iterator++)
  {
    all_cards_1.push_back(spell_cards_1.at(iterator));
    all_cards_2.push_back(spell_cards_2.at(iterator));
  }

  player_1_->setPickUpStack(all_cards_1);
  player_2_->setPickUpStack(all_cards_2);

  return true;
}

//------------------------------------------------------------------------------
void Game::shufflePlayersCards()
{
  player_1_->shufflePickUpStack();
  player_2_->shufflePickUpStack();
}

//------------------------------------------------------------------------------
void Game::getPlayerNames()
{
  player_1_->setName(io_.readPlayerName(0));
  player_2_->setName(io_.readPlayerName(1));
}

//------------------------------------------------------------------------------
void Game::splitStartingCards()
{
  player_1_->getStartingCards();
  player_2_->getStartingCards();
}

//------------------------------------------------------------------------------
std::vector<std::string> Game::splitString(std::string string)
{
  std::vector<std::string> splitted_string;
  std::string string_element;
  for (char single_char : string)
  {
    if (single_char == ' ' && string_element.length() >= 1)
    {
      splitted_string.push_back(string_element);
      string_element = "";
    }
    else if (single_char != ' ')
      string_element += single_char;
  }
  if (string_element != "")
    splitted_string.push_back(string_element);
  return splitted_string;
}

//------------------------------------------------------------------------------
int Game::castSpell(Oop::Player *player_attack, Oop::Player *player_defend,
                                                std::vector<std::string> input)
{
  int hand_card_position = getInput(input, 1);
  if (hand_card_position == -1)
    return -1;

  if (!proofCorrectPosition(hand_card_position, 7, 1))
    return -1;

  else
  {
    if (player_attack->getHandSize() < hand_card_position)
    {
      io_.out(Interface::INFO, Interface::WARNING_EXECUTION_NOT_POSSIBLE);
      return -1;
    }
    else
    {
      if (player_attack->getHandCards().at(
        static_cast<unsigned long>(hand_card_position - 1))->getType() !=
                                                          Card::CardType::SPELL)
      {
        io_.out(Interface::INFO, Interface::WARNING_EXECUTION_NOT_POSSIBLE);
        return -1;
      }
    }
  }
  int return_value =
    handleCastSpell(player_attack, player_defend, hand_card_position);
  if (return_value == -2)
    return -2;


  return 0;
}

//------------------------------------------------------------------------------
int Game::handleCastSpell(Oop::Player *player_attack,
                           Oop::Player *player_defend, int input)
{
  unsigned long position = static_cast<unsigned long>(input);
  SpellCard* card = static_cast<SpellCard*>
    (player_attack->getHandCards().at(position - 1));

  if (player_attack->getManaPoints() < card->getManaCost())
  {
    io_.out(Interface::INFO, Interface::WARNING_NOT_ENOUGH_MANA);
    return 1;
  }
  else
  {
    if (card->getSpellType() == SpellCard::SpellType::HEALER)
    {
      player_attack->reduceMana(card->getManaCost());
      for (size_t iterator = 0; iterator < 7; iterator++)
      {
        if (player_attack->getGameField()[iterator] != nullptr)
        {
          player_attack->addCreatureLife(iterator);
        }
      }
      player_attack->deleteCardFromHand(input);
    }
    else if (card->getSpellType() == SpellCard::SpellType::RELIEF)
    {
      player_attack->reduceMana(card->getManaCost());
      int hand_card_size = player_attack->getHandSize() - 1;
      int size_pick_up_stack = player_attack->getPickUpStack().size();

      player_attack->deleteCardFromHand(input);

      for (size_t iterator = 0; iterator < 3; iterator++)
      {
        if (hand_card_size < 7)
        {
          if (size_pick_up_stack != 0)
          {
            player_attack->addCardToHand();
            size_pick_up_stack--;
          }
          else
            player_attack->reduceLifePoints(1);
          hand_card_size++;
        }
        else
          player_attack->reduceLifePoints(1);

        if (player_attack->getLifePoints() <= 0)
          return -2;
      }
    }
    else if (card->getSpellType() == SpellCard::SpellType::REBIRTH)
    {
      player_attack->reduceMana(card->getManaCost());
      int size_of_game_field = 0;
      int size_of_graveyard = player_attack->getGraveyard().size();

      for (int iterator = 0; iterator < 7; iterator++)
      {
        if (player_attack->getGameField()[iterator] != nullptr)
           size_of_game_field++;
      }

      if (size_of_game_field == 7 || size_of_graveyard == 0)
      {
        io_.out(Interface::INFO, Interface::WARNING_REBIRTH_UNSUCCESSFUL);
        player_attack->deleteCardFromHand(input);
        return -1;
      }
      else
      {
        player_attack->addCardFromGraveyard();
      }
      player_attack->deleteCardFromHand(input);
    }
    else if (card->getSpellType() == SpellCard::SpellType::DRACULA)
    {
      player_attack->reduceMana(card->getManaCost());
      player_attack->addLifePoints(2);
      player_defend->reduceLifePoints(2);
      player_attack->deleteCardFromHand(input);
      if(player_defend->getLifePoints() <= 0)
        return -2;
    }
  }
  return 0;
}

//------------------------------------------------------------------------------
int Game::setCreature(Oop::Player *player, std::vector<std::string> input)
{
  int hand_card_position = getInput(input, 1);
  if (hand_card_position == -1)
    return -1;

  int field_position = getInput(input, 3);
  if (field_position == -1)
    return -1;

  int valid_position = 0;

  if (!proofCorrectPosition(hand_card_position, 7, 1))
     return -1;

  if (!proofCorrectPosition(field_position, 7, 1))
    return -1;

  if (input.at(2) != "to")
  {
    io_.out(Interface::INFO, Interface::WARNING_WRONG_PARAMETER);
    return 0;
  }
  valid_position = player->setNewGameField(field_position, hand_card_position);

  if (valid_position == 2)
    player->setNewHandCards(hand_card_position);

  else if (valid_position == 1)
    io_.out(Interface::INFO, Interface::WARNING_NOT_ENOUGH_MANA);

  else
    io_.out(Interface::INFO, Interface::WARNING_EXECUTION_NOT_POSSIBLE);

  return 0;
}

//------------------------------------------------------------------------------
int Game::sacrificeCard(Oop::Player *player,
                        std::vector<std::string> check_input)
{
  int hand_position = getInput(check_input, 1);
  if (hand_position == -1)
    return -1;

  if (!proofCorrectPosition(hand_position, 7, 1))
    return -1;

  else
  {
    if (hand_position <= player->getHandSize())
    {
      player->handleSacrificeCard(hand_position);
    }
    else
      io_.out(Interface::INFO, Interface::WARNING_EXECUTION_NOT_POSSIBLE);
  }
  return 0;
}

//------------------------------------------------------------------------------
bool Game::isPositionValid(Oop::Player *attacker,
                           int attacker_creature_position,
                           Oop::Player *defender,
                           int defender_creature_position)
{
  if (defender->checkPosForDefend(defender_creature_position))
  {
    if (defender->checkForShieldCreatures(defender_creature_position))
    {
      if (attacker->checkPosForAttack(attacker_creature_position))
      {
        return true;
      }
      else
      {
        io_.out(Interface::INFO, Interface::WARNING_EXECUTION_NOT_POSSIBLE);
        return false;
      }
    }
    else
    {
      io_.out(Interface::INFO, Interface::WARNING_SHIELD_MONSTER);
      return false;
    }
  }
  else
  {
    io_.out(Interface::INFO, Interface::WARNING_EXECUTION_NOT_POSSIBLE);
    return false;
  }
}

//------------------------------------------------------------------------------
int Game::applyAttackOnDefender(Oop::Player *attacker,
                                 int attacker_creature_position,
                                 Oop::Player *defender,
                                 int defender_creature_position)
{
  if (defender_creature_position == 0)
  {
    defender->reduceLifePoints(attacker->getGameField()
      [attacker_creature_position - 1]->getDamagePoints());
    if (attacker->getGameField()
      [attacker_creature_position - 1]->getManaDrain())
    {
      defender->drainAllMana();
    }
    if (defender->getLifePoints() <= 0)
    {
      attacker->handleMemoryLeaks();
      defender->handleMemoryLeaks();
      std::string name = "Game ended. Player " +
        attacker->getName() + " won!\n";
      io_.out(Interface::INFO, name);
      return -1;
    }
    return 1;
  }
  else
  {
    if (defender->getGameField()
      [defender_creature_position - 1]->getReadyToFight())
    {
      defender->reduceCreatureLife((defender_creature_position - 1),
        attacker->getGameField()
          [attacker_creature_position - 1]->getDamagePoints());

      if (defender->getGameField()
        [defender_creature_position - 1]->getCurrentLifePoints() == 0)
      {
        defender->deleteCreatureFromGameField(defender_creature_position - 1);
      }
      return 1;
    }
    else
    {
      attacker->nowAlreadyAttackedFalse(attacker_creature_position);
      io_.out(Interface::INFO, Interface::WARNING_EXECUTION_NOT_POSSIBLE);
      return 1;
    }
  }
}

//------------------------------------------------------------------------------
int Game::getInput(std::vector<std::string> check_input,
                                                  unsigned long input_position)
{
  int position = -1;

  try
  {
    position = std::stoi(check_input.at(input_position));
  }
  catch (std::invalid_argument const &e)
  {
    io_.out(Interface::INFO, Interface::WARNING_WRONG_PARAMETER);
    return -1;
  }
  if (position < 0)
  {
    io_.out(Interface::INFO, Interface::WARNING_WRONG_PARAMETER);
    return -1;
  }
  else
    return position;
}

//------------------------------------------------------------------------------
bool Game::proofCorrectPosition(int position, int position_1, int position_2)
{
  if (position > position_1 || position < position_2)
  {
    io_.out(Interface::INFO, Interface::WARNING_WRONG_PARAMETER);
    return false;
  }
  else
    return true;
}

//------------------------------------------------------------------------------
int Game::doAttack(Oop::Player *player_attack, Oop::Player *player_defend,
                                              std::vector<std::string> input)
{
  int defender_creature_position = getInput(input, 1);
  if (defender_creature_position == -1)
    return -1;

  int attacker_creature_position = getInput(input, 3);
  if (attacker_creature_position == -1)
    return -1;

  if (!proofCorrectPosition(defender_creature_position, 7, 0))
    return -1;

  if (!proofCorrectPosition(attacker_creature_position, 7, 1))
    return -1;

  if (input.at(2) != "with")
  {
    io_.out(Interface::INFO, Interface::WARNING_WRONG_PARAMETER);
    return -1;
  }

  if (isPositionValid(player_attack, attacker_creature_position,
                       player_defend, defender_creature_position))
  {
    if (applyAttackOnDefender(player_attack, attacker_creature_position,
                          player_defend, defender_creature_position) == -1)
    {
      return -2;
    }
  }
  else
  {
    return -1;
  }
  return -1;
}


//------------------------------------------------------------------------------
int Game::playPlayer(Oop::Player *player_attack, Oop::Player *player_defend)
{
  player_attack->setAllreadyAttackedToFalse();
  player_attack->setFieldCreaturesToReadyToFight();
  player_defend->setShielCreaturesReadyToFight();

  int input_size = 0;

  if (!player_attack->addCardToHand())
    player_attack->reduceLifePoints(1);

  if (player_attack->getLifePoints() <= 0)
  {
    player_attack->handleMemoryLeaks();
    player_defend->handleMemoryLeaks();

    std::string output = Interface::ENDLINE_PART_ONE
                    + player_defend->getName() + Interface::ENDLINE_PART_TWO;
    io_.out(Interface::INFO, output);
    return -1;
  }
  std::string name = player_attack->getName();
  std::string player_name = ("Current player is " + name);
  io_.out(Interface::INFO, player_name);
  io_.out(player_attack, player_defend);

  std::string input;
  std::vector<std::string> check_input;

  while (1)
  {
    input = io_.askPlayer(name + " > ");
    input = stringToLowercase(input);
    if (input.length() == 0)
      continue;
    check_input = splitString(input);
    input_size = check_input.size();


    if (check_input.at(0) == Interface::COMMAND_SET &&
        check_input.size() == 4)
    {
      setCreature(player_attack, check_input);
    }
    else if (check_input.at(0) == Interface::COMMAND_ATTACK &&
            check_input.size() == 4)
    {
      if (doAttack(player_attack, player_defend, check_input) == -2)
        return -1;
    }
    else if (check_input.at(0) == Interface::COMMAND_CAST && input_size == 2)
    {
      int return_value = castSpell(player_attack, player_defend, check_input);
      if (return_value == -2)
      {
        player_attack->handleMemoryLeaks();
        player_defend->handleMemoryLeaks();

        std::string output = Interface::ENDLINE_PART_ONE
                        + player_defend->getName() + Interface::ENDLINE_PART_TWO;
        io_.out(Interface::INFO, output);
        return -1;
      }
    }

    else if (check_input.at(0) == Interface::COMMAND_SACRIFICE
              && input_size == 2)
    {
      sacrificeCard(player_attack, check_input);
    }
    else if (check_input.at(0) == Interface::COMMAND_HELP && input_size == 1)
    {
      for (unsigned long counter = 0;
            counter < Interface::INFO_HELP_MSGS.size(); counter++)
      {
        io_.out(Interface::INFO, Interface::INFO_HELP_MSGS.at(counter));
      }
    }

    else if (check_input.at(0) == Interface::COMMAND_STATE && input_size == 1)
      io_.out(player_attack, player_defend);

    else if (check_input.at(0) == Interface::COMMAND_QUIT && input_size == 1)
    {
      player_attack->handleMemoryLeaks();
      player_defend->handleMemoryLeaks();

      std::string output = Interface::ENDLINE_PART_ONE
                      + player_defend->getName() + Interface::ENDLINE_PART_TWO;
      io_.out(Interface::INFO, output);
      return -1;
    }
    else if
      ((check_input.at(0) == Interface::COMMAND_QUIT && input_size > 1) ||
      (check_input.at(0) == Interface::COMMAND_FINISH && input_size > 1) ||
      (check_input.at(0) == Interface::COMMAND_STATE && input_size > 1) ||
      (check_input.at(0) == Interface::COMMAND_SACRIFICE && input_size != 2) ||
      (check_input.at(0) == Interface::COMMAND_CAST && input_size != 2) ||
      (check_input.at(0) == Interface::COMMAND_ATTACK && input_size != 4) ||
      (check_input.at(0) == Interface::COMMAND_HELP && input_size > 1) ||
      (check_input.at(0) == Interface::COMMAND_SET && input_size != 4))
    {
      io_.out(Interface::INFO, Interface::WARNING_WRONG_PARAM_COUNT);
    }
    else if (check_input.at(0) == Interface::COMMAND_FINISH
                                  && check_input.size() == 1)
    {
      break;
    }
    else
      io_.out(Interface::INFO, Interface::WARNING_UNKNOWN_COMMAND);
  }
  return 0;
}

//------------------------------------------------------------------------------
std::string Game::stringToLowercase(std::string string)
{
  for (unsigned long counter = 0; counter < string.length(); counter++)
  {
    string.at(counter) = tolower(string.at(counter));
  }

  return string;
}

//------------------------------------------------------------------------------
void Game::addManaBeforeRound(Oop::Player *player)
{
  if (rounds_ == 0)
    player->addMana(Interface::MAX_MANA_GAIN/8);

  else if (rounds_ == 1)
    player->addMana(Interface::MAX_MANA_GAIN/4);

  else if (rounds_ == 2)
    player->addMana(Interface::MAX_MANA_GAIN/2);

  else if (rounds_ >= 3)
    player->addMana(Interface::MAX_MANA_GAIN);

}

//------------------------------------------------------------------------------
void Game::run()
{
  shufflePlayersCards();
  getPlayerNames();
  splitStartingCards();
  int return_value;
  rounds_ = 0;

  while (1)
  {
    std::string round_string = "Round: " + std::to_string(rounds_);
    io_.out(Interface::INFO, round_string);


    addManaBeforeRound(player_1_);
    return_value = playPlayer(player_1_, player_2_);
    if (return_value == -1)
      break;

    addManaBeforeRound(player_2_);
    return_value = playPlayer(player_2_, player_1_);
    if (return_value == -1)
      break;

    rounds_++;

  }
}
