#pragma once

#include <array>
#include <cstdint>

namespace skap {
  struct HeaderIndexCounters {
    std::size_t image;
    std::size_t audio;
  };

  struct Header {
    std::array<char, 4> signature;
    uint8_t fmt_ver;
    uint64_t build_ver;
    HeaderIndexCounters idx_counters;
    Header(HeaderIndexCounters &&counters) noexcept;
  };
}
