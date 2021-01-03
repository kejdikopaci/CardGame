//------------------------------------------------------------------------------
// SpellCard.hpp
//------------------------------------------------------------------------------

#ifndef SPELLCARD_HPP
#define SPELLCARD_HPP

#include "Card.hpp"
#include "string"
//------------------------------------------------------------------------------
namespace Oop
{
  class Game;
  //----------------------------------------------------------------------------
  // SpellCard Class
  // Represent the Spell Cards with it's attributes
  // It's a Subclass of Card Class
  // Don't land in Graveyard after use, instead they are destroyed
  //
  class SpellCard : public Card
  {

  public:

    // Spell Type Mana Amount
    const static int HEALER_MANA;
    const static int RELIEF_MANA;
    const static int REBIRTH_MANA;
    const static int DRACULA_MANA;

    //--------------------------------------------------------------------------
    /// Enumeration of Spell Types of Spell Card
    //
    enum SpellType {HEALER, RELIEF, REBIRTH, DRACULA};

    //--------------------------------------------------------------------------
    /// Args constructor
    //
    SpellCard(SpellType type);

    //--------------------------------------------------------------------------
    /// Destructor
    //
    ~SpellCard();

    //----------------------------------------------------------------------------
    /// Method to get the Spell Type
    /// @return SpellType The type of the Spell
    //
    virtual SpellType getSpellType() const;

  private:

    SpellType spell_type_;
    //--------------------------------------------------------------------------
    /// Method to check if a Spell Action can be executed
    /// @param game Ref to a game obj
    /// @return True if Spell Action can be executed
    //
    bool action(Game& game);

  };
}

#endif //ASSIGNMENT_5758_SPELLCARD_HPP
