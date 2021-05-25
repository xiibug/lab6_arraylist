
#ifndef TARRAYLIST
#define TARRAYLIST

#include <iostream>
#include<fstream>

using namespace std;

template<class T>
class TArrayListIter;

template <class T>
class TArrayList
{
protected:
    T* data;
    int* links;
    int size;
    int count;
    int root;
public:
    TArrayList(int _size = 1);
    TArrayList(TArrayList<T>& _v);
    ~TArrayList();

    TArrayList<T>& operator =(TArrayList<T>& _v);

    bool IsEmpty(void) const;
    bool IsFull(void) const;

    void InsFirst(T d);
    void InsLast(T d);
    void Ins(TArrayListIter<T>& e, T d);

    TArrayListIter<T> begin();
    TArrayListIter<T> end();

    void DelFirst();
    void DelLast();
    void Del(TArrayListIter<T>& e);

    T GetFirst();
    T GetLast();

    template <class T1>
    friend ostream& operator<< (ostream& ostr, const TArrayList<T1>& A);
    template <class T1>
    friend istream& operator >> (istream& istr, TArrayList<T1>& A);

    template<class T1>
    friend class TArrayListIter;

    TArrayList<T> DivisionByK(int k);
    void LoadToFile();

    int GetCount();
};

template<class T>
class TArrayListIter
{
protected:
    TArrayList<T>& list;
    int index;
public:
    TArrayListIter(TArrayList<T>& _list, int _index = -2);
    TArrayListIter(TArrayListIter<T>& _v);
    ~TArrayListIter();

    bool IsGoNext();
    void GoNext();

    bool operator==(const TArrayListIter<T>& _v);
    bool operator!=(const TArrayListIter<T>& _v);
    TArrayListIter<T>& operator++();
    TArrayListIter<T>& operator =(const TArrayListIter<T>& _list);

    T& operator * (int);
    T& operator * ();


    T GetData();
    T GetIndex();
};

template <class T1>
ostream& operator<< (ostream& ostr, const TArrayList<T1>& A) {

    int i = A.root;
    while (A.links[i] != -1)
    {
        ostr << A.data[i] << " ";
        i = A.links[i];
    }
    ostr << A.data[i] << " ";
    return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TArrayList<T1>& A) {
    int count;
    istr >> count;
    for (int i = 0; i < count; i++)
    {
        T1 d;
        istr >> d;
        A.InsLast(d);
    }
    return istr;
}

template<class T>
inline void TArrayList<T>::LoadToFile()
{
    ofstream fout("ArrList.txt");
    if (fout.is_open())
    {
        for (int i = 0; i < this->size; i++)
        {
            fout << this->data[i] << " ";
        }
    }
    else
        throw new exception;
}


template<class T>
inline TArrayList<T>::TArrayList(int _size)
{
    if (_size <= 0)
        throw new exception;

    size = _size;
    count = 0;

    data = new T[size];
    links = new int[size];

    for (int i = 0; i < size; i++)
    {
        links[i] = -2;
    }

    root = -1;
}

template <class T>
TArrayList<T>::TArrayList(TArrayList<T>& _v)
{
    count = _v.count;
    size = _v.size;
    root = _v.root;

    data = new T[size];
    links = new int[size];

    for (int i = 0; i < size; i++)
    {
        links[i] = _v.links[i];
        data[i] = _v.data[i];
    }
}

template <class T>
TArrayList<T>::~TArrayList()
{
    if (this->data != 0)
    {
        delete[] data;
        delete[] links;
        data = 0;
        links = 0;
        count = 0;
        size = 0;
        root = -1;
    }
}

template <class T>
TArrayList<T>& TArrayList<T>::operator =(TArrayList<T>& _v)
{
    if (this == &_v)
        return *this;

    if (size != _v.size)
    {
        delete[] data;
        delete[] links;

        data = new T[_v.size];
        links = new int[_v.size];
    }

    count = _v.count;
    size = _v.size;
    root = _v.root;

    for (int i = 0; i < size; i++)
    {
        links[i] = _v.links[i];
        data[i] = _v.data[i];
    }

    return *this;
}



template<class T>
inline bool TArrayList<T>::IsEmpty(void) const
{
    return count == 0;
}

template<class T>
inline bool TArrayList<T>::IsFull(void) const
{
    return count >= size;
}

template<class T>
inline void TArrayList<T>::InsFirst(T d)
{
    if (this->IsFull())
        throw new exception;

    int i = 0;
    for (i = 0; i < size; i++)
        if (links[i] == -2)
            break;

    data[i] = d;
    links[i] = root;
    root = i;
    count++;
}

template<class T>
inline void TArrayList<T>::InsLast(T d)
{
    if (this->IsFull())
        throw new exception;

    if (this->IsEmpty())
    {
        root = 0;
        data[0] = d;
        links[0] = -1;
    }
    else
    {
        int i = 0;
        for (i = 0; i < size; i++)
            if (links[i] == -2)
                break;

        int end = root;
        while (links[end] != -1)
            end = links[end];

        data[i] = d;
        links[i] = -1;
        links[end] = i;
    }
    count++;
}

template<class T>
inline void TArrayList<T>::Ins(TArrayListIter<T>& e, T d)
{
    if (this->IsFull())
        throw new exception;
    if (this->IsEmpty())
    {
        root = 0;
        data[0] = d;
        links[0] = -1;
    }
    else
    {
        int k = e.GetIndex();
        if (links[k] == -2)
        {
            int end = root;
            while (links[end] != -1)
                end = links[end];
            data[k] = d;
            links[k] = -1;
            links[end] = k;
        }
    }
    count++;
}

template<class T>
inline TArrayListIter<T> TArrayList<T>::begin()
{
    return TArrayListIter<T>(*this, root);
}

template<class T>
inline TArrayListIter<T> TArrayList<T>::end()
{
    return TArrayListIter<T>(*this, -1);
}

template<class T>
inline void TArrayList<T>::DelFirst()
{
    if (this->IsEmpty())
        throw new exception;

    int i = root;
    root = links[root];
    links[i] = -2;

    count--;
}

template<class T>
inline void TArrayList<T>::DelLast()
{
    if (this->IsEmpty())
        throw new exception;

    if (links[root] == -1)
    {
        links[root] = -2;
        root = -1;
    }
    else
    {
        int prev = root;
        int end = links[root];

        while (links[end] != -1)
        {
            prev = end;
            end = links[end];
        }

        links[prev] = -1;
        links[end] = -2;

    }
    count--;
}

template<class T>
inline void TArrayList<T>::Del(TArrayListIter<T>& e)
{
    if (this->IsEmpty())
        throw new exception;
    if (links[root] == -1)
    {
        links[root] = -2;
        root = -1;
    }
    else
    {
        int pEnd = e.GetIndex();
        int end = links[root];
        while (links[end] != -1)
        {
            pEnd = end;
            end = links[end];
        }
        links[pEnd] = -1;
        links[end] = -2;
    }
    count--;
}

template<class T>
inline T TArrayList<T>::GetFirst()
{
    if (this->IsEmpty())
        throw new exception;
    return data[root];
}

template<class T>
inline T TArrayList<T>::GetLast()
{
    if (this->IsEmpty())
        throw new exception;
    int end = root;
    while (links[end] != -1)
        end = links[end];
    return data[end];
}

template<class T>
inline TArrayList<T> TArrayList<T>::DivisionByK(int k)
{
    TArrayList<T> s(this->size);
    for (int i = 0; i < this->size; i++)
        if (this->data[i] % k == 0)
            s.InsLast(this->data[i]);
    return s;
}

template <class T>
int TArrayList<T>::GetCount()
{
    return count;
}

#endif 

template<class T>
inline TArrayListIter<T>::TArrayListIter(TArrayList<T>& _list, int _index) : list(_list), index(_index)
{
    this->index = _index;
}

template<class T>
inline TArrayListIter<T>::TArrayListIter(TArrayListIter<T>& _v) : list(_v.list), index(_v.index)
{
}

template<class T>
inline TArrayListIter<T>::~TArrayListIter()
{
    index = -2;
}

template<class T>
inline bool TArrayListIter<T>::IsGoNext()
{
    return (index >= 0);
}

template<class T>
inline void TArrayListIter<T>::GoNext()
{
    if (IsGoNext())
        index = list.links[index];
}

template<class T>
inline bool TArrayListIter<T>::operator==(const TArrayListIter<T>& _v)
{
    return (index == _v.index);
}

template<class T>
inline bool TArrayListIter<T>::operator!=(const TArrayListIter<T>& _v)
{
    return !this->operator==(_v);
}

template<class T>
inline TArrayListIter<T>& TArrayListIter<T>::operator++()
{
    GoNext();
    return *this;
}

template<class T>
inline TArrayListIter<T>& TArrayListIter<T>::operator=(const TArrayListIter<T>& _v)
{
    list = _v.list;
    index = _v.index;
}

template<class T>
T& TArrayListIter<T>::operator*(int)
{
    return list.data[index];
}

template<class T>
T& TArrayListIter<T>::operator*()
{
    return list.data[index];
}

template<class T>
inline T TArrayListIter<T>::GetData()
{
    if (index < 0)
        throw new exception;
    return list.data[index];
}

template<class T>
inline T TArrayListIter<T>::GetIndex()
{
    if (index < 0)
        throw new exception;
    return index;
}