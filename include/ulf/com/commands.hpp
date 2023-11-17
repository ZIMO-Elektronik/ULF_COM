// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Commands
///
/// \file   ulf/com/commands.hpp
/// \author Vincent Hamp
/// \date   17/11/2023

#pragma once

#include <array>
#include <string_view>

namespace ulf::com {

using namespace std::literals;

/// Commands
inline constexpr std::array commands{
  // General
  "PING\r"sv,

  // Protocols (mode changes)
  "DCC_EIN\r"sv,
  "DECUP_EIN\r"sv,
  "MDU_EIN\r"sv,
  "SUSIV2\r"sv,
};

}  // namespace ulf::com