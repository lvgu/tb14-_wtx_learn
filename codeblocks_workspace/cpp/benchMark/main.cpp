#include <iostream>
#include <shlwapi.h>
#include "benchmark/benchmark.h"

#include <io.h>


#include "h/test.h"


/**<
��Ҫʹ�����Google benchkmark
�һ�������һ�����ã�
��build option������
�� BENCHMARK_STATIC_DEFINE
c++��׼Ϊstd17

��������benchmark��̬���һ��C:\Windows\System32\Shlwapi.dll��̬��
���ӵ� -lshlwapi�����


 */
using namespace std;


static void BM_test_wrap(benchmark::State& state)
{
    for (auto _ : state) {
        test();  // ��Ĳ��Ժ���
//        testCpp();
    }
}

/**< google benchmark Ĭ�ϻ����ж�Σ�����Ϊ�ռ������ʵ���Ϣ��ֹͣ */
//BENCHMARK(BM_test_wrap);
/**< �����������ã�ֻ����һ�� */
BENCHMARK(BM_test_wrap)->Iterations(1); // ��������һ��

BENCHMARK_MAIN();



