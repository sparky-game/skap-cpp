#include <chrono>
#include <skap_header.hh>

static inline uint64_t concat_num(uint64_t x, uint64_t y) {
  uint64_t n = 10;
  while (y >= n) n *= 10;
  return n * x + y;
}

static inline uint64_t compute_build_ver(void) {
  auto now { std::chrono::system_clock::now() };
  std::time_t t { std::chrono::system_clock::to_time_t(now) };
  std::tm *t_spec { std::localtime(&t) };
  std::array<uint64_t, 4> t_spec_arr {
    static_cast<uint64_t>(t_spec->tm_mon + 1),
    static_cast<uint64_t>(t_spec->tm_mday),
    static_cast<uint64_t>(t_spec->tm_hour),
    static_cast<uint64_t>(t_spec->tm_min)
  };
  uint64_t build_ver { static_cast<uint64_t>(t_spec->tm_year + 1900) };
  for (const auto &i : t_spec_arr) {
    if (i < 10) build_ver *= 10;
    build_ver = concat_num(build_ver, i);
  }
  return build_ver;
}

namespace skap {
  Header::Header(HeaderIndexCounters &&counters) noexcept
    : signature{{ 'S', 'K', 'A', 'P' }}, fmt_ver{1}, build_ver{ compute_build_ver() }, idx_counters{ std::move(counters) }
  {}
}
