//------------------------------------------------------------------------------
// SpellCard.cpp
//------------------------------------------------------------------------------

#include "SpellCard.hpp"
#include "Interface.hpp"

using Oop::SpellCard;

//------------------------------------------------------------------------------
// Static Constants
const int SpellCard::HEALER_MANA = 5;
const int SpellCard::RELIEF_MANA = 3;
const int SpellCard::REBIRTH_MANA = 5;
const int SpellCard::DRACULA_MANA = 2;

//------------------------------------------------------------------------------
SpellCard::SpellCard(SpellType type) : Oop::Card(), spell_type_(type)
{
  type_ = SPELL;
  switch (type)
  {
    case SpellCard::SpellType::RELIEF:
      name_ = std::string (Oop::Interface::STRING_RELIEF);
      mana_cost_ = RELIEF_MANA;
      break;
    case SpellCard::SpellType::REBIRTH:
      name_ = std::string (Oop::Interface::STRING_REBIRTH);
      mana_cost_ = REBIRTH_MANA;
      break;
    case SpellCard::SpellType::HEALER:
      name_ = std::string (Oop::Interface::STRING_HEALER);
      mana_cost_ = HEALER_MANA;
      break;
    case SpellCard::SpellType::DRACULA:
      name_ = std::string (Oop::Interface::STRING_DRACULA);
      mana_cost_ = DRACULA_MANA;
      break;
    default:
      name_ = std::string ("Not Defined");
      mana_cost_ = 0;
      break;
  }
}

//------------------------------------------------------------------------------
SpellCard::~SpellCard()
{
}


//------------------------------------------------------------------------------
bool SpellCard::action(Game &game)
{
  if (spell_type_ == 1)
  {
    return false;
  }

  return false;
}

//------------------------------------------------------------------------------
SpellCard::SpellType SpellCard::getSpellType() const
{
  return spell_type_;
}
