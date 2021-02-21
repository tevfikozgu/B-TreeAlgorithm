# B-TreeAlgorithm
 B-Tree Algorithm is implemented for both insert and delete operations.

## Insert Operation

For this operation, **insert.cpp** will be used. To execute this program, initially these steps must be done:

* First download all files(except **delete.cpp**).
* In the next step, compile main.cpp by g++ -Wall -Werror insert.cpp -o insert
* Run file as ./insert

This program will expect you to enter some inputs. Sample input set is given below.

| :memo: INPUT SET           |
|:---------------------------|
| 21
3
z
56 34 G
71 6 M
68 0 P
123 -666 T
999 4 X
41 33 A 
-66 8 B
748 54 C
99 978 D
400 23 E
98 66 J
0 43 K
66 12 N
45 1 O 
11 -34 Q
67 -36 R 
40 7 S 
85 3 U 
8 2 V
62 9 Y
9 5 Z |

In this input set, 21 is the number of nodes in the tree. 3 is the degree of the B-Tree and finally z is the key that will be used for inserting an element as an key.

When this input set is typed, tree will be printed in prefix order. Result is given below.

| :boom: Output of the tree  |
|:---------------------------|
|(748,54,C)(56,34,G)(68,0,P)(40 ,7,S)(8,2,V)
(41,33,A)(-66,8,B)
(99,978,D)(400,23,E)
(98,66,J)(0,43,K)(71,6,M)(66,12,N)(45,1,O)
(11,-34,Q)(67,-36,R)
(123,-666,T)(85,3,U)
(999,4,X)(62,9,Y)(9,5,Z)|

## Delete Operation

Delete operation was a little bit confusing. Initially you need to compile program. Steps are given below.

* First download all files(except **insert.cpp**).
* In the next step, compile main.cpp by g++ -Wall -Werror delete.cpp -o insert
* Run file as ./delete

Like **insert.cpp** this program also expect to enter inputs. Sample input set is given below.

| :memo: INPUT SET           |
|:---------------------------|
| 21
3
z
56 34 G
71 6 M
68 0 P
123 -666 T
999 4 X
41 33 A 
-66 8 B
748 54 C
99 978 D
400 23 E
98 66 J
0 43 K
66 12 N
45 1 O 
11 -34 Q
67 -36 R 
40 7 S 
85 3 U 
8 2 V
62 9 Y
9 5 Z 
G|

Only difference is the last item that was typed. In this set last item which is *G* is the key that will be deleted. Output of this set is given below.

| :boom: Output of the tree  |
|:---------------------------|
|(748,54,C)(98,66,J)(68,0,P)(40,7,S)(8,2,V)
(41,33,A)(-66,8,B)
(99,978,D)(400,23,E)
(0,43,K)(71,6,M)(66,12,N)(45,1,O)
(11,-34,Q)(67,-36,R)
(123,-666,T)(85,3,U)
(999,4,X)(62,9,Y)(9,5,Z)|