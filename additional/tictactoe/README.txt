Tic-tac-toe is a popular board game. It is composed of 3 rows and 3
columns (9 cells). Each cell can beﬁlled by one of three symbols: (1)
empty, (2) X, or (3) O. Two players alternateﬁlling the cells. Once a
cell isﬁlled by X or O, this cell cannot beﬁlled again. Theﬁrst player
can be either X or O. This problem assumes that X isﬁrst. Figure 1
(a)-(d) show several examples of the game during plays. The game ends
when either one of the two players wins, or it not possible toﬁnd a
winner. A player wins if this player’s three symbols appear the same
row, the same column, or a diagonal. Figure 1 (e)-(g) show three
examples of winning. Figure 1 (h) shows an example of draw. This is
draw because the next player is X; neither X or O can form a line.

Figure 1: (a) - (d) Examples of the Tic-Tac-Toe game. (e)-(f) X wins. (g) O wins. (h) Draw.

. means empty

(a)

..X
...
...

(b)

X..
.O.
...

(c)

X.X
.O.
...

(d)

..X
.O.
...

(e)

XXX
.O.
.O.

(f)

XOX
OX.
.OX

(g)

XOX
.O.
.OX

(h)

XOX
OXX
O.O


The game board may be rotated or mirrored. Figure 2 (a)-(d) are
equivalent. Fig- ure 2 (a) becomes Figure 2 (b) after 90◦ rotation
clockwise. Similarly, Figure 2 (c) can be obtained from Figure 2 (b)
after another 90◦ rotation clockwise. Figure 2 (e)(f) are rotation
equivalent. Figure 2 (g) cannot be produced by rotating Figure 2
(f). Instead, Figure 2 (g) can be produced taking vertical mirror of
Figure 2. Usually, a Tic-Tac-Toe game stops when a winner is
determined or draw is unavoidable.  In other words, the games shown in
Figure 1 (e)-(g) should stop even though some cells are still empty.

Figure 2 (a) - (d) Rotation equivalent. (e)(f) Rotation
equivalent. (f)(g) Mirror equivalent.

(a) 

X..
...
...

(b)

..X
...
...

(c)

...
...
..X

(d)

...
...
X..

(e)

XX.
.O.
...

(f)

..X
.OX
...

(g)

...
.OX
..X


Question 1

This first question asks the number of possible diﬀerent Tic-Tac-Toe
boards. Igore rotation and mirror equivalents. Thus, Figure 2 (a)-(d)
are counted as four diﬀerent boards. Figure 2 (f)-(g) are counted as
two diﬀerent boards. Also, the players continue playing until all nine
cells areﬁlled even though the winner has been decided, or draw is
certain.

This question can be translated into the following: The board has 9
cells and n cells are ﬁlled by either X or O (obviously, n is between
1 and 9). How many ways can these 9 cells beﬁlled?  Suppose among then
ﬁlled cells,a are X and b are O. Apparently,a + b = n. Since X plays
ﬁrst, the following condition must hold:


(1) when n is even: a = b
(2) when n is odd: a = b + 1


If n cells are ﬁlled, there are C(9, n) ways to select these n
cells. Here, C(p, q) is combination: selecting q from p distinct
options. Then, among the n cells, we choose a for X and b for O; there
are C(n, a) ways. Thus, there are C(9, n) x C(n, a) ways to ﬁll n of
the 9 cells. The following table shows the numbers of boards
asnchanges from 1 to 9.

n   a   b   C(9, n)   C(n, a) number of boards
1   1   0        9          1                9
2   1   1       36          2               72
3   2   1       84          3              252
4   2   2      126          6              756
5   3   2      126         10             1260
6   3   3       84         20             1680
7   4   3       36         35             1260
8   4   4        9         70              630
9   5   4        1        126              126

Total	                                  6045


Question 2

Write a C program to generate all possible boards. For simplicity,
each board is printed in only one line: the three cells of the top row
is followed by the three cells of the middle row, then the last
row. Use-to show unﬁlled cells. For example, Figure 1 (c) will be
printed as

X-X-O----

Figure 1 (h) will be printed as

XOXOXXO-O

Question 3

Stop when the winner has already been decided or draw is
unavoidable. For example, Figure 1 (e)-(f) should have no additional
cells to fill.

Question 4

Remove rotation or mirror equivalent.  For example, Figure 2 (a)-(d)
should appear only once.


