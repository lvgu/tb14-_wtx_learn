#include <iostream>
#include <shlwapi.h>
#include "benchmark/benchmark.h"

#include <io.h>


#include "h/test.h"


/**<
想要使用这个Google benchkmark
我还进行了一下设置，
在build option中设置
宏 BENCHMARK_STATIC_DEFINE
c++标准为std17

加上两个benchmark静态库和一个C:\Windows\System32\Shlwapi.dll动态库
链接到 -lshlwapi这个库


 */
using namespace std;


static void BM_test_wrap(benchmark::State& state)
{
    for (auto _ : state) {
        test();  // 你的测试函数
//        testCpp();
    }
}

/**< google benchmark 默认会运行多次，在认为收集到合适的信息后停止 */
//BENCHMARK(BM_test_wrap);
/**< 可以这样设置，只允许一次 */
BENCHMARK(BM_test_wrap)->Iterations(1); // 设置运行一次

BENCHMARK_MAIN();



