## @file cli_handler.py
#  @brief Moduł obsługi interfejsu wiersza poleceń (CLI).
#  @details Odpowiada za pobranie danych od użytkownika, sformatowanie ich do specyfikacji
#           wymaganej przez silnik C++ oraz obsługę procesu.

import sys
from pathlib import Path
#dodać zimoprtowane z drugiego pliku python metody weryfikacji poprawnosci kostki

BASE_DIR = Path(__file__).resolve().parent.parent
DATA_DIR = BASE_DIR / "data"
INPUT_FILE = DATA_DIR / "cube_state.txt"
OUTPUT_FILE = DATA_DIR / "solution_steps.txt"

# Definicja kolejności ścianek i dozwolonych kolorów
FACES_ORDER = ['U', 'D', 'F', 'B', 'L', 'R']
VALID_COLORS = {'W', 'Y', 'G', 'B', 'O', 'R'}

##
# @brief Klasa zarządzająca komunikacją CLI i integracją.
class SolverCLI:
    
    ##
    # @brief Inicjalizacja z domyślnym timeoutem.
    def __init__(self, timeout_sec=5.0):
        self.timeout = timeout_sec

    ##
    # @brief Formatuje surowy ciąg znaków do formatu wymaganego przez plik .txt.
    # @details Zamienia "WWWWWWWWW" na "U: W W W W W W W W W".
    # @param face Oznaczenie ścianki (np. 'U').
    # @param stickers Ciąg 9 znaków kolorów.
    # @return Sformatowany ciąg dla jednej ścianki.
    def _format_face_string(self, face, stickers):
        # Rozdziela znaki spacjami: "WW..." -> "W W ..."
        spaced_colors = " ".join(list(stickers))
        return f"{face}: {spaced_colors}"

    ##
    # @brief Interaktywnie pobiera stan kostki od użytkownika.
    # @details Pyta oddzielnie o każdą z 6 ścianek, walidując długość i znaki.
    # @return Sformatowany ciąg gotowy do zapisu do pliku lub None w przypadku przerwania.
    def get_user_input(self):
        print("\n=== WPROWADZANIE STANU KOSTKI ===\n")
        print("Dozwolone kolory: B - Blue, G - Green, O - Orange, R - Red, W - White, Y - Yellow")
        print("Ścianki w kolejności: U (up - góra), D (down - dół), F (front - przód), B (back - tył), L (left - lewo), R (right - prawo)")
        print("Wpisuj ciągi po 9 znaków (np. WWWWWWWWW) dla każdej ścianki.\n")
        

        formatted_parts = []

        try:
            for face in FACES_ORDER:
                while True:
                    raw_input = input(f"Ścianka {face}: ").strip().upper()
                    
                    # Walidacja 1: Długość
                    if len(raw_input) != 9:
                        print(f"Błąd: Wymagane dokładnie 9 znaków. Wpisano {len(raw_input)}.")
                        continue
                    
                    # Walidacja 2: Poprawność znaków
                    invalid_chars = set(raw_input) - VALID_COLORS
                    if invalid_chars:
                        print(f"Błąd: Niedozwolone znaki: {invalid_chars}")
                        continue
                    
                    formatted_parts.append(self._format_face_string(face, raw_input))
                    break
            
            full_cube_state = " ".join(formatted_parts)
            return full_cube_state

        except KeyboardInterrupt:
            sys.exit(0)

    ##
    # @brief Zapisuje sformatowany stan kostki do pliku.
    # @param cube_string Gotowy ciąg danych.
    # @return True jeśli zapis się powiódł.
    def save_to_file(self, cube_string):
        try:
            DATA_DIR.mkdir(exist_ok=True)
            with open(INPUT_FILE, 'w') as f:
                f.write(cube_string)
            print(f"\nZapisano plik wejściowy: {INPUT_FILE}")
            return True
        except IOError as e:
            print(f"Błąd zapisu pliku: {e}")
            return False
    
    ##
    # @brief Główna pętla aplikacji.
    def run(self):
        cube_data = self.get_user_input()
        if cube_data:
            if self.save_to_file(cube_data):
                # Tu będzie wywołanie self.run_cpp_solver()
                print("OK")

if __name__ == "__main__":
    cli = SolverCLI()
    cli.run()