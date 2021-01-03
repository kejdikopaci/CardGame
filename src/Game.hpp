//------------------------------------------------------------------------------
// Game.hpp
//------------------------------------------------------------------------------


#ifndef GAME_HPP
#define GAME_HPP
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <fstream>
#include <cstdio>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"



namespace Oop
{
  class Interface;
  class Card;
  class Player;

  //----------------------------------------------------------------------------
  /// Game Class
  /// This class reads the config file
  //
  class Game
  {
  private:

    Oop::Interface &io_;
    Oop::Player *player_1_;
    Oop::Player *player_2_;

    unsigned int rounds_;

  public:
    //--------------------------------------------------------------------------
    /// Standard constructor
    //
    Game(Oop::Interface &io);

    //--------------------------------------------------------------------------
    /// Destructor
    //
    ~Game();

    //--------------------------------------------------------------------------
    /// Reads the config file
    ///
    /// @param std::string config_file the path of config file
    /// @return returns true if config file is valid otherwise false
    //
    bool loadConfig(std::string config_file);

    //--------------------------------------------------------------------------
    /// Starts the game
    /// Quits the game if reads quit or the game is over
    //
    void run();

    //--------------------------------------------------------------------------
    /// Checks if the the configfile is valid
    /// @param std::string config_file the path of config file
    /// @return returns true if config file is valid otherwise false
    //
    bool validateConfigFile(std::string &config_file);

    //--------------------------------------------------------------------------
    /// Checking if there are Cards with the same name, if this is the case, we
    /// check for the equality.
    /// @param std::string config_file the path of config file
    /// @return false if cards with same name have not the same attributes
    //
    bool checkForDoubles(std::string &config_file);


    //--------------------------------------------------------------------------
    /// Reads the Creature Cards from the config file
    /// @param std::string config_file the path of config file
    /// @return returns vector with all creature cards
    //
    std::vector<Oop::Card*> readCreatureCards(std::string &config_file);

    //--------------------------------------------------------------------------
    /// Proofs if the spell cards in the configfile are valid
    /// @param std::string config_file the path of config file
    /// @return returns vector with all spell cards
    //
    std::vector<Oop::Card*> readSpellCards(std::string &config_file);

    //--------------------------------------------------------------------------
    /// Shuffels card stack for both player before starting the game
    //
    void shufflePlayersCards();

    //--------------------------------------------------------------------------
    /// Reads the names of the players before starting
    //
    void getPlayerNames();

    //--------------------------------------------------------------------------
    /// Splits the first 3 cards before starting the game
    //
    void splitStartingCards();

    //--------------------------------------------------------------------------
    /// Handles the correct set of a creature into the game field
    /// @param Oop::Player *player the player which sets the card
    /// @param std::vector<std::string> input vector of the input
    /// @return -1 when invalid command, else return 0
    //
    int setCreature(Oop::Player *player, std::vector<std::string> input);

    //--------------------------------------------------------------------------
    /// Handles the commands of the playes
    /// @param Oop::Player *player_attack_ player who attacks
    /// @param Oop::Player *player_attack_ player who defends
    /// @return -1 when error occurs, 0 when everything was correct
    //
    int playPlayer(Oop::Player *player_attack_, Oop::Player *player_defend_);

    //--------------------------------------------------------------------------
    /// Converts uppercase letters in a string to lowercase letters
    /// @param std::string string which is the input
    /// @return std::string the input in lowercase
    //
    std::string stringToLowercase(std::string string);

    //--------------------------------------------------------------------------
    /// splits the string in seperate strings
    /// @param std::string string the whole input
    /// @return std::vector<std::string> which includes the splitted string
    //
    std::vector<std::string> splitString(std::string string);

    //--------------------------------------------------------------------------
    /// Check for attack function can be run
    /// @param Player *attacker the player which attacks
    /// @param int attacker_creature_position position of the creature
    /// @param Player *defender the player which defends
    /// @param int defender_creature_position position of the creature
    /// @return true when position is valid, else false
    //
    bool isPositionValid(Player *attacker, int attacker_creature_position,
                         Player *defender, int defender_creature_position);

    //--------------------------------------------------------------------------
    /// After checking all possible error, aplly attack on the enemy player
    /// @param Player *attacker the player which attacks
    /// @param int attacker_creature_position position of the creature
    /// @param Player *defender the player which defends
    /// @param int defender_creature_position position of the creature
    /// @return -1 when error occurs, else 1
    //
    int applyAttackOnDefender(Player *attacker, int attacker_creature_position,
                              Player *defender, int defender_creature_position);

    //--------------------------------------------------------------------------
    /// checks for error when player casts a spell
    /// @param Oop::Player *player_attack player which attacks
    /// @param Oop::Player *player_defend player which defends
    /// @param std::vector<std::string> input which includes the splitted input
    /// @return -1 when error occurs, else 0
    //
    int castSpell(Oop::Player *player_attack, Oop::Player *player_defend,
                  std::vector<std::string> input);

    //--------------------------------------------------------------------------
    /// handles Sacrife command
    /// @param Oop::Player *player which calls the sacrifice command
    /// @param std::vector<std::string> input includes the splitted input
    /// @return -1 when error occurs, else 0
    //
    int sacrificeCard(Oop::Player *player, std::vector<std::string> input);

    //--------------------------------------------------------------------------
    /// handles the cast of a spell
    /// @param Oop::Player *player_attack player which attacks
    /// @param Oop::Player *player_defend player which defends
    /// @return -1 when error occurs, else 0
    //
    int handleCastSpell(Oop::Player *player_attack, Oop::Player *player_defend,
                        int input);

    //--------------------------------------------------------------------------
    /// Adds the right amount of mana bevor each round
    /// @param Oop::Player *player the player which gets the mana
    //
    void addManaBeforeRound(Oop::Player *player);

    //--------------------------------------------------------------------------
    /// Tests the Position
    /// @param int position is the input of the player
    /// @param int position_1 checking if position is greater then position_1
    /// @param int position_2 checking if position is smaller then position_2
    /// @return true if its correct, else false
    //
    bool proofCorrectPosition(int position, int position_1, int position_2);

    //--------------------------------------------------------------------------
    /// Checking if the input number is an integer value
    /// @param std::vector<std::string>check_input is the splitted input
    /// @param unsigned long input_position number of the vector position
    /// @return -1 when error occurs, else 0
    //
    int getInput(std::vector<std::string> check_input,
                                                  unsigned long input_position);

    //--------------------------------------------------------------------------
    /// handles the attack command
    /// @param Oop::Player *player_attack player which attacks
    /// @param Oop::Player *player_defend player which defends
    /// @param std::vector<std::string> input which includes the splitted input
    /// @return -1 when error occurs, else 0
    //
    int doAttack(Oop::Player *player_attack, Oop::Player *player_defend,
                                                std::vector<std::string> input);
  };
}

#endif //ASSIGNMENT_5758_GAME_HPP
