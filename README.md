# Projekt z PWI zespół 4
Tematem projektu jest program układający kostkę Rubika.

# Ramowy plan projektu:
1) Wczytanie danych (Python):
Użytkownik wprowadza stan początkowy kostki na interaktywnej planszy. Program sprawdza poprawność danych (m.in. zgodność liczby pól w danym kolorze). Po zatwierdzeniu generowany jest plik wejściowy .txt zawierający cyfrową reprezentację układu ścianek.

2) Warstwa algorytmiczna (C++): Program wczytuje wygenerowany plik, przetwarza dane i uruchamia algorytm rozwiązujący. Sekwencja ruchów zapisywana jest do osobnego pliku wynikowego .txt.

3) Wizualizacja rozwiązania (Python): Program odczytuje listę ruchów z pliku i prezentuje użytkownikowi instrukcję ułożenia kostki. 

Oraz przy 1) i 3) aspoekcie: możliwość wypisywania (i wczytywania) na standardowe wyjście


## Dokumentacja (Doxygen)

Projekt wykorzystuje narzędzie **Doxygen** do automatycznego generowania dokumentacji dla kodu C++ oraz Python. Pliki dokumentacji (HTML/LaTeX) nie są przechowywane w repozytorium (są ignorowane przez `.gitignore`). Po pobraniu repozytorium należy pobrać Doxygen:
  ```bash
  sudo apt install doxygen
  ```
A nastepnie wygenerować pliki:
  ```bash
  doxygen Doxyfile
  ```
Dokumentacja powinna wtedy znaleźć się w pliku html/index.html oraz latex/refman.tex


# Dane zespołu
Zespół 4, opiekun Piotr Ostropolski-Nalewaja, skład: 
359949 359409 351683 361008 360678 331060 [Python i C++]

### Planowana struktura repozytorium
```text
/Projekt-PWI-zesp-4
│
├── README.md               # Instrukcja uruchomienia, autorzy, opis (P3)
├── .gitignore              # Ignorowanie plików .o, .exe, __pycache__, .txt (P3)
├── Doxyfile                # Plik tworzący dokumentację
│
├── /data                   # Folder wymiany danych
│   ├── .gitkeep            # Żeby git widział pusty folder
│   ├── cube_state.txt      # Generuje P1 lub P3 -> Czyta C1
│   └── solution_steps.txt  # Generuje C1/C2 -> Czyta P2 lub P3
│
├── /src_cpp                # Kod źródłowy C++
│   ├── main.cpp            # (C1) Ładuje dane, uruchamia solver
│   ├── Cube.cpp / .h       # (C1) Struktura
│   ├── Solver.cpp / .h     # (C2) Algorytm
│   └── Heuristics.cpp / .h # (C3) Optymalizacja
│
├── /src_py                 # Kod źródłowy Python
│   ├── main.py             # (P3) Główny skrypt sterujący (menu)
│   ├── input_gui.py        # (P1) Okno wprowadzania
│   ├── vis_gui.py          # (P2) Okno wizualizacji
│   └── cli_handler.py      # (P3) Obsługa konsoli
│
└── /docs                   # Dokumentacja projektowa
    └── format_pliku.md     # KRYTYCZNE: Opis formatu plików .txt
```
