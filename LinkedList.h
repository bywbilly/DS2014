/** @file */
#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

/**
 * A linked list.
 *
 * The iterator iterates in the order of the elements being loaded into this list.
 */
template <class T>
class LinkedList
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
            if(valid)return (cursor->next!=NULL);else return (cursor!=NULL);
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T &next()
        {
            if(!hasNext())throw ElementNotExist();
            if(!valid)
            {
                valid=1;
                return cursor->value;
            }else
            {
                cursor=cursor->next;
                return cursor->value;
            }
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
            if(cursor->pred)cursor->pred->next=cursor->next;else base.head=cursor->next;
            if(cursor->next)cursor->next->pred=cursor->pred;else base.tail=cursor->pred;
            auto *a=cursor;
            cursor=cursor->next;
            delete a;
            base.amount--;
            if(!base.amount)base.head=base.tail=0;
        }

        /**
         * TODO constructor
         */
        Iterator(LinkedList<T> &c):base(c)
        {
            cursor=c.head;
            valid=0;
        }

        ~Iterator()
        {
            cursor=0;
        }
    private:
        /**
         * @param cursor point to the position
         * @param valid iterator is invalid when executes remove()
         */
        struct LinkedList<T>::Node *cursor;
        LinkedList<T> &base;
        bool valid;
    };

    class ConstIterator
    {
    public:
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext()
        {
            if(valid)return (cursor->next!=NULL);else return (cursor!=NULL);
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T &next()
        {
            if(!hasNext())throw ElementNotExist();
            if(!valid)
            {
                valid=1;
                return cursor->value;
            }else
            {
                cursor=cursor->next;
                return cursor->value;
            }
        }

        /**
         * TODO constructor
         */
        ConstIterator(const LinkedList<T> &c):base(c)
        {
            cursor=c.head;
            valid=0;
        }
    private:
        /**
         * @param cursor point to the position
         * @param valid iterator is invalid when executes remove()
         */
        struct LinkedList<T>::Node *cursor;
        const LinkedList<T> &base;
        bool valid;
    };
    /**
     * TODO Constructs an empty linked list
     */
    LinkedList()
    {
        head=tail=NULL;
        amount=0;
    }

    /**
     * TODO Copy constructor
     */
    LinkedList(const LinkedList<T> &c)
    {
        *this=c;
    }

    /**
     * TODO Assignment operator
     */
    LinkedList<T>& operator=(const LinkedList<T> &c)
    {
        if(&c!=this)
        {
            if(c.isEmpty())
            {
                head=tail=NULL;
                amount=0;
            }else
            {
                auto i=c.iterator();
                Node *j=0,*a;
                head=tail=0;
                if(i.hasNext())j=head=new Node(i.next(),0,0);
                while(1)
                {
                    if(i.hasNext())
                    {
                        a=new Node(i.next(),j,0);
                        j->next=a;
                        j=a;
                    }else break;
                }
                tail=j;
                amount=c.size();
            }
        }
        return *this;
    }

    /**
     * TODO Desturctor
     */
    ~LinkedList()
    {
        clear();
    }

    /**
     * TODO Appends the specified element to the end of this list.
     * Always returns true.
     */
    bool add(const T& e)
    {
        if(isEmpty())
        {
            head=tail=new Node(e,0,0);
            amount++;
            return 1;
        }
        Node *a=new Node(e,tail,0);
        tail->next=a;
        tail=a;
        amount++;
        return 1;
    }

    /**
     * TODO Inserts the specified element to the beginning of this list.
     */
    void addFirst(const T& elem)
    {
        if(isEmpty())
        {
            head=tail=new Node(elem,0,0);
            amount++;
        }
        Node *a=new Node(elem,0,head);
        head->pred=a;
        head=a;
        amount++;
    }

    /**
     * TODO Insert the specified element to the end of this list.
     * Equivalent to add.
     */
    void addLast(const T &elem)
    {
        add(elem);
    }

    /**
     * TODO Inserts the specified element to the specified position in this list.
     * The range of index parameter is [0, size], where index=0 means inserting to the head,
     * and index=size means appending to the end.
     * @throw IndexOutOfBound
     */
    void add(int index, const T& element)
    {
        if(index<0 || index>=amount)throw IndexOutOfBound();
        if(index==0)
        {
            addFirst(element);
            return;
        }
        if(index==amount)
        {
            addLast(element);
            return;
        }
        Node *a=head;
        for(int i=0;i<index-1;++i)a=a->next;
        Node *j=new Node(element,a,a->next);
        a->next->pred=j;
        a->next=j;
        amount++;
    }

    /**
     * TODO Removes all of the elements from this list.
     */
    void clear()
    {
        Node *i,*j;
        for(i=head;i;)
        {
            j=i->next;
            delete i;
            i=j;
        }
        head=tail=0;
        amount=0;
    }

    /**
     * TODO Returns true if this list contains the specified element.
     */
    bool contains(const T& e) const
    {
        for(auto i=head;i;i=i->next)
            if(i->value==e)return 1;
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
        Node *a=head;
        for(int i=0;i<index;++i)a=a->next;
        return a->value;
    }

    /**
     * TODO Returns a const reference to the first element.
     * @throw ElementNotExist
     */
    const T& getFirst() const
    {
        if(isEmpty())throw ElementNotExist();
        return head->value;
    }

    /**
     * TODO Returns a const reference to the last element.
     * @throw ElementNotExist
     */
    const T& getLast() const
    {
        if(isEmpty())throw ElementNotExist();
        return tail->value;
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
        Node *a=head;
        for(int i=0;i<index;++i)a=a->next;
        if(a->pred)a->pred->next=a->next;else head=a->next;
        if(a->next)a->next->pred=a->pred;else tail=a->pred;
        delete a;
        amount--;
        if(!amount)head=tail=0;
    }

    /**
     * TODO Removes the first occurrence of the specified element from this list, if it is present.
     * Returns true if it was present in the list, otherwise false.
     */
    bool remove(const T &e)
    {
        Node *a;
        for(a=head;a;a=a->next)
            if(a->value==e)break;
        if(!a)return 0;
        if(a->pred)a->pred->next=a->next;else head=a->next;
        if(a->next)a->next->pred=a->pred;else tail=a->pred;
        delete a;
        amount--;
        if(!amount)head=tail=0;
        return 1;
    }

    /**
     * TODO Removes the first element from this list.
     * @throw ElementNotExist
     */
    void removeFirst()
    {
        if(isEmpty())throw ElementNotExist();
        amount--;
        Node *a=head->next;
        if(a)a->pred=0;
        delete head;
        head=a;
        if(!amount)head=tail=0;
    }

    /**
     * TODO Removes the last element from this list.
     * @throw ElementNotExist
     */
    void removeLast()
    {
        if(isEmpty())throw ElementNotExist();
        amount--;
        Node *a=tail->pred;
        if(a)a->next=0;
        delete tail;
        tail=a;
        if(!amount)head=tail=0;
    }

    /**
     * TODO Replaces the element at the specified position in this list with the specified element.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void set(int index, const T &element)
    {
        if(index<0 || index>=amount)throw IndexOutOfBound();
        Node *a=head;
        for(int i=0;i<index;++i)a=a->next;
        a->value=element;
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

    /**
     * TODO Returns an iterator over the elements in this list.
     */
    ConstIterator iterator() const
    {
        return ConstIterator(*this);
    }
private:
    /**
     * @param head the node pointing to the first one
     * @param tail the node pointing to the last one
     * @param amount the size of the linked list
     */
    struct Node
    {
        T value;
        Node *pred,*next;
        Node(T _value,Node *_pred=0,Node *_next=0):value(_value),pred(_pred),next(_next){}
    };
    Node *head,*tail;
    int amount;
};

#endif
