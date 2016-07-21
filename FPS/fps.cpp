
//
// 処理落ち対策のFPS検出に使えそうな実験
//

#include <iostream>
#include <chrono>
#include <thread>

int main()
{
  using namespace std::chrono;
  typedef steady_clock::time_point  t_point;
  typedef milliseconds              m_sec;

  t_point begin = steady_clock::now();

  std::this_thread::sleep_for(seconds(3));

  t_point end = steady_clock::now();

  m_sec elapsed_time = duration_cast<m_sec>(end - begin);

  std::cout << elapsed_time.count() << std::endl;
}

//
// 実験結果
// . 1frame として吐き出すには何らかの形で変換する必要がある
//
