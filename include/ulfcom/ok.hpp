// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// "OK\r" constant
///
/// \file   ulfcom/tx/ok.hpp
/// \author Vincent Hamp
/// \date   15/11/2023

#pragma once

#include <string_view>

namespace ulfcom {

/// Reply to received commands on success
inline constexpr std::string_view ok{"OK\r"};

}  // namespace ulfcom