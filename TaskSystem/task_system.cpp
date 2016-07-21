
#include <iostream>
#include <memory>
#include <functional>
#include <map>
#include <unordered_map>


enum class ObjType
{
  Object,
  SubObject,
  All_Object,
};


class ObjSuper
{
public:
  const ObjType& getType() const { return m_type; }

  virtual void update() = 0;
  virtual void draw() = 0;

protected:
  ObjType m_type;

  ObjSuper() = default;
  ~ObjSuper() = default;
};
typedef std::shared_ptr<ObjSuper>  pObjSuper;


class Object : public ObjSuper
{
public:
  Object() : m_hoge(0) { m_type = ObjType::Object; };

  void update() { std::cout << "object update..." << std::endl; }
  void draw() { std::cout << "object_data = " << m_hoge << std::endl; }

  void increment() { ++m_hoge; }

private:
  int m_hoge;
};


class SubObject : public ObjSuper
{
public:
  SubObject() : m_hoge(100) { m_type = ObjType::SubObject; };

  void update() { std::cout << "sub_obj update..." << std::endl; }
  void draw() { std::cout << "sub_obj_data = " << m_hoge << std::endl; }

private:
  int m_hoge;
};


class Task
{
public:
  static Task& get()
  {
    static Task s_instance;
    return s_instance;
  }

  void update() { for (auto& it : m_obj) it.second->update(); }
  void draw() { for (auto& it : m_obj) it.second->draw(); }

  void append(const pObjSuper obj)
  {
    const auto add = std::make_pair(obj->getType(), obj);
    m_obj.insert(add);
  }

  template<class OBJ>
  OBJ& getObject(const ObjType key) const
  {
    auto& p_obj = m_obj.find(key)->second;
    return *std::dynamic_pointer_cast<OBJ>(p_obj);
  }

private:
  std::map<ObjType, pObjSuper> m_obj;
};


int main()
{
  Task::get().append(pObjSuper(new Object()));
  Task::get().append(pObjSuper(new SubObject()));

  // �^�X�N�ɒǉ����ꂽ�I�u�W�F�N�g��S�čX�V�A�`��
  Task::get().update();
  Task::get().draw();
  std::cout << std::endl;

  // �^�X�N�ɓ����Ă���I�u�W�F�N�g�����o���čX�V�A�`��
  {
    auto& obj = Task::get().getObject<Object>(ObjType::Object);
    obj.update();
    obj.increment();
    obj.draw();
    std::cout << std::endl;
  }

  // �^�X�N�ɓ����Ă���I�u�W�F�N�g��S�čX�V�A�`��
  // �����o�����I�u�W�F�N�g�̍X�V���e���c���Ă����Ԃ��m�F ... OK
  Task::get().update();
  Task::get().draw();
}
