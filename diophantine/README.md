# diophantine

A program automatically solving diophantine equations of the form a ^ x + b = c ^ y for its positive integer solutions (x, y), where a, b and c are given positive integers satisfying a >= 2 and c >= 2.

Due to the limitations of the int type range, this program can only ensure successful solving of equations within the range of 2 <= a <= 70, b <= 30 and 2 <= c <= 70. However, there are many equations outside this range that can also be solved successfully.

Implemented in pure SysY.

## Usage

```sh
./diophantine
```

You need to input a, b and c first.

## Examples

1. $5^x+3=2^y,\ x,y\in\mathbb{N}^*\Rightarrow(x,y)=(1, 3)\ or\ (x,y)=(3, 7)$

Please input a (a should be a positive integer >= 2):  
5  
Please input b (b should be a positive integer):  
3  
Please input c (c should be a positive integer >= 2):  
2  
For positive integers x, y satisfying 5 ^ x + 3 = 2 ^ y,  
if y >= 8, 5 ^ x = 253 (mod 256).  
So x = 35 (mod 64),  
which implies x = 35, 99, 163, 227 (mod 256).  
Therefore, 5 ^ x = 14, 224, 243, 33 (mod 257).  
So 2 ^ y = 17, 227, 246, 36 (mod 257), but this is impossible.  
Therefore, y < 8.  
Further examination shows that (x, y) = (1, 3), (3, 7).  

2. $3^x+10=13^y,\ x,y\in\mathbb{N}^*\Rightarrow(x,y)=(1, 1)\ or\ (x,y)=(7, 3)$

Please input a (a should be a positive integer >= 2):  
3  
Please input b (b should be a positive integer):  
10  
Please input c (c should be a positive integer >= 2):  
13  
For positive integers x, y satisfying 3 ^ x + 10 = 13 ^ y,  
if x >= 8, 13 ^ y = 10 (mod 6561).  
So y = 1461 (mod 2187),  
which implies y = 1461, 3648, 5835, 8022 (mod 8748).  
Therefore, 13 ^ y = 11616, 6486, 5881, 11011 (mod 17497).  
So 3 ^ x = 11606, 6476, 5871, 11001 (mod 17497), but this is impossible.  
Therefore, x < 8.  
Further examination shows that (x, y) = (1, 1), (7, 3).

3. $2^x+89=91^y,\ x,y\in\mathbb{N}^*\Rightarrow(x,y)=(1, 1)\ or\ (x,y)=(13, 2)$

Please input a (a should be a positive integer >= 2):  
2  
Please input b (b should be a positive integer):  
89  
Please input c (c should be a positive integer >= 2):  
91  
For positive integers x, y satisfying 2 ^ x + 89 = 91 ^ y,  
if y >= 3, 2 ^ x = 254 (mod 343).  
So x = 76 (mod 147),  
which implies x = 76, 223, 370, 517, 664, 811, 958, 1105, 1252 (mod 1323).  
Therefore, 2 ^ x = 1994, 852, 1811, 957, 1447, 1513, 2343, 348, 1970 (mod 2647).  
So 91 ^ y = 2083, 941, 1900, 1046, 1536, 1602, 2432, 437, 2059 (mod 2647), but this is impossible.  
Therefore, y < 3.  
Further examination shows that (x, y) = (1, 1), (13, 2).

4. $x,y\in\mathbb{N}^*\Rightarrow 101^x+3\neq103^y$

Please input a (a should be a positive integer >= 2):  
101  
Please input b (b should be a positive integer):  
3  
Please input c (c should be a positive integer >= 2):  
103  
For positive integers x, y satisfying 101 ^ x + 3 = 103 ^ y,  
if x >= 1, 103 ^ y = 3 (mod 101).  
So y = 69 (mod 100),  
which implies y = 19 (mod 25).  
Therefore, 103 ^ y = 583 (mod 701).  
So 101 ^ x = 580 (mod 701), but this is impossible.  
Therefore, x < 1.  
So 101 ^ x + 3 = 103 ^ y is impossible.

## References

* [2^x-5^y=3 Has No Positive Integer Solution Satisfying x>7](https://www.zhihu.com/question/643199800/answer/3390621395).
* [Positive Integer Solutions of the Equation 3^x+10=13^y](https://zhuanlan.zhihu.com/p/684271210).
* [A Universal Semi-Automaton for Solving a Class of Diophantine Equations](https://zhuanlan.zhihu.com/p/685073628).
