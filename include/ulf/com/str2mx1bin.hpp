// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert string to MX1 binary
///
/// \file   ulf/com/str2mx1bin.hpp
/// \author Vincent Hamp
/// \date   17/11/2023

#pragma once

#include <expected>
#include <optional>
#include <string_view>
#include <system_error>

namespace ulf::com {

/// Convert string to MX1 binary
///
/// String should have the pattern "\x01\x01.+?(?<!\x10)\x17". If the
/// string contains multiple MX1 binary frames only the first one is returned.
///
/// \param  str                         String
/// \return std::string_view            View of the received MX1 binary
/// \return std::nullopt                Not enough characters
/// \return std::errc::invalid_argument Invalid MX1 binary
constexpr std::expected<std::optional<std::string_view>, std::errc>
str2mx1bin(std::string_view str) {
  auto const count{size(str)};
  // Can't be MX1 binary yet
  if (!count) return std::nullopt;
  // Not start of heading (SOH)
  else if ((count >= 1uz && str[0uz] != '\x01') ||
           (count >= 2uz && str[1uz] != '\x01'))
    return std::unexpected(std::errc::invalid_argument);
  // Look for end of transmission block (ETB)
  for (auto i{2uz}; i < count; ++i)
    if (str[i - 1uz] != '\x10' && str[i] == '\x17')
      return str.substr(0uz, i + 1uz);
  // Not enough characters
  return std::nullopt;
}

}  // namespace ulf::com