Plik tekstowy ma opisywać kolejne stany kostki Rubika 3x3x3


(stan 1)
---
(stan 2)
---
(stan 3)
---
itd.


Jeden stan składa się z 6 ścian kostki, zapisanych zawsze w następującej kolejności:


U (Up)    – ściana górna
D (Down)  – ściana dolna
F (Front) – ściana przednia
B (Back)  – ściana tylna
L (Left)  – ściana lewa
R (Right) – ściana prawa


Każda ściana:
zaczyna się od linii: X: gdzie X to identyfikator ściany (U, D, F, B, L, R)
zawiera 3 kolejne linie
każda linia ma 3 symbole kolorów oddzielone spacjami


Przykład jednej ściany:
U: W W W
W W W
W W W


Oznaczenie kolorów: 
    W-biały
    Y-żółty
    G-zielony
    B-niebieski
    O-pomarańczowy
    R-czerwony


Przykładowy plik txt

U: W W W
W W W
W W W
D: Y Y Y
Y Y Y
Y Y Y
F: G G G
G G G
G G G
B: B B B
B B B
B B B
L: O O O
O O O
O O O
R: R R R
R R R
R R R
---
U: W W G
W W G
O O G
D: Y Y B
Y Y B
R R B
F: G G Y
G G Y
G G Y
B: W B B
W B B
W B B
L: O O O
O O O
Y Y Y
R: R R R
R R R
W W W
---
