
//
// Observer パターンの実験
//

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <list>


// 監視役の基底クラス
class Observer
{
public:
  Observer() {}
  virtual void Update() {}
};


// 監視対象の基底クラス
class Subject
{
  typedef std::shared_ptr<Observer>  ObserverRef;

public:
  Subject() {}

  // 自身を監視する、監視役を登録
  void AddObserver(const ObserverRef observer)
  {
    list.emplace_back(observer);
  }

  // 登録を破棄
  void RemoveObserver()
  {
    list.pop_front();
  }

  // 登録済みの全ての監視役に、自身の更新を通知
  void NotifyObservers()
  {
    std::cout << list.size() << std::endl;
    for (auto observer : list) { observer->Update(); }
  }

private:
  std::list<ObserverRef> list;
};


// 監視対象
class Model : public Subject
{
public:
  Model() {}

  void SetName(const std::string& str) { name = str; }
  const std::string& GetName() const { return name; }

private:
  std::string name;
};


// 監視役
class View : public Observer
{
public:
  View(Model& m) : model(m) {}

  void SetName(const std::string name) { viewName = name; }

  // 監視対象からの通知を受けて実行する処理
  void Update() override
  {
    std::cout << ">> model name change." << std::endl;
    Draw();
  }

  // 普段の処理
  void Draw()
  {
    std::cout << "model name is ";
    std::cout << model.GetName() << std::endl;
    std::cout << "viewer is ";
    std::cout << viewName << std::endl;
  }

private:
  Model& model;
  std::string viewName;
};


int main()
{
  Model model;
  model.SetName("first");

  std::vector<std::shared_ptr<View> > view;

  // 監視役に監視させる対象を登録
  for (int i = 0; i < 3; i++)
  {
    view.push_back(std::make_shared<View>(model));
  }

  view[0]->SetName("hoge");
  view[1]->SetName("fuga");
  view[2]->SetName("piyo");

  // Model に View を登録
  for (auto v : view) { model.AddObserver(v); }

  // View の描画
  for (auto v : view) { v->Draw(); }
  std::cout << std::endl;

  // Model 変更
  model.SetName("second");

  // Model 変更の通知
  model.NotifyObservers();
}
