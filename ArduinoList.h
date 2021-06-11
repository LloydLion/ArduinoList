template<class T>
struct ListNode
{
public:
  ListNode();
  T object;
  ListNode<T>* next;
};

template<class T>
class List
{
public:
  // class Iterator
  // {
  // public:
  //   Iterator(List<T>* list);
  //   bool moveNext();
  //   T& current();
  //   void reset();
  // private:
  //   List<T>* list;
  //   ListNode<T>* currentEl;
  // };

  List();
  ~List();
  void add(const T& obj);
  T& get(int index);
  int getCount();
  void insertAfter(const T& object, int index);
  void remove(int index);
  void set(int index, const T& object);
  void swap(int index1, int index2);
  //const Iterator& getIterator();
  int minVal(int (*selector)(const T&));
  int maxVal(int (*selector)(const T&));
  int find(void* (*selector)(const T&), void* search);
  ListNode<T>* getNode(int index);

private:
  ListNode<T>* first;
  int count;
};




//-------------------------------------------




// template<class T>
// bool List<T>::Iterator::moveNext()
// {
//   Serial.println("-movit");
//   currentEl = currentEl->next;
//   if(currentEl == nullptr) return false;
//   else return true;
// }

// template<class T>
// T& List<T>::Iterator::current()
// {
//   Serial.println("-getcurit");
//   Serial.println((int)(currentEl->object));
//   return currentEl->object;
// }

// template<class T>
// void List<T>::Iterator::reset()
// {
//   Serial.println("-resit");
//   currentEl = list->first;
// }

// template<class T>
// List<T>::Iterator::Iterator(List<T>* list)
// {
//   Serial.println("-crit");
//   Serial.println("-crit");
//   this->list = list;
//   Serial.println("-crit");
//   reset();
//   Serial.println("-crit");
// }

template<class T>
ListNode<T>::ListNode()
{
  next = nullptr;
}

template<class T>
List<T>::List()
{
  first = nullptr;
  count = 0;
}

template<class T>
List<T>::~List()
{
  ListNode<T>* toDel = first;
  ListNode<T>* toDel2;
  while(toDel!=nullptr)
  {
    toDel2 = toDel;
    toDel = toDel->next;
    delete toDel2;
  }
}

// template<class T>
// const typename List<T>::Iterator& List<T>::getIterator()
// {
//   Serial.println("-getit");
//   return Iterator(this);
// }

template<class T>
T& List<T>::get(int index)
{
  return getNode(index)->object;
}

template<class T>
int List<T>::find(void* (*selector)(const T&), void* search)
{
  auto node = first;
  int index = 0;

  do
  {
    auto ft = selector(node->object);
    if(ft == search) return index;

    index++;
  }
  while((node = node->next) != nullptr);

  return -1;
}

template<class T>
void List<T>::add(const T& object)
{
  if(count == 0)
  {
    first = new ListNode<T>();
    first->object = object;
  }
  else
  {
    ListNode<T>* last;
    last = getNode(count-1)->next = new ListNode<T>();
    last->object = object;
  }

  count++;
}

template<class T>
int List<T>::getCount()
{
  return count;
}

template<class T>
void List<T>::insertAfter(const T& object, int index)
{
  auto node = new ListNode<T>();
  node->object = object;

  if(index == -1)
  {
    node->next = first;
    first = node;
  }
  else
  {
    auto tnode = getNode(index);
    auto next = tnode->next;
    tnode->next = node;
    node->next= next;
  }

  count++;
}

template<class T>
int List<T>::minVal(int (*selector)(const T&))
{
  int currentMin = 0x7FFF;
  int currentIndex = -1;

  ListNode<T>* node = first;
  for(int i = 0; i < count; i++)
  {
    int val = selector(node->object);
    if(currentMin >= val)
    {
      currentMin = val;
      currentIndex = i;
    }
    node = node->next;
  }
  return currentIndex;
}

template<class T>
int List<T>::maxVal(int (*selector)(const T&))
{
  int currentMax = 0x8000;
  int currentIndex = -1;

  ListNode<T>* node = first;
  for(int i = 0; i < count; i++)
  {
    int val = selector(node->object);
    if(currentMax <= val)
    {
      currentMax = val;
      currentIndex = i;
    }
    node = node->next;
  }
  return currentIndex;
}

template<class T>
void List<T>::remove(int index)
{
  if(index == 0)
  {
    auto save = first->next;
    delete first;
    first = save;
  }
  else
  {
    auto node = getNode(index-1);
    auto target = node->next->next;
    delete node->next;
    node->next = target;
  }

  count--;
}

template<class T>
void List<T>::set(int index, const T& object)
{
  getNode(index)->object = object;
}

template<class T>
void List<T>::swap(int index1, int index2)
{
  auto el = get(index1);
  set(index1, get(index2));
  set(index2, el);
}

template<class T>
ListNode<T>* List<T>::getNode(int index)
{
  if(index >= count || index < 0) return nullptr;

  ListNode<T>* res = first;
  while(index-- != 0)
  {
    res = res->next;
  }

  return res;
}