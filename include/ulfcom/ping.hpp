// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Reply to "PING\r" command
///
/// \file   ulfcom/tx/ping.hpp
/// \author Vincent Hamp
/// \date   15/11/2023

#pragma once

#include <cassert>
#include <cstring>
#include <string_view>
#include <ztl/inplace_vector.hpp>

namespace ulfcom {

/// Reply to "PING\r" command
///
/// Generate reply to "PING\r" command. This reply contains the device name, the
/// current version and optionally it's hardware revision.
///
/// \param  device_name Device name
/// \param  version     Version
/// \return Reply to "PING\r" command
constexpr auto ping(char const* device_name, char const* version) {
  assert(device_name && version);
  ztl::inplace_vector<char,
                      ULFCOM_MAX_DEVICE_NAME_LEN +  // Device name
                        sizeof(' ') +               // Space
                        sizeof('v') +               // Version identifier
                        ULFCOM_MAX_VERSION_LEN +    // Version
                        sizeof(' ') +               // Space
                        sizeof('h') +               // Revision identifier
                        sizeof(char) +              // Revision
                        sizeof('\r')>               // Carriage return
    retval{};
  auto const first{cbegin(retval)};
  auto last{
    std::copy_n(device_name,
                std::min(strlen(device_name), ULFCOM_MAX_DEVICE_NAME_LEN),
                begin(retval))};
  *last++ = ' ';
  *last++ = 'v';
  last = std::copy_n(
    version, std::min(strlen(version), ULFCOM_MAX_VERSION_LEN), last);
  *last++ = '\r';
  retval.resize(static_cast<decltype(retval)::size_type>(last - first));
  return retval;
}

/// Reply to "PING\r" command
///
/// Generate reply to "PING\r" command. This reply contains the device name, the
/// current version and optionally it's hardware revision.
///
/// \param  device_name Device name
/// \param  version     Version
/// \param  revision    Hardware revision
/// \return Reply to "PING\r" command
constexpr auto
ping(char const* device_name, char const* version, char revision) {
  auto retval{ping(device_name, version)};
  retval.back() = ' ';
  retval.push_back('h');
  retval.push_back(revision);
  retval.push_back('\r');
  return retval;
}

}  // namespace ulfcom