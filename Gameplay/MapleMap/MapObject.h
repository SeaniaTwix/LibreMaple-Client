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
#include "../Camera.h"
#include "../Physics/Physics.h"

namespace jrc
{
//! Base for objects on a map, eg. mobs, npcs, characters etc.
class MapObject
{
public:
    virtual ~MapObject() = default;

    //! Draws the object at the given position and with the specified
    //! interpolation.
    virtual void draw(double viewx, double viewy, float alpha) const = 0;

    //! Updates the object and returns the updated layer.
    virtual std::int8_t update(const Physics& physics);
    //! Reactivates the object.
    virtual void activate();
    //! Deactivates the object.
    virtual void deactivate();
    //! Checks whether this object is active or not.
    virtual bool is_active() const;
    //! Obtains the layer used to determine the drawing order on the map.
    virtual std::int8_t get_layer() const;

    //! Changes the objects position.
    void set_position(std::int16_t x, std::int16_t y);
    //! Changes the objects position.
    void set_position(Point<std::int16_t> position);

    //! Returns the object id unique to every object on one map.
    std::int32_t get_oid() const;
    //! Returns the current position.
    Point<std::int16_t> get_position() const;

protected:
    MapObject(std::int32_t oid, Point<std::int16_t> position = {});

    PhysicsObject ph_obj;
    std::int32_t oid;
    bool active;
};
} // namespace jrc
