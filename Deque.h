/** @file */
#ifndef __DEQUE_H
#define __DEQUE_H

#include "ElementNotExist.h"
#include "IndexOutOfBound.h"
#include "cstring"

/**
 * An deque is a linear collection that supports element insertion and removal at both ends.
 * The name deque is short for "double ended queue" and is usually pronounced "deck".
 * Remember: all functions but "contains" and "clear" should be finished in O(1) time.
 *
 * You need to implement both iterators in proper sequential order and ones in reverse sequential order.
 */
template <class T>
class Deque
{
public:
    class Iterator
    {
    public:
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext()
        {
            if(base.capacity==0)return 0;
            if(!order)
            {
                return ((cursor+1)%base.capacity!=base.last);
            }else
            {
                return ((cursor-1+base.capacity)%base.capacity!=base.first);
            }
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T &next()
        {
            if(!hasNext())throw ElementNotExist();
            valid=1;
            if(!order)
            {
                cursor=(cursor+1)%base.capacity;
            }else
            {
                cursor=(cursor-1+base.capacity)%base.capacity;
            }
            return base.elements[cursor];
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
            valid=0;
            int t1=cursor,t2;
            if(!order)
            {
                while(1)
                {
                    t2=(t1+1)%base.capacity;
                    if(t2==base.last)break;
                    base.elements[t1]=base.elements[t2];
                    t1=t2;
                }
                cursor=(cursor-1+base.capacity)%base.capacity;
                base.last=(base.last-1+base.capacity)%base.capacity;
            }else
            {
                while(1)
                {
                    t2=(t1-1+base.capacity)%base.capacity;
                    if(t2==base.first)break;
                    base.elements[t1]=base.elements[t2];
                    t1=t2;
                }
                cursor=(cursor+1)%base.capacity;
                base.last=(base.first+1)%base.capacity;
            }
        }

        /**
         * TODO constructor
         */
        Iterator(Deque<T> &c, int cur,bool _order):base(c),cursor(cur),order(_order)
        {
            valid=0;
        }
    private:
        /**
         * @param cursor point to the position
         * @param valid iterator is invalid when executes remove()
         * @param order check whether the iterator is an iterator over the elements in this deque in proper sequence
         */
        Deque<T> &base;
        int cursor;
        bool order,valid;
    };

    /**
     * TODO Constructs an empty deque.
     */
    Deque()
    {
        capacity=8;
        first=0;last=1;
        elements=new T[capacity];
    }

    /**
     * TODO Destructor
     */
    ~Deque()
    {
        delete [] elements;
    }

    /**
     * TODO Assignment operator
     */
    Deque& operator=(const Deque<T>& x)
    {
        if(&x!=this)
        {
            int temp=x.size();
            capacity=temp*2;
            delete [] elements;
            elements=new T[capacity];
            for(int i=0;i<temp;++i)elements[i+1]=x.get(i);
            first=0;last=temp+1;
        }
        return *this;
    }

    /**
     * TODO Copy-constructor
     */
    Deque(const Deque<T>& x)
    {
            int temp=x.size();
            capacity=temp*2;
            elements=new T[capacity];
            for(int i=0;i<temp;++i)elements[i+1]=x.get(i);
            first=0;last=temp+1;
    }

	/**
	 * TODO Inserts the specified element at the front of this deque.
	 */
	void addFirst(const T& e)
	{
        if((first-1+capacity)%capacity==last)enlarge();
        elements[first]=e;
        first=(first-1+capacity)%capacity;
	}

	/**
	 * TODO Inserts the specified element at the end of this deque.
	 */
	void addLast(const T& e)
	{
	    if(first==(last+1)%capacity)enlarge();
	    elements[last]=e;
	    last=(last+1)%capacity;
	}

	/**
	 * TODO Returns true if this deque contains the specified element.
	 */
	bool contains(const T& e) const
	{
	    if(first<last)
        {
            for(int i=first+1;i<last;++i)
                if(elements[i]==e)return 1;
        }else
        {
            for(int i=first+1;i<capacity;++i)
                if(elements[i]==e)return 1;
            for(int i=0;i<last;++i)
                if(elements[i]==e)return 1;
        }
        return 0;
	}

	/**
	 * TODO Removes all of the elements from this deque.
	 */
    void clear()
    {
        first=0;
        last=1;
    }

	 /**
	  * TODO Returns true if this deque contains no elements.
	  */
	bool isEmpty() const
	{
	    return ((first+1)%capacity==last);
	}

	/**
	 * TODO Retrieves, but does not remove, the first element of this deque.
	 * @throw ElementNotExist
	 */
    const T& getFirst()
    {
        if(isEmpty())throw ElementNotExist();
        return elements[(first+1)%capacity];
    }

	 /**
	  * TODO Retrieves, but does not remove, the last element of this deque.
	  * @throw ElementNotExist
	  */
    const T& getLast()
    {
        if(isEmpty())throw ElementNotExist();
        return elements[(last-1+capacity)%capacity];
    }

	 /**
	  * TODO Removes the first element of this deque.
	  * @throw ElementNotExist
	  */
	void removeFirst()
	{
	    if(isEmpty())throw ElementNotExist();
	    first=(first+1)%capacity;
	}

	/**
	 * TODO Removes the last element of this deque.
	 * @throw ElementNotExist
	 */
	void removeLast()
	{
	    if(isEmpty())throw ElementNotExist();
	    last=(last-1+capacity)%capacity;
	}

	/**
	 * TODO Returns a const reference to the element at the specified position in this deque.
	 * The index is zero-based, with range [0, size).
	 * @throw IndexOutOfBound
	 */
	const T& get(int index) const
	{
	    if(index<0 || index>=size())throw IndexOutOfBound();
	    return elements[(first+index+1)%capacity];
	}

	/**
	 * TODO Replaces the element at the specified position in this deque with the specified element.
	 * The index is zero-based, with range [0, size).
	 * @throw IndexOutOfBound
	 */
	void set(int index, const T& e)
	{
	    if(index<0 || index>=size())throw IndexOutOfBound();
	    elements[(first+index+1)%capacity]=e;
	}

	/**
	 * TODO Returns the number of elements in this deque.
	 */
    int size() const
    {
        if(first<last)return last-first-1;else return last+capacity-first-1;
    }

	 /**
	  * TODO Returns an iterator over the elements in this deque in proper sequence.
	  */
    Iterator iterator()
    {
        return Iterator(*this,first,0);
    }

	 /**
	  * TODO Returns an iterator over the elements in this deque in reverse sequential order.
	  */
    Iterator descendingIterator()
    {
        return Iterator(*this,last,1);
    }
private:
    /**
     * @param capacity the size of the array
     * @param first the left cursor
     * @param last the right cursor
     * @param elements the array which restore the elements
     */
    int capacity,first,last;
    T *elements;

    /**
     * TODO double the space of the array
     */
    void enlarge()
    {
        T *temp=new T[capacity*2];
        int a=0;
        if(first<last)
        {
            for(int i=first+1;i<last;++i)temp[++a]=elements[i];
        }else
        {
            for(int i=first+1;i<capacity;++i)temp[++a]=elements[i];
            for(int i=0;i<last;++i)temp[++a]=elements[i];
        }
        first=0;
        last=a+1;
        capacity*=2;
        delete [] elements;
        elements=temp;
    }
};

#endif
