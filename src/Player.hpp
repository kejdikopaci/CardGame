//------------------------------------------------------------------------------
// Player.hpp
//------------------------------------------------------------------------------
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <map>
#include <functional>
//------------------------------------------------------------------------------
namespace Oop
{
  //----------------------------------------------------------------------------
  // Player Class
  // Represent the player with it's attributes
  // Attributes are Mana, Karten and Lifepoints
  //
  class CreatureCard;
  class Card;
  class Player
  {

  private:

    std::string name_;
    int life_points_;
    int mana_points_;
    CreatureCard *game_field_[7];
    std::vector<Card*> pick_up_stack_;
    std::vector<Card*> hand_;
    std::vector<CreatureCard*> graveyard_;

  public:

    //--------------------------------------------------------------------------
    /// Standard constructor with args
    //
    Player(std::string name);

    //--------------------------------------------------------------------------
    /// Standard constructor without args
    //
    Player();

    //--------------------------------------------------------------------------
    /// Destructor
    //
    ~Player();

    //--------------------------------------------------------------------------
    /// Copy Constructor
    //
    Player(const Player &player_) = default;


    //--------------------------------------------------------------------------
    /// Method to get the name of the player
    /// @return returns the name of the player
    //
    std::string getName() const;

    //--------------------------------------------------------------------------
    /// Method to set the name of the player
    //
    void setName(std::string name);

    //--------------------------------------------------------------------------
    /// Method to get the life of the player
    /// @return returns the life points
    //
    int getLifePoints() const;

    //--------------------------------------------------------------------------
    /// Increases the life points by points
    /// @param points the amount to increase the life points
    //
    void addLifePoints(int points);

    //--------------------------------------------------------------------------
    /// Reduces the life points by points
    /// @param points the amount to reduce the life points
    //
    void reduceLifePoints(int points);

    //--------------------------------------------------------------------------
    /// Method to get the Mana Points
    /// @return the number of Mana Points
    //
    int getManaPoints() const;

    //--------------------------------------------------------------------------
    /// Method to add Mana Points
    /// @param mana the amount of mana to be added
    //
    void addMana(int mana);

    //--------------------------------------------------------------------------
    /// Method to reduce Mana
    /// @param mana The amount to be reduced
    //
    void reduceMana(int mana);

    //--------------------------------------------------------------------------
    /// Method to get cards that player currently has on hand
    /// @return vector of pointers Card
    //
    const std::vector<Card*> getHandCards() const;

    //--------------------------------------------------------------------------
    /// Method to get the length of vector hand_ i.e. amount of cards on hand
    /// @return the numbers of cards in hand
    //
    int getHandSize() const;

    //--------------------------------------------------------------------------
    /// Returns the Creatures Cards that are on the field
    /// @return the pointer to Field of Game
    //
    const CreatureCard *const *getGameField() const;

    //--------------------------------------------------------------------------
    /// Assigns the card stack to player
    //
    void setPickUpStack(std::vector<Card*> card_stack);

    //--------------------------------------------------------------------------
    /// Get the pick up stack of player
    //
    const std::vector<Oop::Card*> getPickUpStack() const;

    //--------------------------------------------------------------------------
    /// Shuffles the Pickupstack at the beginning of the game, help from Random
    /// class.
    /// @return returns vector with shuffled cards
    //
    std::vector<Oop::Card*> shufflePickUpStack();

    //--------------------------------------------------------------------------
    /// Gives the players the 3 first card before starting to play
    //
    void getStartingCards();

    //--------------------------------------------------------------------------
    /// Adds one card from pick_up_stack_ to hand_
    /// @return true if pick_up_stack_ is not empty, false otherwise
    //
    bool addCardToHand();

    //--------------------------------------------------------------------------
    /// After we set a Card from HandCard to Gamefield we have logicaly
    /// a new handcard.
    /// @param setCard setCard is integer value, which card will be set
    //
    void setNewHandCards(int set_card);

    //--------------------------------------------------------------------------
    /// We set the Creature Card on the Gamefield
    /// @param setCard set_card is integer value, which card will be set
    /// @param hand_card is number which handcard will be set
    /// @return -1 if no valid set parameters
    /// @return 1 if not enough mana
    /// @return 2 if card got set
    //
    int setNewGameField(int set_card, int hand_card);

    //--------------------------------------------------------------------------
    /// Check if position for the attacker is valid
    /// @param position to be checked
    /// @return true if valid else false
    //
    bool checkPosForAttack(int position);

    //--------------------------------------------------------------------------
    /// Check if position of the defender is valid
    /// @param position to be checked
    /// @return true if valid else false
    //
    bool checkPosForDefend(int position);

    //--------------------------------------------------------------------------
    /// Check before a attack if there are chield creatures
    /// @param position to be checked
    /// @return true if valid else false
    //
    bool checkForShieldCreatures(int position);

    //--------------------------------------------------------------------------
    /// Methode to set already attacked to false
    //
    void setAllreadyAttackedToFalse();

    //--------------------------------------------------------------------------
    /// Methode to reduce the life of a creature
    /// @param position where creature is
    /// @param damage_amount the amount of damage to reduce
    //
    void reduceCreatureLife(int position, int damage_amount);

    //--------------------------------------------------------------------------
    /// Sets creature ready to fight
    //
    void setFieldCreaturesToReadyToFight();

    //--------------------------------------------------------------------------
    /// Methode to delete creature from the game field
    //
    void deleteCreatureFromGameField(int position);

    //--------------------------------------------------------------------------
    /// Methode to drain all mana from a player
    //
    void drainAllMana();

    //--------------------------------------------------------------------------
    /// Methode to add the creature lifepoints
    /// @param position where the creature is
    //
    void addCreatureLife(int position);

    //--------------------------------------------------------------------------
    /// Methode to handle the sacrification of a card. Card gets pushed to
    /// the graveyard and the player gets a lifepoint
    /// @param position of card to sacrifice
    //
    void handleSacrificeCard(int position);

    //--------------------------------------------------------------------------
    /// Methode to delete a card from the handcards
    /// @param position to be checked
    //
    void deleteCardFromHand(int position);

    //--------------------------------------------------------------------------
    /// Methode to get the pointer to the graveyard
    /// @return pointer to the graveyard
    //
    const std::vector<CreatureCard*> getGraveyard() const;

    //--------------------------------------------------------------------------
    /// Methode to add a card from the graveyard to the hand
    /// @return true if valid else false
    //
    bool addCardFromGraveyard();

    //--------------------------------------------------------------------------
    /// Methode to handle memory leaks
    //
    void handleMemoryLeaks();

    //--------------------------------------------------------------------------
    /// Methode to set the shield creature ready to fight
    //
    void setShielCreaturesReadyToFight();

    //--------------------------------------------------------------------------
    /// Methode to set already attacked to false for creature at position
    /// @param position of creature
    //
    void nowAlreadyAttackedFalse(int position);

  };
}

#endif //ASSIGNMENT_5758_PLAYER_HPP
