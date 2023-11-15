// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

///
///
/// \file   ulfcom/rx/str2binary.hpp
/// \author Vincent Hamp
/// \date   15/11/2023

#include <expected>
#include <optional>
#include <string_view>
#include <system_error>

namespace ulfcom::rx {

std::expected<std::optional<std::string_view>, std::errc>
str2binary(std::string_view str) {
  auto const count{size(str)};
  if (!count) return std::nullopt;
  if ((count >= 1uz && str[0uz] != '\x01') ||
      (count >= 2uz && str[1uz] != '\x01'))
    return std::unexpected(std::errc::bad_message);
  for (auto i{2uz}; i < count; ++i)
    if (str[i - 1uz] != '\x10' && str[i] == '\x17')
      return str.substr(0uz, i + 1uz);
  return std::nullopt;
}

}  // namespace ulfcom::rx