
#include <iostream>
#include <functional>


typedef std::function<void()>  Sequence;

class Sequencer
{
public:
  Sequencer() :
    prev_(nullptr),
    now_(nullptr),
    next_(nullptr)
  {
  }

  void execute()
  {
    if (next_)
    {
      prev_ = now_;
      now_ = next_;
      next_ = nullptr;
    }
    now_();
  }

  void setAction(const Sequence sequence = nullptr)
  {
    next_ = sequence;
  }

private:
  Sequence prev_;
  Sequence now_;
  Sequence next_;
};


class Object
{
public:
  Object()
  {
    sequence_.setAction(std::bind(&Object::start, this));
  }

  void draw()
  {
    sequence_.execute();
  }

private:
  Sequencer sequence_;

  void start()
  {
    std::cout << "Object.Start" << std::endl;
    sequence_.setAction(std::bind(&Object::update, this));
  }

  void update()
  {
    std::cout << "Object.Update" << std::endl;
    sequence_.setAction(std::bind(&Object::finish, this));
  }

  void finish()
  {
    std::cout << "Object.Finish" << std::endl;
    sequence_.setAction();
  }
};


int main()
{
  Object object;

  object.draw();   // Object.Start
  object.draw();   // Object.Update
  object.draw();   // Object.Finish
  object.draw();   // Object.Finish
}
