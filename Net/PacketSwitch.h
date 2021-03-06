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
#include "PacketHandler.h"

#include <array>
#include <memory>
#include <type_traits>

namespace jrc
{
//! Class which contains the array of handler classes to use.
class PacketSwitch
{
public:
    //! Register all handlers.
    PacketSwitch();

    //! Forward a packet to the correct handler.
    void forward(const std::int8_t* bytes, std::size_t length) const;

private:
    //! Print a warning to the console about something strange or amiss in
    //! the packet switcher.
    void warn(std::string_view message, std::size_t opcode) const noexcept;

    //! Opcodes for which handlers can be registered.
    enum Opcode : std::uint16_t;

    //! Message when an unhandled packet is received.
    static constexpr const char* MSG_UNHANDLED = "Unhandled packet detected";
    //! Message when a packet with a larger opcode than the array size is
    //! received.
    static constexpr const char* MSG_OUT_OF_BOUNDS = "Large opcode detected";
    //! Message when a handler is registered more than once.
    static constexpr const char* MSG_REREGISTER
        = "Handler was registered twice";
    //! Maximum number of handlers needed.
    static constexpr const std::size_t NUM_HANDLERS = 500;

    std::array<std::unique_ptr<PacketHandler>, NUM_HANDLERS> handlers;

    //! Register a handler for the specified opcode.
    template<std::size_t O, typename T, typename... Args>
    void emplace(Args&&... args)
    {
        static_assert(O < NUM_HANDLERS,
                      "PacketSwitch::emplace - Opcode out of array bounds.");
        static_assert(
            std::is_base_of<PacketHandler, T>::value,
            "Error: Packet handlers must derive from PacketHandler.");

        if (handlers[O]) {
            warn(MSG_REREGISTER, O);
        }

        handlers[O] = std::make_unique<T>(std::forward<Args>(args)...);
    }
};
} // namespace jrc
