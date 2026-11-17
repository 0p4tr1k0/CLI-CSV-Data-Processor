# CLI CSV Data Processor

A command-line interface (CLI) application written in C for parsing, modifying, and processing CSV data files. This project demonstrates low-level memory management, file I/O operations, and modular programming principles.

## 🚀 Features

* **Custom Parser:** Reads and parses `.csv` files natively without relying on external third-party libraries.

* **Data Manipulation:** Execute commands to modify the loaded CSV data (e.g., adding or removing rows).

* **Memory Safe:** Tested with Valgrind to ensure proper dynamic memory allocation and prevent memory leaks.

* **Automated Build:** Utilizes a `Makefile` for quick and efficient compilation and testing.

## 🛠️ Tech Stack

* **Language:** C

* **Build & Test Tools:** Make (GCC / MinGW), Valgrind

* **Environment:** Cross-platform (Linux / Unix / Windows)

## 📂 Project Structure

* `main.c` - Entry point handling CLI arguments and program loop.

* `csv.c` / `csv.h` - Core logic for reading, parsing, and manipulating CSV data.

* `Makefile` - Build instructions and automation commands.

* `input.csv` - Sample dataset for processing.

## ⚙️ How to Build and Run

### Prerequisites

Ensure you have a C compiler (like `gcc`) and `make` installed on your system. Valgrind is recommended for memory testing on Linux/Unix systems.

### Compilation

Clone the repository and compile the project using the provided Makefile:

```
git clone https://github.com/0p4tr1k0/projekt.git
cd projekt
make

```

### Execution & Testing (Using Makefile)

You can quickly run or test the application using the predefined Makefile targets:

* **Run the application:**

```
make run

```

```
*(Executes: `./databaze --output modified.csv --input input.csv`)*

```

* **Run with Valgrind (Memory Test):**

```
make test

```

```
*(Executes: `valgrind ./databaze --output modified.csv --input input.csv`)*

```

### Manual Execution

If you prefer to run it manually with custom arguments:

```
./databaze --output [OUTPUT_FILE.csv] --input [INPUT_FILE.csv]

```

## 🛠️ Available Commands

Once the program is running (or passed via standard input), it accepts several commands to manipulate the CSV data.

*(Note: Adjust this list based on the exact features your application supports)*

* `addrow [data1,data2,...]` - Appends a new row to the end of the CSV data.

* `deleterow [index]` - Deletes a specific row based on its index.

* `print` - Displays the current state of the loaded CSV data in the terminal.

* `save` - Saves the modified data to the specified output file.

* `exit` - Terminates the program securely and frees all allocated memory.

## 💡 Example Usage

Here is an example of a typical workflow within the CLI:

```
$ make run
> Loaded input.csv successfully (15 rows).
> addrow "Patrik,Longbottom,Developer"
Row added successfully.
> print
...
15: John,Doe,Manager
16: Patrik,Longbottom,Developer
...
> exit
Data saved to modified.csv. Memory freed. Goodbye!

```

## 👨‍💻 Author

**Patrik Mlčák**

* [GitHub](https://github.com/0p4tr1k0)
