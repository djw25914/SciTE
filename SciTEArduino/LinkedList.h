#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template<class T>
class LinkedList {

private:                 // Node class
    struct Node
    {
        T data;
        Node *prev;
        Node *next;

        Node( const T & d = T{}, Node * p = nullptr, Node *n = nullptr)
        {
            data = d;
            prev = p;
            next = n;
        }
    };
public:                  // Constructor, Destructor, Other public methods
    LinkedList()
    {
        init();
    }

    ~LinkedList()
    {
        clear();
        delete head;
        delete tail;
    }

    int size() const
    {
        return _count;
    }

    bool empty() const
    {
        if (_count == 0)
            return true;
        return false;
    }

    void clear()
    {
        while (!empty())
            popFront();
    }

    void add(T & t)
    {
        oldLast = _tail->prev;
        newLast = new Node(t,oldLast, _tail);
        oldLast->next = newLast;
        _tail->prev = newLast;
    }

    void remove(T & t)
    {
        Node node = _head;
        while (node->next != nullptr)
        {
            if (node->data == t)
            {
                node->next->prev = node->prev;
                node->prev->next = node->next;
                delete node
                break;
            }
            node = node->next;
        }
        renumber();
    }

    void remove(int idNumber)
    {
        Node node = _head;
        while ( node->next != nullptr )
        {
            if ( node->data->id() == idNumber )
            {
                node->next->prev = node->prev;
                node->prev->next = node->next;
                delete node;
                break;
            }
        }
    }

    void rewind()
    { //reset the [makeshift, but stupid simple excuse for an] iterator to the beginning of the list.
        _current = head->next;
    }

    bool end()
    {
        if ( _current == _tail )
            return true;
        return false;
    }

    void next()
    {
        _current = _current->next;
    }

    void previous()
    {
        _current = _current->prev;
    }

    T * current()
    {
        return _current->data;
    }

    void _renumber()
    {
        num = 0;
        Node *cur = head->next;
        while(cur != _tail)
        {
            cur->data->setNumber(num++);
            cur = cur->next();
        }
        T::_setNextItemNumber = n;
    }

private:                 // Class vars, Object vars, and private methods
    uint8_t _count;
    Node *_head;
    Node *_tail;
    Node *_current;

    init()
    {
        _count = 0;
        _nextId = 0;
        _head = new Node;
        _tail = new Node;
        _head->next = tail;
        _tail->prev = head;
        _current = _head->next;
    }
};

template class LinkedList<ScheduleItem>;
template class LinkedList<OverrideItem>;
#endif