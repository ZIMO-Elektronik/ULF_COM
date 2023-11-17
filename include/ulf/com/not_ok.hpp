// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// "NOT OK\r" constant
///
/// \file   ulf/com/not_ok.hpp
/// \author Vincent Hamp
/// \date   17/11/2023

#pragma once

#include <string_view>

namespace ulf::com {

/// Reply to received commands on failure
inline constexpr std::string_view not_ok{"NOT OK\r"};

}  // namespace ulf::com