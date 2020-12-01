# Programování v jazyce C/ C++
Semestrální projekt pro tento předmět.
# Násobení matic
Pro výpočet násobení matic jsme použili Strassenův algoritmus, který je volán v implementaci rekurzivně. Strassenův algoritmus má _n=2,807_ , což je lepší než klasická metoda, která má _n=3_. Existuje také Coppersmith-Winogradův algoritmus, který má složitost _n=2,376_, to je ještě lepší než implementovaný Strassenův, ale na implementaci je složitý, a proto jsem ho nezvolil.

Program umí jen se čtvercovými matice o velikosti mocnin 2.

Přijímá vstupy přímo z příkazové řádky, nebo je zde možnost vložit parametr s cestou na .txt soubor, který obsahuje matici.

**Textový soubor musí být ve formátu:**

ČÍSLO[MEZERA]ČÍSLO[KONEC ŘÁDKU]

ČÍSLO[MEZERA]ČÍSLO[KONEC ŘÁDKU]

# Příkazy

**--help** 

Vypíše dostupné příkazy aplikace.

**--author**

Vrátí jméno a email autora.

**--version**

Vratí verzi aplikace.

**--direct** _[NUMBER]x[NUMBER] [NUMBER]x[NUMBER]_

Nastavení zadávání dat z konzole.
_Příklad: --direct 4x4 4x4_
Poté bude uživatel zadávat data ručně.

**--files** _[PATH1] [PATH2]_

Přijme cestu k textovému souboru, ze kterého si přečte data matice.

# Časy při single thread