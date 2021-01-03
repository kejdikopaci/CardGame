//------------------------------------------------------------------------------
// CreatureCard.hpp
//------------------------------------------------------------------------------

#ifndef CREATURECARD_HPP
#define CREATURECARD_HPP
#include "Card.hpp"

//------------------------------------------------------------------------------
namespace Oop
{
  //----------------------------------------------------------------------------
  // CreatureCard Class
  // Represent the CreatureCard Cards with it's attributes
  // It's a Subclass of Card Class
  //
  class CreatureCard : public Card
  {

  public:
    //--------------------------------------------------------------------------
    /// Standard constructor with args
    //
    CreatureCard(const std::string name, int mana_cost, int damage_points,
                int life_points, bool shield, bool mana_drain, bool speedy);

    //--------------------------------------------------------------------------
    /// Destructor
    //
    ~CreatureCard();

    //--------------------------------------------------------------------------
    /// Method to get the total amount of life points
    /// @return int The life points
    //
    int getLifePoints() const;

    //--------------------------------------------------------------------------
    /// Method to get the damage a creature can make when attacking
    /// @return int Damage Points
    //
    int getDamagePoints() const;

    //--------------------------------------------------------------------------
    /// Method to check if a creature has the drain ability
    /// @return bool True in case Creature das the drain ability
    ///         otherwise False
    //
    bool getManaDrain() const;

    //--------------------------------------------------------------------------
    /// Method to check if a Creature has a shield or not
    /// @return bool True in case Creature das Shield otherwise False
    //
    bool getShield() const;

    //--------------------------------------------------------------------------
    /// Method to get the remaining life points
    /// @return int The number of life points
    //
    int getCurrentLifePoints() const;

    //--------------------------------------------------------------------------
    /// Method to check if a creature can allready fight
    /// @return bool True if a creature can fight false otherwise
    //
    bool getReadyToFight() const;

    //--------------------------------------------------------------------------
    /// Method to check if Creature has already attacked
    /// @return bool True if has already attacked, false otherwise
    //
    bool getAlreadyAttacked() const;

    //--------------------------------------------------------------------------
    /// Method to set already attacked to true
    //
    void setAlreadyAttackedToTrue() ;

    //--------------------------------------------------------------------------
    /// Method to set allready attacked to false
    //
    void setAlreadyAttackedToFalse();

    //--------------------------------------------------------------------------
    /// Method to reduce the livepoints
    /// @param damage_value the value of livepoints getting reduced
    //
    void reduceCurrentLifePoints(int damage_value);

    //--------------------------------------------------------------------------
    /// Method to set the creature ready to fight
    //
    void setCreatureReadyToFight();

    //--------------------------------------------------------------------------
    /// Method to add one livepoints
    //
    void addCurrentLifePoints();

    //--------------------------------------------------------------------------
    /// Method to set the current livepoints
    //
    void setCurrentLifePoints();

    //--------------------------------------------------------------------------
    /// Method to set ready to fight to false
    //
    void setReadyToFightFalse();

    //--------------------------------------------------------------------------
    /// Let's see if we are going to implement bonus, otherwise a method
    /// to check if a creature can attack immidiately
    /// @return True if a Creature can attack immidiately, otherwise false
    //
    bool getSpeedy() const;

  private:

    const int damage_points_;
    const int life_points_;
    int current_life_points_;
    const bool shield_;
    const bool mana_drain_;
    bool ready_to_fight_;
    bool already_attacked_;
    const bool speedy_; // For the bonus task relevant, till then set to false

  };
}

#endif //ASSIGNMENT_5758_CREATURECARD_HPP
