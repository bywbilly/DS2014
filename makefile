head = ArrayList.h LinkedList.h HashMap.h TreeMap.h Deque.h PriorityQueue.h ElementNotExist.h IndexOutOfBound.h

test : test.cpp $(head)
	g++ -std=c++11 $< -o test -g -Wall

clean:
	rm  test
