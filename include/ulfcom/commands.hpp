// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// ULFCom
///
/// \file   ulfcom/commands.hpp
/// \author Vincent Hamp
/// \date   15/11/2023

#include <array>
#include <string_view>

namespace ulfcom {

using namespace std::literals;

/// Array of commands
constexpr std::array commands{
  // General
  "PING\r"sv,

  // Protocols
  "DCC_EIN\r"sv,
  "DECUP_EIN\r"sv,
  "MDUSNDPREP\r"sv,
  "SUSIV2\r"sv,
};

}  // namespace ulfcom