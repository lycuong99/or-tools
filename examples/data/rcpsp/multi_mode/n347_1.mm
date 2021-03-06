************************************************************************
file with basedata            : cn347_.bas
initial value random generator: 19465
************************************************************************
projects                      :  1
jobs (incl. supersource/sink ):  18
horizon                       :  126
RESOURCES
  - renewable                 :  2   R
  - nonrenewable              :  3   N
  - doubly constrained        :  0   D
************************************************************************
PROJECT INFORMATION:
pronr.  #jobs rel.date duedate tardcost  MPM-Time
    1     16      0       23       13       23
************************************************************************
PRECEDENCE RELATIONS:
jobnr.    #modes  #successors   successors
   1        1          3           2   3   4
   2        3          3           6   8  12
   3        3          3           5   6   9
   4        3          3           7   8   9
   5        3          2          13  14
   6        3          1           7
   7        3          2          10  13
   8        3          2          16  17
   9        3          3          10  12  14
  10        3          2          11  17
  11        3          1          15
  12        3          2          16  17
  13        3          2          15  16
  14        3          1          15
  15        3          1          18
  16        3          1          18
  17        3          1          18
  18        1          0        
************************************************************************
REQUESTS/DURATIONS:
jobnr. mode duration  R 1  R 2  N 1  N 2  N 3
------------------------------------------------------------------------
  1      1     0       0    0    0    0    0
  2      1     2       9    9    9    1    8
         2     6       5    8    7    1    5
         3     8       3    7    3    1    1
  3      1     5       4    5    6    2    8
         2     8       3    4    4    2    6
         3    10       3    3    3    1    4
  4      1     7      10    5    4   10    7
         2     9       8    4    4   10    7
         3    10       6    4    1   10    4
  5      1     1       9    4    7    7   10
         2     1       7    5    7    5    8
         3     4       4    4    7    5    6
  6      1     7       2    4    7    9    6
         2     7       2    4    8    8    6
         3    10       1    4    7    8    6
  7      1     5       7   10    6    9    7
         2     6       7    9    6    5    6
         3     7       7    8    5    5    4
  8      1     2       8    6   10    8    6
         2     7       7    5    9    7    6
         3     9       7    4    7    7    6
  9      1     1      10    8    5    9    3
         2     4       6    8    4    9    3
         3     6       4    3    4    9    2
 10      1     4       4    8    9    7    8
         2     4       4    9    6    6    8
         3     7       2    7    5    6    7
 11      1     1       9    7    7    4    6
         2     9       6    4    4    3    5
         3     9       7    3    4    3    4
 12      1     3       6    8   10    1    7
         2     8       6    5    9    1    6
         3     9       4    3    9    1    6
 13      1     1       2    6    8    8   10
         2     1       3    9    8    7   10
         3     3       1    3    8    4    7
 14      1     1       4   10    9    9    5
         2     1       4    8    8   10    5
         3     9       3    6    7    9    4
 15      1     1       6    3    7    5   10
         2     6       6    3    7    4    7
         3     9       5    3    5    4    7
 16      1     3       5    2    6    7    3
         2    10       5    2    6    2    3
         3    10       5    2    3    4    3
 17      1     2      10    3    9    9    7
         2     3       9    3    7    8    4
         3     6       8    2    5    8    3
 18      1     0       0    0    0    0    0
************************************************************************
RESOURCEAVAILABILITIES:
  R 1  R 2  N 1  N 2  N 3
   19   23  102   95   93
************************************************************************
