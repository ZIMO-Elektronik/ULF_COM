// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert string to command
///
/// \file   ulfcom/rx/str2cmd.hpp
/// \author Vincent Hamp
/// \date   15/11/2023

#pragma once

#include <expected>
#include <optional>
#include <string_view>
#include <system_error>
#include "commands.hpp"

namespace ulfcom {

/// Convert string to command
///
/// String must be any of the ones in the commands array.
///
/// \param  str                     String
/// \return std::string_view        View of the received command
/// \return std::nullopt            Not enough characters
/// \return std::errc::bad_message  Invalid command
constexpr std::expected<std::optional<std::string_view>, std::errc>
str2cmd(std::string_view str) {
  auto const it{std::ranges::find_if(commands, [&str](std::string_view cmd) {
    return size(cmd) >= size(str) ? cmd.starts_with(str) : str.starts_with(cmd);
  })};
  // Command not found
  if (it == cend(commands)) return std::unexpected(std::errc::bad_message);
  // Command found (and complete)
  else if (size(str) >= size(*it)) return *it;
  // Not enough characters
  return std::nullopt;
}

}  // namespace ulfcom
