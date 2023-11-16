#include <ulfcom/ulfcom.hpp>

int main() {
  // Check if character stream contains valid MX1 binary
  auto maybe_mx1bin{ulfcom::str2mx1bin("\x01\x01"
                                       "data\x17")};

  // Could be MX1 binary
  if (maybe_mx1bin) {
    // Already complete?
    if (*maybe_mx1bin) {
      // Complete MX1 binary
      auto mx1bin{**maybe_mx1bin};
    }
    // No, still missing characters
    else {}
  }
  // Error, not MX1 binary scheme
  else {}

  // Replies to "PING\r"
  auto ping{ulfcom::ping("MyDevice", "1.2.3")};
  auto ping_with_rev{ulfcom::ping("MyDevice", "1.2.3", 'B')};
}