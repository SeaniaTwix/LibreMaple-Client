//////////////////////////////////////////////////////////////////////////////
// This file is part of the LibreMaple MMORPG client                        //
// Copyright © 2015-2016 Daniel Allendorf, 2018-2019 LibreMaple Team        //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#include "RegularAttack.h"

namespace jrc
{
void RegularAttack::apply_useeffects(Char&) const
{
}

void RegularAttack::apply_actions(Char& user, Attack::Type type) const
{
    action.apply(user, type);
}

void RegularAttack::apply_stats(const Char& user, Attack& attack) const
{
    attack.damage_type = Attack::DMG_WEAPON;
    attack.skill = 0;
    attack.mob_count = 1;
    attack.hit_count = 1;
    attack.stance = user.get_look().get_stance();
    if (attack.type == Attack::CLOSE) {
        attack.range = user.get_afterimage().get_range();
    }
}

void RegularAttack::apply_hit_effects(const AttackUser&, Mob&) const
{
}

Animation RegularAttack::get_bullet(const Char& user,
                                    std::int32_t bulletid) const
{
    return bullet.get(user, bulletid);
}

bool RegularAttack::is_attack() const
{
    return true;
}

bool RegularAttack::is_skill() const
{
    return false;
}

std::int32_t RegularAttack::get_id() const
{
    return 0;
}

SpecialMove::ForbidReason RegularAttack::can_use(std::int32_t,
                                                 Weapon::Type weapon,
                                                 const Job&,
                                                 std::uint16_t,
                                                 std::uint16_t,
                                                 std::uint16_t bullets) const
{
    switch (weapon) {
    case Weapon::BOW:
    case Weapon::CROSSBOW:
    case Weapon::CLAW:
    case Weapon::GUN:
        return bullets ? FBR_NONE : FBR_BULLETCOST;
    default:
        return FBR_NONE;
    }
}
} // namespace jrc
