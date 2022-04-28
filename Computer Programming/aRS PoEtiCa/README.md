# Tema 2 - aRS PoEtiCa
Nume: Mateescu F. Viorel-Cristian

Grupa: 312CB

### Task 0:
* Structura "Interactive Console", este formata din o serie de "if-uri" care verifica input-ul de la tastatura, prin functia din "string.h".
* Apeleaza functia corespunzatoare input-ului;
### Task 1:
* Functia "uppercase", introduce intr-o variabila poezia apelata de "load".
* Primul "if", rescrie toate caracterele din string in litere mari, apoi se verifica ca fiecare prim caracter din fiecare vers sa fie mare.
* Apoi pe restul le transforma in lowercase. 
### Task 2:
* Functia "trimming", stocheaza intr-o variabila poezia apelata.
* Prin for loop, verifica fiecare caracter ( "a-z", "A-Z"), fara caractere speciale si incrementeaza stringul.
* Prin "if", daca se gasesc caractere ( -, ') le elimina (o problema cu aceste doua caractere), precum si spatiile in plus.
* Apoi rescrie stringul cu un singur spatiu intre cuvinte si elimina non-caracterele.
### Task 3:
* Functia "silly", se declara o variabila "caracter" care i-a valoarea fiecarui caracter din string.
* In functie de valoarea lui p, va schimba fiecare caracter din string.
* Schimbarea este aplicata in functie de valoarea lui sample si realizata printr-o conditie soecifica.
* Daca caracterele sunt mici, atunci le face uppercase. Daca p este mai mic ca sample atunci le face lowercase;
### Task 4:
* Functia "friendly", stocheaza fiecare cuvant intr-un vector pana intalneste caracterul NULL, pentru a determina sfarsitul stringului.
* In momentul in care gaseste NULL, se opreste si apeleaza functia get_friendly.
* Daca nu ii gaseste sinonim pastreaza cuvantul curent, daca nu, il inlocuieste cu sinonimul sau si il copie in variabila "aux".
* Dupa ce a facut verificarea completa a fiecarui cuvant copie tot aux in poezia initiala.
### Task 5:
* Functia "rhimy", se copie poezia intr-un buffer si se impart cuvintele in Tokens. 
* Separ ultimul cuvant din fiecare vers si il introduc intr-o matrice fara caractere non-alfabetice.
* Pentru rima imperecheata, verifica primul vers cu al doilea si incearca sa-i gaseasca un sinonim din lista specifica. 
* Daca ii gaseste sinonim, acesta sa fie cel mai mic lexicogramatic .Daca nu se gaseste sinonim, atunci returneaza valoarea NULL si-l lasa neschimbat.
* Rolul de comparare in cazul in care sinonimul este diferit de "zz" (nu exista cuvant care sa inceapa cu "zz") il inlocuieste in string.
* Este o verificare pentru rima, in cazul in care inlocuieste sinonimul sau diminutivul in locul cuvantului respectiv, acesta sa asigure rima de orice tip.
* Singura diferenta este aparitia lui modulo 4, care sa-mi asigure ca versurile pare (0-2, 1-3, 4-6, 5-7) pentru rima incrucisata sunt accesate.
* La rima imbratisata, m-am folosit de variabila "pas" care are rolul de a indica pozitia tipului de rima (0-3, 1-2, 0-4, 2-3).
