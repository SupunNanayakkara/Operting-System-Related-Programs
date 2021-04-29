0 movv sp 90
1 movv a 120
2 movv b 180
3 call 20
4 add a b
5 out acc
6 halt


20 push a
21 push b
22 push acc
23 movv a 25
24 movv b 125
25 add a b
26 out acc
27 pop acc
28 pop b
29 pop a
30 ret


