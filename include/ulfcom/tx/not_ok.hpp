// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// "NOT OK\r" constant
///
/// \file   ulfcom/tx/not_ok.hpp
/// \author Vincent Hamp
/// \date   15/11/2023

#include <string_view>

namespace ulfcom::tx {

/// Reply to received commands on failure
inline constexpr std::string_view not_ok{"NOT OK\r"};

}  // namespace ulfcom::tx