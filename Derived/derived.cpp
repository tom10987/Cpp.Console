
//
// 2015/11/24
// 継承クラスにおける、仮想関数とオーバーライドの実験
//
// 実験内容：
// 子クラスの仮想関数につけた修飾子が、孫クラスにどんな影響を与えるか
//
// 結果：
// 基底クラスの仮想関数と一致してさえいれば、
// 途中にどんな修飾子がついてもオーバーライドとして機能する
//
// override 修飾子
// 仮想関数をオーバーライドしていることを明示するだけ
// 修飾子なしでも、基底クラスに仮想関数があればオーバーライド可能（理由は後述）
// 逆に言えば、基底クラスに仮想関数がない場合、override 修飾はできない
//
// final 修飾子
// 修飾子を付けたクラス以降の派生クラスでオーバーライドを禁止する
//
// override, final が実装される前から、仮想関数のオーバーライドは可能だった
// これらの実装以前との互換性維持のため、コンパイラは構文で判断する
// そのため、関数名などに override, final は使用可能
//

#include <iostream>
#include <string>


void output(const std::string& str) { std::cout << str << std::endl; }


class Object
{
public:
  Object() { output("----- Object() -----"); }
  virtual ~Object() { output("----- ~Object() -----"); }

  virtual void setup() { output("Object::setup()"); }
  virtual void update() { output("Object::update()"); }
  virtual void draw() { output("Object::draw()"); }
  virtual void release() { output("Object::release()"); }
  virtual void initialize() { output("Object::initialize()"); }

  void destroy() { output("Object::destroy()"); }
};


class ObjectDerived : public Object
{
public:
  ObjectDerived() { output("----- ObjectDerived() -----"); }
  virtual ~ObjectDerived() { output("----- ~ObjectDerived() -----"); }

  // virtual, override 両方
  virtual void setup() override { output(">> ObjectDerived::setup()"); }

  // virtual のみ
  virtual void update() { output(">> ObjectDerived::update()"); }

  // override のみ
  void draw() override { output(">> ObjectDerived::draw()"); }

  // なし
  void release() { output(">> ObjectDerived::release()"); }

  // initialize() は記述しない

  // なし（仮想関数ではない）
  void destroy() { output(">> ObjectDerived::destroy()"); }
};


class ObjectDerivedDerived : public ObjectDerived
{
public:
  ObjectDerivedDerived() { output("----- ObjectDerivedDerived() -----"); }
  ~ObjectDerivedDerived() { output("----- ~ObjectDerivedDerived() -----"); }

  void setup() override { output(">> >> ObjectDerivedDerived::setup()"); }
  void update() override { output(">> >> ObjectDerivedDerived::update()"); }
  void draw() override { output(">> >> ObjectDerivedDerived::draw()"); }
  void release() { output(">> >> ObjectDerivedDerived::release()"); }
  void initialize() override { output(">> >> ObjectDerivedDerived::initialize()"); }

  void destroy() { output(">> >> ObjectDerivedDerived::destroy()"); }
};


// 仮想関数をオーバーライドしないクラス
class ObjectDerivedAnother : public ObjectDerived
{
public:
  ObjectDerivedAnother() { output("----- ObjectDerivedAnother() -----"); }
  ~ObjectDerivedAnother() { output("----- ~ObjectDerivedAnother() -----"); }
};


int main()
{
  const auto execute = [](Object* object)
  {
    output(" ");
    object->setup();
    object->update();
    object->draw();
    object->release();
    object->initialize();
    object->destroy();
    output(" ");

    delete object;
  };

  execute(new ObjectDerivedDerived());
  output(" ");
  execute(new ObjectDerivedAnother());
}
