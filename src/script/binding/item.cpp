/*
 *  illarionserver - server for the game Illarion
 *  Copyright 2011 Illarion e.V.
 *
 *  This file is part of illarionserver.
 *
 *  illarionserver is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  illarionserver is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with illarionserver.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Item.hpp"
#include <data/Data.hpp>
#include "script/binding/binding.hpp"

namespace binding {

    luabind::scope item() {
        luabind::value_vector items;

        for (const auto &item: Data::Items) {
            const auto &name = item.second.serverName;

            if (name.length() > 0) {
                items.push_back(luabind::value(name.c_str(), item.second.id));
            }
        }

        return luabind::class_<Item>("Item")
                .def(luabind::constructor<>())
                .def(luabind::constructor<Item::id_type, Item::number_type, Item::wear_type, Item::quality_type>())
                .enum_("items")
                [
                    items
                ]
                .property("id", &Item::getId, &Item::setId)
                .property("wear", &Item::getWear, &Item::setWear)
                .property("number", &Item::getNumber, &Item::setNumber)
                .property("quality", &Item::getQuality, &Item::setQuality)
                .def("setData", (void(Item:: *)(const std::string &, const std::string &))&Item::setData)
                .def("setData", (void(Item:: *)(const std::string &, int32_t))&Item::setData)
                .def("getData", (std::string(Item:: *)(const std::string &))&Item::getData)
                .def("isLarge", &Item::isLarge);
    }

}