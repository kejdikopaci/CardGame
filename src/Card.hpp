//------------------------------------------------------------------------------
// Card.hpp
//------------------------------------------------------------------------------

#ifndef CARD_HPP
#define CARD_HPP
#include <string>
#include <vector>
#include <map>
#include <functional>

//------------------------------------------------------------------------------
namespace Oop
{
  //----------------------------------------------------------------------------
  // Card Class
  // Represent the Cards with it's attributes
  // It's a Base Class for Creature and Spell Cards
  //
  class Card
  {

  public:

    //--------------------------------------------------------------------------
    /// Enumeration of card types
    //
    enum CardType {CREATURE, SPELL};

    //--------------------------------------------------------------------------
    /// Standard constructor without args
    //
    Card();

    //--------------------------------------------------------------------------
    /// Standard constructor with args
    //
    Card(std::string name, int mana_cost, CardType type);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Card();

    //--------------------------------------------------------------------------
    /// Method to get name
    /// @return std::string Name of Card
    //
    virtual std::string getName() const;

    //--------------------------------------------------------------------------
    /// Method to get the Card Type
    /// @return CardType The type of the card
    //
    virtual CardType getType() const;

    //--------------------------------------------------------------------------
    /// Method to get the Mana Of the card
    /// @return int The Mana value
    //
    virtual int getManaCost() const;

  protected:

    std::string name_;
    int mana_cost_;
    CardType type_;

  };
}

#endif //ASSIGNMENT_5758_CARD_HPP
