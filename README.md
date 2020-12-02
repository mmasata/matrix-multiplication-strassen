# Programování v jazyce C/ C++
Semestrální projekt pro tento předmět.
# Násobení matic
Pro výpočet násobení matic jsme použili Strassenův algoritmus, který je volán v implementaci rekurzivně. Strassenův algoritmus má _n=2,807_ , což je lepší než klasická metoda, která má _n=3_. Existuje také Coppersmith-Winogradův algoritmus, který má složitost _n=2,376_, to je ještě lepší než implementovaný Strassenův, ale na implementaci je složitý, a proto jsem ho nezvolil.

Program umí jen se čtvercovými matice o velikosti mocnin 2.

Přijímá vstupy přímo z příkazové řádky, nebo je zde možnost vložit parametr s cestou na .txt soubor, který obsahuje matici.

**Textový soubor musí být ve formátu:**

ČÍSLO[MEZERA]ČÍSLO[KONEC ŘÁDKU]

ČÍSLO[MEZERA]ČÍSLO[KONEC ŘÁDKU]

# Popis zadání
Naimplementovat program pro násobení matic pomocí Strassenova algoritmu. Výsledný program bude umět přijímat data z příkazové řádky či souboru.
Program bude podporovat pouze čtvercové matice o velikosti libovolné mocniny na druhou. 

# Popis implementace
Nejprve jsem začal s _main.cpp_, kde jsem si nadefinoval switch pro přijímání argumentů z příkazové řádky.
Pokud přijde jakýkoliv jiný argument, než uvedený, pak háže chybu.

Poté jsem začal implementovat matici jako takovou, věděl jsem, že to budu ukládat v dvoudimenzionálním poli, ale ten jsem uložil dovnitř třídy _matrix_, kterou jsem si nadefinoval. Ta třída kromě dat obsahuje i řádky, sloupce, přetěžuje _operator<<_ pro příjemnější vypisování do konzole, a hlavně v destruktoru řeší mazání dvoudimenzionálního pole.

K matrix třídě jsem přidělal _add()_ a _substract()_ operaci k maticím, protože jsem věděl, že je u Strassena budu potřebat.

Poté jsem již začal se samotnou implementací Strassena. Toho jsem dělal rekurzivně, kde jsem vždy vytvořil podmatici o velikosti řádků a sloupců poloviny té předchozí.

Na závěr uvolním třídy matic, co již nejsou potřeba, destruktor matrixu se postará o uvolnění polí.

Poté jsem ještě doimplementoval možnost přijímat data ze souboru, kde jsem použil stejný princip jak u příkazové řádky, jen jsem to četl skrze _fstream_ ze souboru.

# Příkazy

**--help** 

Vypíše dostupné příkazy aplikace.

**--author**

Vrátí jméno a email autora.

**--version**

Vratí verzi aplikace.

**--direct** _[NUMBER]x[NUMBER] [NUMBER]x[NUMBER] [OPTIONAL_DESTINATION_PATH]_

Nastavení zadávání dat z konzole.
_Příklad: --direct 4x4 4x4_
Poté bude uživatel zadávat data ručně. Obsahuje ještě třetí, optional parametr, a to cílový .txt soubor, kam uložíme výslednou matici.

**--files** _[PATH1] [PATH2] [OPTIONAL_DESTINATION_PATH]_ 

Přijme cestu k textovému souboru, ze kterého si přečte data matice. Obsahuje ještě třetí, optional parametr, a to cílový .txt soubor, kam uložíme výslednou matici.

# Examples
V složce examples naleznete _exampleCommands.txt_, kde jsou vzorové příkazy. V složce se také nachází textové soubory _matrix-NUMBER-COUNT.txt_,
jedná se o vstupní data pro naši aplikaci, kde _NUMBER_ definuje počet řádků a sloupců matice.
_Příklad: matrix-16-1.txt, matrix-16.2.txt, ..._

# Časy při single thread