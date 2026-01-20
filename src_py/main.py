import argparse
import sys
import subprocess
from pathlib import Path
import shutil
import tkinter as tk
try:
    from cli_handler import SolverCLI, DATA_DIR, INPUT_FILE, OUTPUT_FILE
    import input_gui
except ImportError:
    sys.path.append(str(Path(__file__).resolve().parent))
    from cli_handler import SolverCLI, DATA_DIR, INPUT_FILE, OUTPUT_FILE
    import input_gui

BASE_DIR = Path(__file__).resolve().parent.parent
CPP_EXEC = BASE_DIR / "src_cpp" / "main"
GUI_SCRIPT = BASE_DIR / "src_py" / "vis_gui.py"

def run_cpp_solver():
    """Runs the C++ solver executable."""
    if not CPP_EXEC.exists():
        print(f"Błąd: Nie znaleziono pliku wykonywalnego C++ w {CPP_EXEC}")
        print("Proszę najpierw skompilować kod C++ (cd src_cpp && ./compile.sh).")
        return False
        
    print(f"\nUruchamianie solvera: {CPP_EXEC} --solve")
    try:
        result = subprocess.run([str(CPP_EXEC), "--solve"], capture_output=False, check=True)
        return True
    except subprocess.CalledProcessError as e:
        print(f"Solver zakończył działanie z kodem błędu {e.returncode}")
        return False
    except OSError as e:
        print(f"Wykonanie nie powiodło się: {e}")
        return False

def run_gui():
    """Runs the visualization GUI."""
    print(f"\nUruchamianie wizualizacji...")
    if not GUI_SCRIPT.exists():
        print(f"Błąd: Nie znaleziono skryptu GUI w {GUI_SCRIPT}")
        return

    # Workaround: vis_gui.py expects "test.txt" in CWD.
    # Copy our output to test.txt
    try:
        if OUTPUT_FILE.exists():
            shutil.copy(str(OUTPUT_FILE), "test.txt")
        else:
            print(f"Ostrzeżenie: Nie znaleziono pliku z rozwiązaniem {OUTPUT_FILE}. Wizualizacja może się nie udać.")
    except Exception as e:
        print(f"Nie udało się skopiować rozwiązania do test.txt: {e}")

    try:
        subprocess.run([sys.executable, str(GUI_SCRIPT)], check=True)
    except Exception as e:
        print(f"Nie udało się uruchomić GUI: {e}")

def main():
    parser = argparse.ArgumentParser(description="Rubik's Cube Solver Orchestrator")
    parser.add_argument('--terminal', "-t", action='store_true', help="Use terminal input mode")

    args = parser.parse_args()
    
    cube_state_ready = False
    
    if args.terminal:
        cli = SolverCLI()
    if args.terminal:
        cli = SolverCLI()
        print("Uruchamianie trybu terminalowego...")
        # cli.run() executes the input loop and saves to file
        cli.run()
        if INPUT_FILE.exists():
            cube_state_ready = True
    else:
        print("Uruchamianie trybu graficznego (GUI)...")
        try:
            root = tk.Tk()
            # Ensure window is large enough
            root.minsize(600, 500)
            app = input_gui.InputGUI(root)
            root.mainloop()
            
            # Check for the file created by input_gui.py
            gui_output = Path.cwd() / "cube_input.txt" # It saves in CWD
            # Verify if input_gui's CWD is same as here. Yes, normally.
            
            if gui_output.exists():
                print(f"GUI zamknięte. Przenoszenie {gui_output} do {INPUT_FILE}...")
                # Ensure destination directory exists
                DATA_DIR.mkdir(exist_ok=True)
                shutil.move(str(gui_output), str(INPUT_FILE))
                cube_state_ready = True
            else:
                print("GUI zamknięte, ale nie znaleziono pliku wyjściowego (może anulowano?).")
                
        except Exception as e:
            print(f"Błąd uruchamiania GUI: {e}")
            print("Zalecane użycie trybu --terminal.")
        
    if cube_state_ready:
        if run_cpp_solver():
            print("Rozwiązanie wygenerowane.")
            run_gui()
        else:
            print("Pomijanie wizualizacji z powodu błędu solvera.")

if __name__ == "__main__":
    main()
