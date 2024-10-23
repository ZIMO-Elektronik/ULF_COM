#include <iostream>
#include <ulf/com.hpp>

using namespace std::literals;

void str2cmd() {
  // Check if character stream contains valid command
  auto maybe_cmd{ulf::com::str2cmd("DCC_EIN\r and then some")};

  // Could be command
  if (maybe_cmd) {
    // Already complete?
    if (*maybe_cmd) {
      // Complete command
      auto cmd{**maybe_cmd};
      std::cout << cmd << "\n";
    }
    // No, still missing characters
    else {}
  }
  // Error, not command
  else {}

  // Or, more concise
  if (maybe_cmd == "DCC_EIN\r"sv) std::cout << "Command found\n";
}

void str2mx1bin() {
  // Check if character stream contains valid MX1 binary
  auto maybe_mx1bin{ulf::com::str2mx1bin("\x01\x01"
                                         "data\x17")};

  // Could be MX1 binary
  if (maybe_mx1bin) {
    // Already complete?
    if (*maybe_mx1bin) {
      // Complete MX1 binary
      auto mx1bin{**maybe_mx1bin};
      std::cout << mx1bin << "\n";
    }
    // No, still missing characters
    else {}
  }
  // Error, not MX1 binary scheme
  else {}
}

void ping() {
  // Replies to "PING\r"
  auto ping{ulf::com::ping("MyDevice", "1.2.3")};
  auto ping_with_rev{ulf::com::ping("MyDevice", "1.2.3", 'B')};
}

int main() {
  str2cmd();
  str2mx1bin();
  ping();
}