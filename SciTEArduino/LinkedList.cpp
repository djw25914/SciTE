/* I'm using templates here, for a good explanation for why I'm doing it the way I am see:
   "Data Structures and Algorithm Analysis in C++", 4E, Mark Allen Weiss, Appendix A (The CS dept should have it)*/

/* Instance variables in use: (for reference)
    T *_items;
    uint8_t _size;
    uint8_t _count;
*/

template <typename T>
void MyArray<T>::_grow() {
/* Grow the array if it's too small to add more values.
 * It's normally good practice to double the array size,
 * but the Arduino has limited resources and the number of
 * items should be fairly limited, so adding 5 should be a
 * good compromise and won't impact performance in any way.
 */
    uint8_t oldSize = _size;
    uint8_t newSize = _size+5;
    
    T *newArray = new T[newSize];

    for (uint8_t cnt = 0; cnt < _count; ++cnt)
    {

    }
}

template <typename T>
void MyArray<T>::MyArray() {

}

template <typename T>
const &T MyArray<T>::at(uint8_t position) {

}

template <typename T>
void MyArray<T>::add(T &item) {

}

template <typename T>
void MyArray<T>::remove(uint8_t position) {

}

template <typename T>
void MyArray<T>::remove(T &item) {

}

// Explicit instantiations
template class MyArray<ScheduleItem>;
template class MyArray<OverrideItem>;