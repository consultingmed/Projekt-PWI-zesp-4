##
# @file cube_input_gui.py
# @brief Moduł interfejsu graficznego do wprowadzania stanu kostki Rubika.
# @details Pozwala użytkownikowi na "pomalowanie" siatki kostki, weryfikuje poprawność wprowadzonych danych (liczba kolorów, kompletność) i zapisuje je do pliku tekstowego.

import tkinter as tk
from tkinter import messagebox

COLORS = {
    'white':  '#FFFFFF',
    'yellow': '#FFFF00',
    'green':  '#00FF00',
    'blue':   '#0000FF',
    'red':    '#FF0000',
    'orange': '#FFA500',
    'grey':   '#D3D3D3'
}
HEX_TO_NAME = {v: k for k, v in COLORS.items()}
POLISH_NAME = {
    'white':  'biały',
    'yellow': 'żółty',
    'green':  'zielony',
    'blue':   'niebieski',
    'red':    'czerwony',
    'orange': 'pomarańczowy',
    'grey':   'szary'
}


class InputGUI:
    ##
    # @brief Główna klasa zarządzająca interfejsem graficznym.
    def __init__(self, root):
        ##
        # @brief Konstruktor klasy InputGUI.
        # @details Inicjalizuje główne okno, zmienne stanu i buduje układ interfejsu.
        # @param root Obiekt głównego okna tkinter (tk.Tk).
        self.root = root
        self.root.title("Siatka kostki")
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(1, weight=1)
        self.current_color = 'white'
        self.tiles = {}
        self.create_palette()
        self.grid_frame = tk.Frame(self.root, bg="#eeeeee", padx=25, pady=25)
        self.grid_frame.grid(row=1, column=0, sticky="nsew")
        self.create_grid()
        save_button = tk.Button(self.root, text="ZAPISZ", bg="#4CAF50", fg="white", font=("Arial", 12, "bold"), command=self.verify_and_save)
        save_button.grid(row=2, column=0, pady=20, sticky="ew", padx=50)
        
    def create_palette(self):
        ##
        # @brief Tworzy górny pasek z paletą kolorów i przyciskiem instrukcji.
        # @details Generuje przyciski dla każdego koloru zdefiniowanego w COLORS (oprócz szarego).
        palette_frame = tk.Frame(self.root, pady=10, bg="#dddddd")
        palette_frame.grid(row=0, column=0, sticky="ew")
        tk.Label(palette_frame, text="Wybierz kolor: ", bg="#dddddd", font=("Arial", 12)).pack(side=tk.LEFT, padx=10)
        
        for color_name, color_hex in COLORS.items():
            if color_name == 'grey': continue
            button = tk.Button(palette_frame, bg=color_hex, width=4, height=2, command=lambda c=color_name: self.set_brush(c))
            button.pack(side=tk.LEFT, padx=5)
            
        help_button = tk.Button(palette_frame, text="Instrukcja", bg="#2196F3",
                fg="white", font=("Arial", 11, "bold"), command=self.show_instructions)
        help_button.pack(side=tk.RIGHT, padx=20)
        
    def show_instructions(self):
        ##
        # @brief Wyświetla okno dialogowe z instrukcją obsługi programu.
        text = (
            "JAK KORZYSTAĆ Z PROGRAMU:\n\n"
            "1. Wybierz kolor z paska na górze.\n"
            "2. Kliknij w pole na siatce, aby je pomalować.\n"
            "3. Środkowe pola ścian są zablokowane – one wyznaczają kolor całej ściany.\n"
            "4. Musisz pomalować całą kostkę (bez szarych pól).\n"
            "5. Każdego koloru musi być dokładnie 9 kafelków.\n"
            "6. Gdy skończysz, kliknij zielony przycisk ZAPISZ."
        )
        messagebox.showinfo("Instrukcja", text)
            
    def set_brush(self, color):
        ##
        # @brief Ustawia aktualnie używany kolor "pędzla".
        # @param color Nazwa koloru (klucz ze słownika COLORS).
        self.current_color = color

    def create_grid(self):
        ##
        # @brief Konfiguruje układ siatki i rozmieszcza ścianki kostki.
        # @details Definiuje mapowanie nazw ścianek (U, L, F, R, B, D) na pozycje (x, y).
        for col in range(12):
            self.grid_frame.columnconfigure(col, weight=1)
        for row in range(9):
            self.grid_frame.rowconfigure(row, weight=1)
        faces_layout = {
            'U': (3, 0),
            'L': (0, 3),
            'F': (3, 3),
            'R': (6, 3),
            'B': (9, 3),
            'D': (3, 6)
        }
        for face_name, (offset_x, offset_y) in faces_layout.items():
            self.create_face(face_name, offset_x, offset_y)

    def create_face(self, face_name, offset_x, offset_y):
        ##
        # @brief Tworzy siatkę 3x3 przycisków dla pojedynczej ścianki.
        # @details Obsługuje logikę blokowania środków ścian (center tiles).
        # @param face_name Symbol ścianki (np. 'U', 'F').
        # @param offset_x Pozycja kolumny w głównej siatce.
        # @param offset_y Pozycja wiersza w głównej siatce.
        center_colors = {
            'U': 'white',
            'D': 'yellow',
            'F': 'blue',
            'B': 'green',
            'R': 'orange',
            'L': 'red'
        }
        for r in range(3):
            for c in range(3):
                text_on_button = ""
                color_bg = COLORS['grey']
                if r == 1 and c == 1:
                    text_on_button = face_name
                    color_bg = COLORS[center_colors[face_name]]
                button = tk.Button(self.grid_frame, bg=color_bg, text=text_on_button, borderwidth=1, relief="solid", font=("Arial", 15, "bold"))
                if r != 1 or c != 1:
                    button.config(command=lambda b=button: self.paint_tile(b))
                button.grid(row=offset_y + r, column=offset_x + c, sticky="nsew", padx=1, pady=1)
                self.tiles[(face_name, r, c)] = button
                
    def paint_tile(self, button_widget):
        ##
        # @brief Zmienia kolor tła klikniętego przycisku.
        # @param button_widget Obiekt przycisku, który został kliknięty.
        color_hex = COLORS[self.current_color]
        button_widget.configure(bg=color_hex)
        
    def verify_and_save(self):
        ##
        # @brief Weryfikuje poprawność stanu kostki i inicjuje zapis.
        # @details Sprawdza czy nie ma szarych pól oraz czy każdy kolor występuje dokładnie 9 razy. Jeśli weryfikacja przebiegnie pomyślnie, wywołuje save_to_file() i zamyka program.
        color_counts = {name: 0 for name in COLORS if name != 'grey'}
        result = {}
        for (face_name, r, c), button in self.tiles.items():
            bg_color_hex = button.cget('bg')
            color_name = HEX_TO_NAME[bg_color_hex]
            if color_name == 'grey':
                messagebox.showerror("Błąd", "Kostka nie jest w pełni pomalowana.\nUzupełnij szare pola.")
                return
            color_counts[color_name] += 1
            result[(face_name, r, c)] = color_name
        for color, count in color_counts.items():
            if count != 9:
                messagebox.showerror("Błąd", f"Każdy kolor powinien występować 9 razy.\n{POLISH_NAME[color].upper()} występuje {count} razy.")
                return
        messagebox.showinfo("Sukces", "Kostka jest poprawna! Zapisuję dane.")
        self.save_to_file(result)
        self.root.destroy()

    def save_to_file(self, data):
        ##
        # @brief Zapisuje przetworzone dane do pliku cube_input.txt.
        # @details Dokonuje transformacji danych (mapowanie nazw na litery) oraz obraca ściankę 'U' o 180 stopni zgodnie z wymaganiami algorytmu.
        # @param data Słownik zawierający stan kostki { (face, r, c): color_name }.
        colors = {
            'white': 'W',
            'yellow': 'Y',
            'green': 'G',
            'blue': 'B',
            'red': 'R',
            'orange': 'O'
        }
        face_order = ['U', 'D', 'F', 'B', 'L', 'R']
        try:
            with open("cube_input.txt", "w") as f:
                for face in face_order:
                    f.write(f"{face}: ")
                    for r in range(3):
                        row_colors = []
                        for c in range(3):
                            if face == 'U':
                                name = data[(face, 2-r, 2-c)]
                            else:
                                name = data[(face, r, c)]
                            letter = colors[name]
                            row_colors.append(letter)
                        line = " ".join(row_colors)
                        f.write(line + "\n")
        except Exception as e:
            messagebox.showerror("Błąd zapisu", f"Błąd: {e}")


if __name__ == "__main__":
    root = tk.Tk()
    root.minsize(600, 500) 
    cube_editor = InputGUI(root)
    root.mainloop()
