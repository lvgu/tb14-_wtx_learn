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

// 断言失败异常：测试断言不满足时抛出
class AssertionFailure : public std::runtime_error {
 public:
  explicit AssertionFailure(const std::string& message) : std::runtime_error(message) {}
};

// 单个测试用例：名称 + 可调用对象
struct TestCase {
  std::string name;
  std::function<void()> function;
};

// 全局测试注册表（单例）
class TestRegistry {
 public:
  // 通过函数内静态变量保证线程安全初始化
  static TestRegistry& instance() {
    static TestRegistry registry;
    return registry;
  }

  // 注册测试函数
  void register_test(std::string name, std::function<void()> function) {
    tests_.push_back(TestCase{std::move(name), std::move(function)});
  }

  // 获取全部测试用例（只读）
  [[nodiscard]] const std::vector<TestCase>& tests() const noexcept { return tests_; }

 private:
  std::vector<TestCase> tests_;
};

// 静态注册器：在全局初始化阶段把测试函数塞进注册表
class TestRegistrar {
 public:
  TestRegistrar(const char* name, std::function<void()> function) {
    TestRegistry::instance().register_test(name, std::move(function));
  }
};

// 格式化源码位置，便于定位失败断言
inline std::string format_location(const char* file, int line) {
  std::ostringstream oss;
  oss << file << ":" << line;
  return oss.str();
}

namespace detail {

// 编译期判断类型是否可以直接输出到 std::ostream
template <typename T, typename = void>
struct is_streamable : std::false_type {};

template <typename T>
struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream&>() <<
                                             std::declval<const T&>())>> : std::true_type {};

// 通用转字符串：可输出类型直接输出，不可输出类型返回占位符
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

// 断言表达式为真
inline void expect_true(bool condition, const char* expr, const char* file, int line) {
  if (condition) {
    return;
  }

  std::ostringstream oss;
  oss << format_location(file, line) << " expected true: " << expr;
  throw AssertionFailure(oss.str());
}

// 断言两侧相等，并在失败时输出 lhs/rhs 的值
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

// 执行所有已注册测试并输出结果汇总
inline int run_all_tests(std::ostream& out = std::cout) {
  const auto& tests = TestRegistry::instance().tests();
  int failed_count = 0;

  for (const auto& test : tests) {
    try {
      // 执行单条测试
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
  // 与命令行约定：0 表示全部通过，非 0 表示有失败
  return failed_count == 0 ? 0 : 1;
}

}  // namespace learning::testing

// 预处理拼接辅助宏
#define LEARNING_DETAIL_CONCAT_INNER(left, right) left##right
#define LEARNING_DETAIL_CONCAT(left, right) LEARNING_DETAIL_CONCAT_INNER(left, right)

// 定义测试用例并自动注册
#define LEARNING_TEST(name)                                                     \
  static void name();                                                           \
  static ::learning::testing::TestRegistrar LEARNING_DETAIL_CONCAT(             \
      learning_test_registrar_, __LINE__)(#name, name);                        \
  static void name()

// 断言宏：自动带上源码文件和行号
#define LEARNING_EXPECT_TRUE(expr) \
  ::learning::testing::expect_true((expr), #expr, __FILE__, __LINE__)

#define LEARNING_EXPECT_EQ(lhs, rhs) \
  ::learning::testing::expect_eq((lhs), (rhs), #lhs, #rhs, __FILE__, __LINE__)
