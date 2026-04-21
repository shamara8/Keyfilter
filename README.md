# Keyfilter - práca s textem
Projekt bol vytvorený v rámci predmetu Základy Programování VUT FIT.
## Popis projektu
Program, který emuluje algoritmus výpočtu povolení a zakázání kláves na virtuální klávesnici navigace. Vstupem programu jsou data známých adres a uživatelem zadaný řetězec. Výstup programu obsahuje znaky, které mají být na klávesnici povoleny.
## Syntax spuštění
Program se spouští v následující podobě: (./keyfilter značí umístění a název programu):

```./keyfilter ADRESA <adresy.txt```

## Syntax překladu
Program se přeloží pomocí ``make``

## Výstup programu
Výstup programu může být trojího druhu:

adresa nalezena,
adresa vyžaduje specifikaci,
adresa nenalezena.
### 1. Adresa nalezena

```Found: S```
Tento výstup se tiskne, pokud je v databázi adres nalezena jediná adresa S, jejíž prefix odpovídá uživatelem zadané adrese ADRESA. (Pozn. prefix P řetězce S je takový řetězec, u kterého řetězec S začíná řetězcem P).

### 2. Adresa vyžaduje specifikaci

```Enable: CHARS```
Pokud je v databázi adres nalezeno více adres odpovídající danému prefixu ADRESA, program pomocí takto naformátovaného řádku vytiskne seznam povolených kláves CHARS. CHARS je abecedně seřazený seznam znaků, u nichž pro každý znak C platí, že v databázi adres existuje adresa, jejíž prefix odpovídá spojení řetězce ADRESA s daným znakem C.

### 3. Adresa nenalezena

```Not found```
Pokud v databázi adres neexistuje adresa, jejíž prefix by odpovídal zadanému řetězci ADRESA, vytiskne program toto hlášení

### Speciální případ!
Ve zvláštním případě, kde ADRESA je shodná s existujícím záznamem v databázi adres a zároveň je ADRESA prefixem jiné adresy, program vytiskne dva řádky:

```Found: ADRESA```
```Enable: CHARS```
kde CHARS jsou znaky odpovídající možným způsobem pokračování adresy. (Příkladem může být zadání YORK s adresami York a Yorktown - program vytiskne jednak Found: YORK, ale také Enable: T).
