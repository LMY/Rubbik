# 0 The Cube

Observe a Solved 3x3 cube. White face down, red face front -> green is right, orange is back, blue is left, yellow is up.

## 0.1 Description: edges, corners

a 3x3x3 rubik rube contains 8 corners and 12 edges. The 8 corners can be *disposed* in 8! ways, each having one of 3 states. The 12 edges can be *disposed* in 12! ways, each having one of 2 possible states.
Total possible states are thus 8!3^8 12! 2^12. Log2 of this number is 69.

From solved state, let's name the corners and the positions of the corners:
* down-left-front = 0
* down-right-front = 1
* down-left-back = 2
* down-right-back = 3
* up-left-front = 4
* up-right-front = 5
* up-left-back = 6
* up-right-back = 7


## 0.2 Corners, 2x2x2 as part of any NxNxN

A 2x2x2 cybe gas 8 corners and any NxNxN cube has 8 corner. Thus, any size-cube contains a 2x2x2 cube that represent the state of the corners.

From solved state, let's name the corners and the positions of the corners:
* down-left = 0
* down-front = 1
* down-right = 2
* down-back = 3
* mid-left-front = 4
* mid-right-front = 5
* mid-left-back = 6
* mid-right-back = 7
* up-left = 8
* up-front = 9
* up-right = 10
* up-back = 11

# 1 Representation
## 1.1 Offset

Offset function maps |N <-> |N^d. Offset functions are famous since [mode13h](https://en.wikipedia.org/wiki/Mode_13h), where offset=320y+x. Generally speaking:

```c++
offset = |X|y + x
offset = |X||Y|z |X|y + x
...
```

## 1.2 Sizeof(offset)

Sizeof is the number of bits needed to represent x states, is simply ceil(log2(x))

## 1.3 12sigma^2

State of edges.
12 objects with 2 possible states each take 12 bit. Obviously ceil(log2(2^x)) = x

## 1.4 8sigma^3

State of corners
8 objects with 3 possible states, ie 3^8 = 6561 states. Sizeof(6561) = 13 bits.

## 1.5 C8

Disposition of corners. 8! states = 40320. Sizeof(8!) = 16
Offset function is:
```c++
offset = a7 + 8*a6 + 8*7*a5 + 8*7*6*a4 + 8*7*6*5*a3 + 8*7*6*5*4*a2 + 8*7*6*5*4*3a1
```
notice that a0 does not appear in formula (position of a0 is the missing one after set a[7..1])

## 1.6 C8-8s3

sizeof(C8)+sizeof(8sigma^3) = 13 + 16 = 29
BUT!
offsetting(C8, 8s3) only 28 bits are needed! Offset function is:
```c++
offset = a7 + 8*a6 + 8*7*a5 + 8*7*6*a4 + 8*7*6*5*a3 + 8*7*6*5*4*a2 + 8*7*6*5*4*3a1 + 8!*3^i sigma[i];   // i in [0..7]
```


## 1.7 C12

Disposition of edges, 12! states = 479001600 states, sizeof(12!) = 29

## 1.8 Splitting C12 and C8

separating 8sigma3 from C8 costs 1bit. Further splitting of C8 into C8..4, C4 (or any other) would cost 1more bit.
in C12 states are naturally separated. Splitting C12 into C12..5, C5 is free. Any other split costs 1bit.

## 1.9 Final table of sizes

| Item       | sizeof(Item) |
| ---------- |:------------:|
| C8-8sigma3 | 28           |
| C12        | 29           |
| 12sigma2   | 12           |
| **Total**  | **69**       |

that is still the theoretical min.
keep in mind that 0 is the solved cube

With [fridrich method](https://en.wikipedia.org/wiki/CFOP_Method) one tends to solve C12..8, then C8..4 and C12..8..4, then C8..1 and lastly C12..8..4..1, an alternative rep would be:

| Item          | what is it              | sizeof(Item) |
| ------------- | ----------------------- |:------------:|
| C8..4-4sigma3 | down corners and states | 18           |
| C12..4        | down corners, mid edges | 25           |
| 8sigma2       | state of down-mid edges | 8            |
| C4..1-4sigma3 | up corners and states   | 11           |
| C4..1         | up edges                | 5            |
| 4sigma2       | state of up edges       | 4            |
| **Total**     |                         | **71**       |

This is nice because we can expect that the resulting 71bit integer *decreases* as we approach the solved state.

# 2 Moves

Moves are { R, U, L, D, F, B } and inverses { Ri, Ui, Li, Di, Fi, Bi }.
A move is a permutation of 4 edges and 4 corners, possibly with state changes.

## 2.1 Corners, permutations

Corner permutations for each moves are:

```c++
corners_permF = { CORNER_DFL, CORNER_UFL, CORNER_UFR, CORNER_DFR };
corners_permB = { CORNER_UBR, CORNER_UBL, CORNER_DBL, CORNER_DBR };
corners_permU = { CORNER_UFR, CORNER_UFL, CORNER_UBL, CORNER_UBR };
corners_permD = { CORNER_DFL, CORNER_DFR, CORNER_DBR, CORNER_DBL };
corners_permR = { CORNER_DFR, CORNER_UFR, CORNER_UBR, CORNER_DBR };
corners_permL = { CORNER_UFL, CORNER_DFL, CORNER_DBL, CORNER_UBL };
```

so that

```c++
position1[perm[x]] = position[perm[x-1]]
```

or, for an inverse move:
```c++
position1[perm[x]] = position[perm[x+1]]
```


## 2.2 Corners, states

Let's name the state for a corner observing where the white/yellow face points

| points     | state |
| ---------- | -----:|
| up/down    | 0     |
| front/back | 1     |
| right/left | 2     |

R,Ri,L,Li moves leave state=2 invariated and toggle states 0<->1
F,Fi,B,Bi moves leave state=1 invariated and toggle states 0<->2
U,Ui,D,Di moves leave state=0 invariated and toggle states 2<->1

## 2.3 Edges, permutations

Edge permutations for each moves are:
```c++
edges_permF = { EDGE_MFE, EDGE_NF,  EDGE_MFW, EDGE_SF };
edges_permB = { EDGE_SB,  EDGE_MBE, EDGE_NB,  EDGE_MBW };
edges_permU = { EDGE_NF,  EDGE_NL,  EDGE_NB,  EDGE_NE };
edges_permD = { EDGE_SW , EDGE_SF,  EDGE_SE,  EDGE_SB };
edges_permR = { EDGE_MFE, EDGE_NE,  EDGE_MBW, EDGE_SE };
edges_permL = { EDGE_MFW, EDGE_SW,  EDGE_MBE, EDGE_NL };
```

using the same permutation function we used for corners

# 3 Edges, states

Let's name the state for a corner observing where the white/yellow/red/orange face points

| points     | state  |
| ---------- | :----: |
| up/down    | 0      |
| front/back | **0**  |
| right/left | 2      |

F,Fi,B,Bi toggle state 0<->1.
The other moves leave edge state constant.

# 4 Move sequences

## 4.1 Notable sequences and orbit



