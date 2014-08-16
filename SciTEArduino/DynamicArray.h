/* A barebones dynamic array class template */

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

template<class T>
class DynamicArray {
public:                  // Constructor, Destructor, Other public methods
    DynamicArray()
    {
        _init();
    }

    ~DynamicArray()
    {
        delete[] _data;
    }

    uint8_t size() const
    {
        return _size;
    }

    uint8_t count() const
    {
        return _count;
    }

    bool empty() const
    {
        if (_count == 0)
            return true;
        return false;
    }

    void add(T & t)
    {
        if (_count+1 == _size)
            _grow();
        _data[count] = t;
    }

    void remove(T & t)
    {
        uint8_t foundAt = 0;
        for(uint8_t i = 0; i < _count; ++i)
        {
            if (_data[i] == t)
            {
                foundAt = i;
                for (uint8_t j = i; j < _count; ++j)
                {
                    delete _data[j];  // Delete the one we were asked to
                    if (j+1 != _count)// Slide things over
                    {
                        _data[j] = _data[j+1];
                    }
                    else // All have been copied over by one, chop off the tail
                    {
                        delete _data[j];
                    }
                }
            }
        }
    }

    T * at(uint8_t n)
    {
        return _data[n];)
    }


private:
    uint8_t _count;
    uint8_t _size;
    T * _data;
    uint8_t _INCREMENT = 5;

private:
    void _init()
    {
        _count = 0;
        _size = _INCREMENT;
        _data = new T[_size];
    }
    void _grow()
    {
        _size = _size + _INCREMENT;
        T * newData = new T[ _size ];
        for (uint8_t i = 0; i < _count; ++i)
        {
            newData[i] = _data[i];
        }
        delete[] _data;
        _data = newData;
};

/* Explicit instantiations for the types we'll be using with DynamicArray*/

#endif