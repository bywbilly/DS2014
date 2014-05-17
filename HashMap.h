/** @file */

#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "ElementNotExist.h"

/**
 * HashMap is a map implemented by hashing. Also, the 'capacity' here means the
 * number of buckets in your internal implemention, not the current number of the
 * elements.
 *
 * Template argument H are used to specify the hash function.
 * H should be a class with a static function named ``hashCode'',
 * which takes a parameter of type K and returns a value of type int.
 * For example, the following class
 * @code
 *      class Hashint {
 *      public:
 *          static int hashCode(int obj) {
 *              return obj;
 *          }
 *      };
 * @endcode
 * specifies an hash function for integers. Then we can define:
 * @code
 *      HashMap<int, int, Hashint> hash;
 * @endcode
 *
 * Hash function passed to this class should observe the following rule: if two keys
 * are equal (which means key1 == key2), then the hash code of them should be the
 * same. However, it is not generally required that the hash function should work in
 * the other direction: if the hash code of two keys are equal, the two keys could be
 * different.
 *
 * Note that the correctness of HashMap should not rely on the choice of hash function.
 * This is to say that, even the given hash function always returns the same hash code
 * for all keys (thus causing a serious collision), methods of HashMap should still
 * function correctly, though the performance will be poor in this case.
 *
 * The order of iteration could be arbitary in HashMap. But it should be guaranteed
 * that each (key, value) pair be iterated exactly once.
 */
template <class K, class V, class H>
class HashMap
{
public:
    class Entry
    {
        K key;
        V value;
    public:
        Entry(){}

        Entry(K k, V v)
        {
            key = k;
            value = v;
        }

        K getKey() const
        {
            return key;
        }

        V getValue() const
        {
            return value;
        }

        V &getConstValue()
        {
            return value;
        }

        void modifyValue(V _value)
        {
            value=_value;
        }
    };

    class Iterator
    {
    public:
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext()
        {
            if( (cursor->next!=0))return 1;
            int start;
            if(!first && cursor->next==0) start=base.getHashCode(cursor->elem.getKey())+1;else start=0;
            for(int i=start;i<base.capacity;++i)
            {
                if(base.elements[i].next)return 1;
            }
            return 0;
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const Entry &next()
        {
            if( (cursor->next!=0))
            {
                cursor=cursor->next;
                first=0;
                return cursor->elem;
            }
            int start;
            if(!first && cursor->next==0) start=base.getHashCode(cursor->elem.getKey())+1;else start=0;
            if(first)first=!first;
            for(int i=start;i<base.capacity;++i)
            {
                if(base.elements[i].next)
                {
                    cursor=base.elements[i].next;
                    return cursor->elem;
                }
            }
            throw ElementNotExist();
        }

        /**
         * TODO Constructor
         */
        Iterator(const HashMap<K,V,H> &c):base(c),cursor(&(c.elements[0])),first(1)
        {
        }
    private:
        const HashMap<K,V,H> &base;
        struct HashMap<K,V,H>::Node *cursor;
        bool first;
    };

    /**
     * TODO Constructs an empty hash map.
     */
    HashMap()
    {
        capacity=11;
        amount=0;
        elements=new Node[capacity];
    }

    /**
     * TODO Destructor
     */
    ~HashMap()
    {
        clear();
        delete [] elements;
    }

    /**
     * TODO Assignment operator
     */
    HashMap &operator=(const HashMap &x)
    {
        if(&x!=this)
        {
            amount=x.size();
            capacity=amount*2+1;
            elements=new Node[capacity];
            auto it=x.iterator();
            while(it.hasNext())
            {
                auto temp=it.next();
                put(temp.getKey(),temp.getValue());
            }
        }
        return *this;
    }

    /**
     * TODO Copy-constructor
     */
    HashMap(const HashMap &x)
    {
        *this=x;
    }

    /**
     * TODO Returns an iterator over the elements in this map.
     */
    Iterator iterator() const
    {
        return Iterator(*this);
    }

    /**
     * TODO Removes all of the mappings from this map.
     */
    void clear()
    {
        Node *a;
        for(int i=0;i<capacity;++i)
        {
            while(elements[i].next)
            {
                a=elements[i].next;
                elements[i].next=elements[i].next->next;
                delete a;
            }
        }
        amount=0;
    }

    /**
     * TODO Returns true if this map contains a mapping for the specified key.
     */
    bool containsKey(const K &key) const
    {
        int i=getHashCode(key);
        auto it=elements[i].next;
        while(it)
        {
            if(it->elem.getKey()==key)return 1;
            it=it->next;
        }
        return 0;
    }

    /**
     * TODO Returns true if this map maps one or more keys to the specified value.
     */
    bool containsValue(const V &value) const
    {
        for(int i=0;i<capacity;++i)
        {
            auto a=elements[i].next;
            while(a)
            {
                if(a->elem.getValue()==value)return 1;
                a=a->next;
            }
        }
        return 0;
    }

    /**
     * TODO Returns a const reference to the value to which the specified key is mapped.
     * If the key is not present in this map, this function should throw ElementNotExist exception.
     * @throw ElementNotExist
     */
    const V &get(const K &key) const
    {
        int i;
        i=getHashCode(key);
        auto it=elements[i].next;
        while(it)
        {
            if(it->elem.getKey()==key)return it->elem.getConstValue();
            it=it->next;
        }
        throw ElementNotExist();
    }

    /**
     * TODO Returns true if this map contains no key-value mappings.
     */
    bool isEmpty() const
    {
        return (amount==0);
    }

    /**
     * TODO Associates the specified value with the specified key in this map.
     */
    void put(const K &key, const V &value)
    {
        int i=getHashCode(key);
        if(elements[i].next==0)
        {
            elements[i].next=new Node(Entry(key,value),0);
        }else
        {
            Node *a;
            for(a=&elements[i];a->next;a=a->next)
            {
                if(a->next->elem.getKey()==key)
                {
                    a->next->elem.modifyValue(value);
                    return;
                }
            }
            a->next=new Node(Entry(key,value),0);
        }
        amount++;
        if(amount>capacity)enlarge();
    }

    /**
     * TODO Removes the mapping for the specified key from this map if present.
     * If there is no mapping for the specified key, throws ElementNotExist exception.
     * @throw ElementNotExist
     */
    void remove(const K &key)
    {
        int i=getHashCode(key);
        if(elements[i].next->elem.getKey()==key)
        {
            amount--;
            auto a=elements[i].next;
            elements[i].next=elements[i].next->next;
            delete a;
            return;
        }else
        {
            auto it=elements[i].next;
            for(;it->next->elem.getKey()!=key;it=it->next);
            auto a=it->next;
            it->next=it->next->next;
            delete a;
            amount--;
            return;
        }
        throw ElementNotExist();
    }

    /**
     * TODO Returns the number of key-value mappings in this map.
     */
    int size() const
    {
        return amount;
    }
private:
    /**
     * @param capacity the size of the array.
     * @param amount the number of the elements of the array.
     * @param elements the array which restore the elements.
     */
    int capacity,amount;
    struct Node
    {
        Entry elem;
        Node *next;
        Node(Entry _elem=Entry(),Node *_next=0):elem(_elem),next(_next){}
    };
    Node *elements;

     int ABS(int x) const
     {
         if(x<0)return -x;else return x;
     }

    /**
     * TODO calculate the corresponding hash code
     */
    int getHashCode(const K &key) const
    {
        K _key=key;
        return ABS(H::hashCode(_key)) % capacity;
    }

    /**
     * TODO double the size and recalculate the key-value
     */
    void enlarge()
    {
        Node *temp=elements,*a;
        int t_capacity=capacity;
        capacity=capacity*2+1;
        amount=0;
        elements=new Node[capacity];
        for(int i=0;i<t_capacity;++i)
        {
            for(a=temp[i].next;a;a=a->next)put(a->elem.getKey(),a->elem.getValue());
        }
        for(int i=0;i<t_capacity;++i)
        {
            while(temp[i].next)
            {
                a=temp[i].next;
                temp[i].next=temp[i].next->next;
                delete a;
            }
        }
        delete [] temp;
    }
};

#endif
