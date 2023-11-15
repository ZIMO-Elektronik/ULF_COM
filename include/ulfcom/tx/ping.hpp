// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Reply to "PING\r" command
///
/// \file   ulfcom/tx/ping.hpp
/// \author Vincent Hamp
/// \date   15/11/2023

#include <string_view>

namespace ulfcom::tx {

// inplace_vector...?
inline std::array<char,
                  ULFCOM_MAX_DEVICE_NAME_LEN +  // Device name
                    sizeof(' ') +               // Space
                    sizeof('v') +               // Version identifier
                    ULFCOM_MAX_VERSION_LEN +    // Version
                    sizeof(' ') +               // Space
                    sizeof('h') +               // Revision identifier
                    sizeof(char) +              // Revision
                    sizeof('\r')>               // Carriage return
ping(char const* device_name, char const* version, char revision) {
  return {};
}

}  // namespace ulfcom::tx