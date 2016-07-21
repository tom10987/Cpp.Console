
//
// MonoState パターンの実験
//

#include <iostream>
#include <string>


void Output(const std::string& str)
{
  std::cout << str << std::endl;
}


// 外部に静的なメンバを置く場合
struct State
{
  static int score;
  static std::string name;
};
int State::score = 0;
std::string State::name = "";


// 外部にあるパラメータを扱うクラス１
class Hoge
{
public:
  Hoge() { Output("Hoge()"); }

  void Update(int value)
  {
    State::score += value;
  }

  void Draw()
  {
    std::cout << State::score << std::endl;
  }
};


// 外部にあるパラメータを扱うクラス２
class Fuga
{
public:
  Fuga() { Output("Fuga()"); }

  void Update(int value)
  {
    State::score += value;
  }

  void Draw()
  {
    std::cout << State::score << std::endl;
  }
};


// 内部にある静的なメンバを扱うクラス
class Piyo
{
public:
  Piyo() { Output("Piyo()"); }

  void Update(int value)
  {
    score += value;
  }

  void Draw()
  {
    std::cout << score << std::endl;
  }

private:
  static int score;
};
int Piyo::score = 0;


int main()
{
  {
    Hoge hoge;
    hoge.Draw();
    hoge.Update(10);
    hoge.Draw();
  }
  {
    Fuga fuga;
    fuga.Draw();
    fuga.Update(-20);
    fuga.Draw();
  }
  {
    Piyo piyo;
    piyo.Draw();
    piyo.Update(100);
    piyo.Draw();
  }
  {
    Piyo piyo;
    piyo.Draw();
    piyo.Update(-30);
    piyo.Draw();
  }
}

/*
 * 結論

 * 内部に静的なメンバを置いたほうが、
 * 外部からのアクセスに制限をかけられるので、状態の保守性が高い
 * ただし、そのクラスしかデータに触れることができない

 * 外部にデータを置いた場合、グローバル変数とほとんど差がない代わりに、
 * 同じデータに対して、クラス毎に異なる振る舞いを設計することができる

 *
 */

/*
 * MonoState と Singleton の違い

 * Singleton は、インスタンスそのものが１つしかないことを保証する

 * MonoState は、インスタンス自体は複数存在できるが、内部で扱うデータが１つしか存在しない
 * つまり、複数のインスタンスが同じデータを扱うことができる

 * Singleton はその構造上、継承させることができない
 * 継承することによって、インスタンスが１つであることを保証できなくなるため

 * MonoState は継承が可能
 * 振る舞いはクラスごとに変えることが可能なため、
 * 親クラスにデータを持たせて、派生クラスに振る舞いを設計するといった方法が可能

 *
 */
