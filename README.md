## CSV databáze
Program vezme zadané data v "input.csv" souboru a přeloží je.

Program se spustí a můžeme manipulovat s daty z daného souboru. Jsou zde základní funkce
pro manipulaci s daty, jako např. přidání řádku, výpočet průměru sloupece, 
přidání sloupce...

### Funkce programu

**1. Načtení CSV souboru:**
Program načte CSV soubor zadaný uživatelem a
automaticky zpracuje data.

**2. Přidávání řádků:**
Program umožňuje přidávání řádků do načtené tabulky.

**3. Výpočet průměru sloupce:**
Program vypočte průměr daného sloupce a následně vypíše
výsledné číšlo uživateli (číslo je zaokrouhlené na jednu desetinu čísla).

**4. Výpočet součtu sloupce:**
Program umožňuje vypočítat součet čísel ve sloupci

**5. Přidávání sloupců:**
Užicatel může přidávat další sloupce.

**6. Uložení změn:**
Soubor je možné po úpravách uložit na disk.

### Přelození a spuštění programu
Program přeložíme zadaním příkazu ```make```.
Program spustíme příkazem ```./databaze --output "název výstupního souboru" --input "název vstupního souboru".```
Soubory musí mít koncovku **.csv**.
