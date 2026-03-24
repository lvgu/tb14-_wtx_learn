#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace learning::testing {

class AssertionFailure : public std::runtime_error {
 public:
  explicit AssertionFailure(const std::string& message) : std::runtime_error(message) {}
};

struct TestCase {
  std::string name;
  std::function<void()> function;
};

class TestRegistry {
 public:
  static TestRegistry& instance() {
    static TestRegistry registry;
    return registry;
  }

  void register_test(std::string name, std::function<void()> function) {
    tests_.push_back(TestCase{std::move(name), std::move(function)});
  }

  [[nodiscard]] const std::vector<TestCase>& tests() const noexcept { return tests_; }

 private:
  std::vector<TestCase> tests_;
};

class TestRegistrar {
 public:
  TestRegistrar(const char* name, std::function<void()> function) {
    TestRegistry::instance().register_test(name, std::move(function));
  }
};

inline std::string format_location(const char* file, int line) {
  std::ostringstream oss;
  oss << file << ":" << line;
  return oss.str();
}

namespace detail {

template <typename T, typename = void>
struct is_streamable : std::false_type {};

template <typename T>
struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream&>() <<
                                             std::declval<const T&>())>> : std::true_type {};

template <typename T>
std::string to_string(const T& value) {
  if constexpr (is_streamable<T>::value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  } else {
    return "<unprintable>";
  }
}

}  // namespace detail

inline void expect_true(bool condition, const char* expr, const char* file, int line) {
  if (condition) {
    return;
  }

  std::ostringstream oss;
  oss << format_location(file, line) << " expected true: " << expr;
  throw AssertionFailure(oss.str());
}

template <typename L, typename R>
void expect_eq(const L& lhs, const R& rhs, const char* lhs_expr, const char* rhs_expr,
               const char* file, int line) {
  if (lhs == rhs) {
    return;
  }

  std::ostringstream oss;
  oss << format_location(file, line) << " expected equality: " << lhs_expr << " == "
      << rhs_expr << " (lhs=" << detail::to_string(lhs)
      << ", rhs=" << detail::to_string(rhs) << ")";
  throw AssertionFailure(oss.str());
}

inline int run_all_tests(std::ostream& out = std::cout) {
  const auto& tests = TestRegistry::instance().tests();
  int failed_count = 0;

  for (const auto& test : tests) {
    try {
      test.function();
      out << "[PASS] " << test.name << "\n";
    } catch (const AssertionFailure& ex) {
      ++failed_count;
      out << "[FAIL] " << test.name << " -> " << ex.what() << "\n";
    } catch (const std::exception& ex) {
      ++failed_count;
      out << "[FAIL] " << test.name << " -> unexpected exception: " << ex.what() << "\n";
    } catch (...) {
      ++failed_count;
      out << "[FAIL] " << test.name << " -> unknown exception\n";
    }
  }

  const int total = static_cast<int>(tests.size());
  out << "\nSummary: " << (total - failed_count) << "/" << total << " tests passed.\n";
  return failed_count == 0 ? 0 : 1;
}

}  // namespace learning::testing

#define LEARNING_DETAIL_CONCAT_INNER(left, right) left##right
#define LEARNING_DETAIL_CONCAT(left, right) LEARNING_DETAIL_CONCAT_INNER(left, right)

#define LEARNING_TEST(name)                                                     \
  static void name();                                                           \
  static ::learning::testing::TestRegistrar LEARNING_DETAIL_CONCAT(             \
      learning_test_registrar_, __LINE__)(#name, name);                        \
  static void name()

#define LEARNING_EXPECT_TRUE(expr) \
  ::learning::testing::expect_true((expr), #expr, __FILE__, __LINE__)

#define LEARNING_EXPECT_EQ(lhs, rhs) \
  ::learning::testing::expect_eq((lhs), (rhs), #lhs, #rhs, __FILE__, __LINE__)
