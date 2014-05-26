#include "LinkedList.h"
#include "ArrayList.h"
#include "HashMap.h"
#include "TreeMap.h"
#include "Deque.h"
#include "PriorityQueue.h"
#include "ElementNotExist.h"
#include "IndexOutOfBound.h"
#include "queue"
#include "set"
#include "iostream"
#include "algorithm"
using namespace std;
typedef pair<int, int> PII;

static int RandNum=31;
int Rand()
{
	return RandNum=(RandNum*11+239)%65537;
}

template <class T>
void printDeque(Deque<T> q)
{
    typename Deque<T>::Iterator itr1 = q.iterator();
    while (itr1.hasNext())
    {
        cout << itr1.next() << "\t";
    }
    cout << endl;
    typename Deque<T>::Iterator itr2 = q.descendingIterator();
    while (itr2.hasNext())
    {
        cout << itr2.next() << "\t";
    }
    cout << endl;
    cout << "End print" << endl;
}

void testDeque()
{
    Deque<int> d1;
    for(int i=0;i<=20;i++)
        d1.addFirst(i);
    printDeque(d1);
    for(int i=1;i<=20;i++)
        d1.removeLast();
    d1.set(0,0);
    Deque<int> d2(d1);
    cout<<d1.isEmpty()<<endl;
    d1.clear();
    cout<<d1.isEmpty()<<endl;
    printDeque(d2);
    for(int i=0;i<=20;i++)
        d1.addLast(i);
    printDeque(d1);
    for(int i=0;i<=20;i++)
        d1.removeFirst();
    cout<<d1.isEmpty()<<endl;
    for(int i=1;i<=100000;i++)
        d2.addLast(i);
    for(int i=0;i<=100000;i++)
        d2.addFirst(i);
    for(int i=0;i<d2.size();i++)
        if(d2.get(i)!=d2.get(d2.size()-i-1))
        {
            cout<<"WA"<<endl;
            return;
        }
    for(int i=0;i<d2.size();i++)d2.set(i,-1);
    if(d2.getFirst()!=d2.getLast())
    {
        cout<<"WA"<<endl;
        return;
    }
    if(!d2.contains(-1))
    {
        cout<<"WA"<<endl;
        return;
    }
    d2.clear();
    if(d2.contains(-1))
    {
        cout<<"WA"<<endl;
        return;
    }
    d2.addFirst(101);
    d2.addLast(202);
    d1=d2;
    printDeque(d1);
    cout<<"done Deque test1"<<endl;
}

void testDeque2()
{
    puts("Begin Deque test 2");
    int count,num=0,t1,t2;
    Deque<int> d;
    vector<int> v;
    for(int i=1;i<=100;i++)
    {
        d.addFirst(i);
        d.addLast(-i);
    }
    Deque<int> d2(d);
    auto it1=d.iterator();
    auto it2=d2.descendingIterator();
    if(d.size()!=d2.size())
    {
        puts("copy WA");
        return;
    }
    count=0;
    for(;;)
    {
        if(it1.hasNext()!=it2.hasNext())
        {
            puts("WA iterator or descendingiterator");
            return;
        }
        if(!it1.hasNext())break;
        t1=it1.next();
        t2=it2.next();
        if(t1!=-t2)
        {
            puts("WA  add");
            return;
        }
        if(Rand()%2)
        {
            count++;
            continue;
        }
        it1.remove();
        it2.remove();
        try
        {
            it1.remove();
        }catch(ElementNotExist e)
        {num++;}
        try
        {
            it2.remove();
        }catch(ElementNotExist e)
        {num++;}
    }
    if(d.size()!=d2.size() || d.size()!=count)
    {
        puts("WA iterator remove");
        return;
    }
    try
    {
        it1.next();
    }catch(ElementNotExist e)
    {num++;}
    try
    {
        it2.next();
    }catch(ElementNotExist e)
    {num++;}
    d.clear();
    d2.clear();
    if(d.size() || d2.size() || !d.isEmpty() || !d2.isEmpty())
    {
        puts("WA clear");
        return;
    }
    try{
        d.getFirst();
    }catch(ElementNotExist e)
    {num++;}
    try{
        d2.getLast();
    }catch(ElementNotExist e)
    {num++;}
    try{
        d.removeFirst();
    }catch(ElementNotExist e)
    {num++;}
    try{
        d2.removeLast();
    }catch(ElementNotExist e)
    {num++;}
    d.addFirst(1);
    try
    {
        d.get(-1);
    }catch(IndexOutOfBound e)
    {num++;}
    try
    {
        d.get(d.size());
    }catch(IndexOutOfBound e)
    {num++;}
    try
    {
        d.set(-1,-1);
    }catch(IndexOutOfBound e)
    {num++;}
    try
    {
        d.set(d.size(),-1);
    }catch(IndexOutOfBound e)
    {num++;}
    cout<<num<<endl;
    puts("Done Deque test 2");
}

template <class V, class C>
void printHeap(PriorityQueue<V, C> q)
{
    typename PriorityQueue<V, C>::Iterator itr = q.iterator();
    vector<V> s;
    while (itr.hasNext())
    {
        s.push_back(itr.next());
    }
    sort(s.begin(), s.end());
    for (int i = 0; i < s.size(); ++i)
    {
        cout << s[i] << '\t';
    }
    cout << endl;
    cout << "End print" << endl;
}

void testHeap()
{
    ArrayList<int> x;
    PriorityQueue<int> y;
    priority_queue<int> s;
    for(int i=1;i<=20;i++)
    {
        int temp=i/2;
        x.add(temp);
        s.push(temp);
        y.push(temp);
    }
    PriorityQueue<int> z(x);
    PriorityQueue<int> t(z);
    for(int i=1;i<20;i++)
    {
        if(y.front()==z.front())
        {
            cout<<y.front()<<'\t';
        }else
        {
            puts("WA");
            return;
        }
        y.pop();
        z.pop();
    }
    cout<<endl;
    if(y.front()!=s.top() || z.front()!=s.top())
    {
        puts("WA");
        return;
    }
    cout<<y.size()<<endl;
    cout<<z.size()<<endl;
    cout<<t.size()<<endl;
    y.pop();
    z=t;
    z.clear();
    cout<<y.empty()<<endl;
    cout<<z.empty()<<endl;
    try
    {
        auto it=y.iterator();
        it.remove();
    }catch (ElementNotExist e)
    {
        cout<<"iterator remove OK"<<endl;
    }
    try
    {
        z.front();
    }catch (ElementNotExist e)
    {
        cout<<"front OK"<<endl;
    }
    try
    {
        z.pop();
    }catch (ElementNotExist e)
    {
        cout<<"pop OK"<<endl;
    }
    z=t;
    try
    {
        auto it=z.iterator();
        it.next();
        it.remove();
        it.remove();
    }catch (ElementNotExist e)
    {
        cout<<"iterator remove OK"<<endl;
    }
    y=t;
    z=t;
    printHeap(y);
    printHeap(z);
    auto it=y.iterator();
    while(it.hasNext())
    {
        it.next();
        it.remove();
    }
    try
    {
        it.next();
    }catch (ElementNotExist e)
    {
        cout<<"next OK"<<endl;
    }
    cout<<y.empty()<<endl;
    cout<<"Done heap test1"<<endl;
}

void testHeap2()
{
    multiset<int> s,s1;
    PriorityQueue<int> p;
    int temp;
    for(int i=0;i<=1000;i++)
    {
        temp=Rand();
        s.insert(temp);
        s1.insert(temp);
        p.push(temp);
    }
    for(auto it=p.iterator();it.hasNext();)
    {
        temp=it.next();
        s1.erase(s1.find(temp));
        if(Rand()%4==0)
        {
            s.erase(s.find(temp));
            it.remove();
        }
        if(*(s.begin())!=p.front())
        {
            puts("WA");
            return;
        }
    }
    cout<<s1.size()<<endl;
    cout<<s.size()<<endl;
    cout<<p.size()<<endl;
    puts("Done heap test 2");
}

int main()
{
    testDeque();
    puts("-----------------------------------------");
    testDeque2();
    puts("-----------------------------------------");
    testHeap();
    puts("-----------------------------------------");
    testHeap2();
    puts("-----------------------------------------");
}
