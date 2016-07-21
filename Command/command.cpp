
//
// Command パターンの実験
//

//
// 結論
// MVC モデルで設計すれば、クラス内のメンバに変更を加えられるはず
//
// 2015/11/14 追記
// C# で実装、C++ に逆輸入する方法で実装に挑戦してみる
//

#include <iostream>


void output(const std::string& str) { std::cout << str.c_str() << std::endl; }


// 行動の一覧
class ObjectAction
{
// Model この辺に置く
public:
  void Action1() { output(">> act_1"); }
  void Action2() { output(">> act_2"); }
  void Action3() { output(">> act_3"); }
  void Action4() { output(">> act_4"); }
};


// 基底クラス
class Object
{
public:
  virtual void update() = 0;

protected:
  Object(ObjectAction* p) : p_actor_(p) {}
  ObjectAction* p_actor_;
};


// 派生１
class Player : public Object
{
public:
  Player(ObjectAction* p) : Object(p) {}

  void update() override
  {
    output("Player.update");
    p_actor_->Action1();
    p_actor_->Action2();
  }
};


// 派生２
class Enemy : public Object
{
public:
  Enemy(ObjectAction* p) : Object(p) {}

  void update() override
  {
    output("Enemy.update");
    p_actor_->Action3();
    p_actor_->Action4();
  }
};


// 実行クラス
class Executer
{
public:
  Executer(Object* p) : p_obj_(p) {}
  void update() { p_obj_->update(); }

private:
  Object* p_obj_;
};


int main()
{
  ObjectAction action;
  Object* obj = new Player(&action);

  Executer exe(obj);
  exe.update();

  delete obj;
  obj = nullptr;
}
