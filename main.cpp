#include <iostream>

using namespace std;

class Memento {
private:
    friend class Number;
    int state;
public:
    Memento(int val)
    {
        state = val;
    }
};

class Number {
private:
    int Value;
public:
    Number(int value) {

        Value = value;

    }
    void Double() {

        Value = 2 * Value;

    }
    void half() {

        Value = Value / 2;
    }

    int getValue() {

        return Value;
    }

    Memento *createMemento() {

        return new Memento(Value);

    }
    void reinstateMemento(Memento *mem) {

        Value = mem->state;

    }
};

class Command
{
  public:
    typedef void(Number:: *Action)();

    Command(Number *Receiver, Action action){

        receiver = Receiver;
        _action = action;

    }
    virtual void execute() {

        mementoList[numCommands] = receiver->createMemento();
        commandList[numCommands] = this;

        if (numCommands > lastPoint)
          lastPoint = numCommands;
        numCommands++;
        (receiver->*_action)();

    }
    static void undo()
    {
        if (numCommands == 0)
        {
            cout << "Лол, еще не одной операции не сделано" << endl;
            return ;
        }
           commandList[numCommands - 1]->receiver->reinstateMemento
          (mementoList[numCommands - 1]);
        numCommands--;
    }
    void static redo()
    {
        if (numCommands > lastPoint)
        {
            cout << "Вы уже в конце" << endl;
            return ;
        }
  (commandList[numCommands]->receiver->*(commandList[numCommands]->_action))();
        numCommands++;
    }
  protected:
    Number *receiver;
    Action _action;
    static Command *commandList[20];
    static Memento *mementoList[20];
    static int numCommands;
    static int lastPoint;
};

Command *Command::commandList[];
Memento *Command::mementoList[];
int Command::numCommands = 0;
int Command::lastPoint = 0;

int main()
{
  int i;
  cout << "Integer: ";
  cin >> i;
  Number *object = new Number(i);

  Command *commands[3];
  commands[1] = new Command(object, &Number::Double);
  commands[2] = new Command(object, &Number::half);

  cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
  cin >> i;

  while (i)
  {
    if (i == 3)
      Command::undo();
    else if (i == 4)
      Command::redo();
    else
      commands[i]->execute();
    cout << "   " << object->getValue() << endl;
    cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
    cin >> i;
  }
}