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
#pragma once
#include "../../Character/Player.h"
#include "../../Template/TimedQueue.h"
#include "../MapleMap/MapChars.h"
#include "../MapleMap/MapMobs.h"
#include "Attack.h"
#include "RegularAttack.h"
#include "Skill.h"

namespace jrc
{
class Combat
{
public:
    Combat(Player& player, MapChars& chars, MapMobs& mobs);

    //! Draw bullets, damage numbers etc.
    void draw(double viewx, double viewy, float alpha) const;
    //! Poll attacks, damage effects, etc.
    void update();

    //! Make the player use a special move.
    void use_move(std::int32_t move_id);

    //! Add an attack to the attack queue.
    void push_attack(const AttackResult& attack);
    //! Show a buff effect.
    void show_buff(std::int32_t cid, std::int32_t skill_id, std::int8_t level);
    //! Show a buff effect.
    void show_player_buff(std::int32_t skill_id);

private:
    struct DamageEffect {
        AttackUser user;
        DamageNumber number;
        std::int32_t damage;
        bool to_left;
        std::int32_t target_oid;
        std::int32_t move_id;
    };

    struct BulletEffect {
        DamageEffect damage_effect;
        Bullet bullet;
        Point<std::int16_t> target;
    };

    void apply_attack(const AttackResult& attack);
    void apply_move(const SpecialMove& move);
    void apply_use_movement(const SpecialMove& move);
    void apply_result_movement(const SpecialMove& move,
                               const AttackResult& result);
    void apply_rush(const AttackResult& result);
    void apply_bullet_effect(const BulletEffect& effect);
    void apply_damage_effect(const DamageEffect& effect);
    void extract_effects(const Char& user,
                         const SpecialMove& move,
                         const AttackResult& result);
    std::vector<DamageNumber> place_numbers(
        std::int32_t oid,
        const std::vector<std::pair<std::int32_t, bool>>& damage_lines);
    const SpecialMove& get_move(std::int32_t move_id);

    Player& player;
    MapChars& chars;
    MapMobs& mobs;

    std::unordered_map<std::int32_t, Skill> skills;
    RegularAttack regular_attack;

    TimedQueue<AttackResult> attack_results;
    TimedQueue<BulletEffect> bullet_effects;
    TimedQueue<DamageEffect> damage_effects;

    std::vector<BulletEffect> bullets;
    std::vector<DamageNumber> damage_numbers;
};
} // namespace jrc
