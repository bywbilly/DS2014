/** @file */
#ifndef __PRIORITYQUEUE_H
#define __PRIORITYQUEUE_H

#include "ArrayList.h"
#include "ElementNotExist.h"
#include "iostream"
#include <algorithm>

/**
 * This is a priority queue based on a priority priority queue. The
 * elements of the priority queue are ordered according to their
 * natual ordering (operator<), or by a Comparator provided as the
 * second template parameter.
 * The head of this queue is the least element with respect to the
 * specified ordering (different from C++ STL).
 * The iterator does not return the elements in any particular order.
 * But it is required that the iterator will eventually return every
 * element in this queue (even if removals are performed).
 */

/*----------------------------------------------------------------------*/
/**
 * Default Comparator with respect to natural order (operator<).
 */
template <class V>
class Less
{
public:
    bool operator()(const V& a, const V& b) { return a < b; }
};

/**
 * To use this priority queue, users need to either use the
 * default Comparator or provide their own Comparator of this
 * kind.
 * The Comparator should be a class with a public function
 * public: bool operator()(const V&, const V&);
 * overriding the "()" operator.
 */

/*----------------------------------------------------------------------*/

template <class V, class C = Less<V> >
class PriorityQueue
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
            return cursor-1>0;
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const V &next()
        {
            if(!hasNext())throw ElementNotExist();
            valid=1;
            cursor--;
            return base->elements[base->point2[cursor]];
        }

		/**
		 * TODO Removes from the underlying collection the last element
		 * returned by the iterator.
		 * The behavior of an iterator is unspecified if the underlying
		 * collection is modified while the iteration is in progress in
		 * any way other than by calling this method.
		 * @throw ElementNotExist
		 */
		void remove()
		{
		    if(!valid)throw ElementNotExist();
		    int p1=base->point2[cursor],p2=base->amount;
            std::swap(base->elements[p1],base->elements[p2]);
            std::swap(base->point2[base->point1[p1]],base->point2[base->point1[p2]]);
            std::swap(base->point1[p1],base->point1[p2]);
            base->point1[base->point2[base->amount]]=cursor;
            base->point2[cursor]=base->point2[base->amount];
            base->amount--;
            base->up(p1);
            base->down(p1);
            valid=0;
		}

		/**
         * TODO Constructor
         */
        Iterator(PriorityQueue<V,C> *c=0):base(c)
        {
            cursor=base->amount+1;
            valid=0;
        }
    private:
        /**
         * @param cursor point to the position
         * @param valid iterator is invalid when executes remove()
         */
        PriorityQueue<V,C> *base;
        int cursor;
        bool valid;
    };

    /**
     * TODO Constructs an empty priority queue.
     */
    PriorityQueue()
    {
        capacity=8;
        amount=0;
        elements=new V[capacity];
        point1=new int[capacity];
        point2=new int[capacity];
    }

    /**
     * TODO Destructor
     */
    ~PriorityQueue()
    {
        delete [] elements;
        delete [] point1;
        delete [] point2;
    }

    /**
     * TODO Assignment operator
     */
    PriorityQueue &operator=(const PriorityQueue &x)
    {
        if(&x!=this)
        {
            amount=x.amount;
            capacity=x.capacity;
            delete [] elements;
            delete [] point1;
            delete [] point2;
            elements=new V[capacity];
            point1=new int[capacity];
            point2=new int[capacity];
            for(int i=1;i<=amount;++i)elements[i]=x.elements[i];
            for(int i=1;i<=amount;++i)point1[i]=point2[i]=i;
        }
        return *this;
    }

    /**
     * TODO Copy-constructor
     */
    PriorityQueue(const PriorityQueue &x)
    {
            amount=x.amount;
            capacity=x.capacity;
            elements=new V[capacity];
            point1=new int[capacity];
            point2=new int[capacity];
            for(int i=1;i<=amount;++i)elements[i]=x.elements[i];
            for(int i=1;i<=amount;++i)point1[i]=point2[i]=i;
    }

	/**
	 * TODO Initializer_list-constructor
	 * Constructs a priority queue over the elements in this Array List.
     * Requires to finish in O(n) time.
	 */
	PriorityQueue(const ArrayList<V> &x)
	{
	    amount=x.size();
        capacity=amount*2;
        elements=new V[capacity];
        point1=new int[capacity];
        point2=new int[capacity];
        for(int i=0;i<amount;++i)elements[i+1]=x.get(i);
        for(int i=1;i<=amount;++i)point1[i]=point2[i]=i;
        for(int i=amount/2;i>0;--i)down(i);
	}

    /**
     * TODO Returns an iterator over the elements in this priority queue.
     */
    Iterator iterator()
    {
        return Iterator(this);
    }

    /**
     * TODO Removes all of the elements from this priority queue.
     */
    void clear()
    {
        amount=0;
    }

    /**
     * TODO Returns a const reference to the front of the priority queue.
     * If there are no elements, this function should throw ElementNotExist exception.
     * @throw ElementNotExist
     */
    const V &front() const
    {
        if(empty())throw ElementNotExist();
        return elements[1];
    }

    /**
     * TODO Returns true if this PriorityQueue contains no elements.
     */
    bool empty() const
    {
        return (amount==0);
    }

    /**
     * TODO Add an element to the priority queue.
     */
    void push(const V &value)
    {
        if(amount+2>=capacity)enlarge();
        elements[++amount]=value;
        point1[amount]=amount;
        point2[amount]=amount;
        up(amount);
    }

    /**
     * TODO Removes the top element of this priority queue if present.
     * If there is no element, throws ElementNotExist exception.
     * @throw ElementNotExist
     */
    void pop()
    {
        if(empty())throw ElementNotExist();
        elements[1]=elements[amount];
        point1[point2[amount]]=point1[amount];
        point2[point1[amount]]=point2[amount];
        --amount;
        down(1);
    }

    /**
     * TODO Returns the number of key-value mappings in this map.
     */
    int size() const
    {
        return amount;
    }
/*
    void show(bool yes=0) const
    {
        for(int i=1;i<=amount;i++)std::cout<<elements[i]<<" ";
        std::cout<<std::endl;
        if(yes)
        {
            for(int i=1;i<=amount;i++)std::cout<<point1[i]<<" ";
            std::cout<<std::endl;
            for(int i=1;i<=amount;i++)std::cout<<point2[i]<<" ";
            std::cout<<std::endl;
        }
    }*/
private:
    /**
     * @param capacity the size of the array.
     * @param amount the number of the elements of the array.
     * @param elements the array which restore the elements.
     */
    int capacity,amount;
    V *elements;
    int *point1,*point2;
    C cmp;

    /**
     * TODO double the capacity of the array.
     */
    void enlarge()
    {
        V *temp=new V[capacity*2];
        int *p1=new int[capacity*2],*p2=new int[capacity*2];
        for(int i=1;i<=amount;i++)
        {
            temp[i]=elements[i];
            p1[i]=point1[i];
            p2[i]=point2[i];
        }
        capacity*=2;
        delete [] elements;
        delete [] point1;
        delete [] point2;
        elements=temp;
        point1=p1;
        point2=p2;
    }

    /**
     * TODO shift up the element whose position is index
     */
    void up(int index)
    {
        for(int w=index;w!=1;w/=2)
            if(cmp(elements[w],elements[w/2]))
               {
                   std::swap(elements[w],elements[w/2]);
                   std::swap(point2[point1[w]],point2[point1[w/2]]);
                   std::swap(point1[w],point1[w/2]);
               }else break;
    }

    /**
     * TODO shift down the element whose position is index
     */
    void down(int index)
    {
        int j;
        for(int w=index;w*2<=amount;w=j)
        {
            j=w*2;
            if(j+1<=amount && cmp(elements[j+1],elements[j]))j++;
            if(cmp(elements[j],elements[w]))
            {
                std::swap(elements[j],elements[w]);
                std::swap(point2[point1[w]],point2[point1[j]]);
                std::swap(point1[w],point1[j]);
            }else break;
        }
    }
};

#endif
