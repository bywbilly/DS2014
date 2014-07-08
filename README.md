DS2014
======

update：PriorityQueue的实现 存在问题。HashMap的hash无法处理hashcode为-2147483648的情况

fc.py:比较2个文件差异，定位于第一个出错的行

-----------------------------------------

目前已通过所有测试。包括Ted的测试，tby的weak测试，上一届的测试，chendy构造的测试，我自己构造的Deque和PriorityQueue的测试

我自己构造的测试考虑了在PriorityQueque中通过iterator进行remove后保证仍然是一个堆结构

-----------------------------------------

内存情况在ubuntu14.10下使用valgrind检测，测试结果为内安全存

test.cpp为tby的测试,out为对应的答案文件

Ted的测试见https://github.com/Determinant/datastructure_final_spring_2013

上一届测试可以在课程中心找到

mytest为我自己的测试，mytest.ans为对应的答案文件,请使用我提供的fc.py进行比较，否则可能会因为制表符宽度不同导致文件差异。

需要chendy构造的测试请pm我（或者直接向chendi索取）

-----------------------------------------

email:judaplus@gmail.com

