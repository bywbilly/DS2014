/** @file */
#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"
#include "cstring"

/**
 * The ArrayList is just like vector in C++.
 * You should know that "capacity" here doesn't mean how many elements are now in this list, where it means
 * the length of the array of your internal implemention
 *
 * The iterator iterates in the order of the elements being loaded into this list
 */
template <class T>
class ArrayList
{
public:
    friend class Iterator;
    class Iterator
    {
    public:
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext()
        {
            return cursor+1<base.amount;
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T &next()
        {
            if(!hasNext())throw ElementNotExist();
            valid=1;
            return base.elements[++cursor];
        }

        /**
         * TODO Removes from the underlying collection the last element
         * returned by the iterator
         * The behavior of an iterator is unspecified if the underlying
         * collection is modified while the iteration is in progress in
         * any way other than by calling this method.
         * @throw ElementNotExist
         */
        void remove()
        {
            if(!valid)throw ElementNotExist();
            base.removeIndex(cursor);
            valid=0;
            --cursor;
        }

        /**
         * TODO Constructor
         */
        Iterator(ArrayList<T> &c):base(c)
        {
            cursor=-1;
            valid=0;
        }
    private:
        /**
         * @param cursor point to the position
         * @param valid iterator is invalid when executes remove()
         */
        ArrayList<T> &base;
        int cursor;
        bool valid;
    };

    /**
     * TODO Constructs an empty array list.
     */
    ArrayList()
    {
        capacity=8;
        amount=0;
        elements=new T[capacity];
    }

    /**
     * TODO Destructor
     */
    ~ArrayList()
    {
        delete [] elements;
    }

    /**
     * TODO Assignment operator
     */
    ArrayList& operator=(const ArrayList& x)
    {
        if(&x!=this)
        {
            amount=x.amount;
            capacity=x.capacity;
            delete [] elements;
            elements=new T[capacity];
            for(int i=0;i<amount;++i)elements[i]=x.get(i);
        }
        return *this;
    }

    /**
     * TODO Copy-constructor
     */
    ArrayList(const ArrayList& x)
    {
        amount=x.amount;
        capacity=x.capacity;
        elements=new T[capacity];
        for(int i=0;i<amount;++i)elements[i]=x.get(i);
    }

    /**
     * TODO Appends the specified element to the end of this list.
     * Always returns true.
     */
    bool add(const T& e)
    {
        if(amount==capacity)enlarge();
        elements[amount++]=e;
        return 1;
    }

    /**
     * TODO Inserts the specified element to the specified position in this list.
     * The range of index parameter is [0, size], where index=0 means inserting to the head,
     * and index=size means appending to the end.
     * @throw IndexOutOfBound
     */
    void add(int index, const T& element)
    {
        if(index<0 || index>amount)throw IndexOutOfBound();
        if(amount==capacity)enlarge();
        for(int i=amount++;i>index;--i)elements[i]=elements[i-1];
        elements[index]=element;
    }

    /**
     * TODO Removes all of the elements from this list.
     */
    void clear()
    {
        amount=0;
    }

    /**
     * TODO Returns true if this list contains the specified element.
     */
    bool contains(const T& e) const
    {
        for(int i=0;i<amount;++i)
            if(elements[i]==e)return 1;
        return 0;
    }

    /**
     * TODO Returns a const reference to the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    const T& get(int index) const
    {
        if(index<0 || index>=amount)throw IndexOutOfBound();
        return elements[index];
    }

    /**
     * TODO Returns true if this list contains no elements.
     */
    bool isEmpty() const
    {
        return (amount==0);
    }

    /**
     * TODO Removes the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void removeIndex(int index)
    {
        if(index<0 || index>=amount)throw IndexOutOfBound();
        for(int i=index;i<amount-1;++i)elements[i]=elements[i+1];
        --amount;
    }

    /**
     * TODO Removes the first occurrence of the specified element from this list, if it is present.
     * Returns true if it was present in the list, otherwise false.
     */
    bool remove(const T &e)
    {
        for(int i=0;i<amount;++i)
            if(e==elements[i])
            {
                removeIndex(i);
                return 1;
            }
        return 0;
    }

    /**
     * TODO Replaces the element at the specified position in this list with the specified element.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void set(int index, const T &element)
    {
        if(index<0 || index>=amount)throw IndexOutOfBound();
        elements[index]=element;
    }

    /**
     * TODO Returns the number of elements in this list.
     */
    int size() const
    {
        return amount;
    }

    /**
     * TODO Returns an iterator over the elements in this list.
     */
    Iterator iterator()
    {
        return Iterator(*this);
    }
private:

    /**
     * @param capacity the size of the array.
     * @param amount the number of the elements of the array.
     * @param elements the array which restore the elements.
     */
    int capacity,amount;
    T *elements;

    /**
     * TODO double the capacity of the array.
     */
    void enlarge()
    {
        T *temp=new T[capacity*2];
        for(int i=0;i<amount;++i)temp[i]=elements[i];
        capacity*=2;
        delete [] elements;
        elements=temp;
    }
};

#endif
