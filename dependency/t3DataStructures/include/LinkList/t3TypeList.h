#ifndef T3_TYPELIST_H
#define T3_TYPELIST_H

template <class T, class U>
class t3TypeList
{
public:
    typedef T head;
    typedef U next;
};

#endif
