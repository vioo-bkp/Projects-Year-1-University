# Tema 1 - IPv4_Address
Nume: Mateescu F. Viorel-Cristian

Grupa: 312 CB

### Declarare Functii:
* binaryRepresentation- functie ce am folosit-o la task-ul 8, pentru a reprezenta in binar a fiecarui octet.
* declarand o variabila i, shiftarea era diferita de 0 afiseaza 1, daca nu, 0.
* getByte- functie ce stocheaza in "byte" shiftarea la dreapta cu 8, 16, 24 biti si retine in unsigned char, fiecare byte al adresei.

* Pe prima linie se va citi numărul de seturi de date si fiecare set de date va fi precedat de o linie cu numărul setului corespunzator.
* In functia "main" sunt declarate variabilele necesare pentru calcul binar si afisari/citiri de MASTI si IP-uri. 
* Am declarat un "for" care lucreaza cu octetii prin shiftare, incorporand o bucla, prin introducerea unei adrese IP in format punctat.
### Rezolvari Taskuri:
#### Task 1 & 2
* Functia "getByte". Odata pentru afisarea in format zecimal a mastii MSK_2 si afisarea in format IP/MASK printr-un printf..

#### Task 3
* Am declarat variabila "aux" careia i-am atribuit valoarea lui IP_1. Apoi am facut "si logic" intre biții adresei IP_1 și biții măștii de rețea MSK_1.
* Transform adresa intr-o adresa hibrida punand biti de 0 acolo unde se găsește masca de rețea.
* Adresa de retea are toti bitii de baza in momentul acesta setati pe 0. 

#### Task 4
* Am declarat o noua variabila "mask1" care neaga bitii lui "mask", inversând valoarea bitilor de pe fiecare poziție,apoi "sau logic" intre biții adresei IP și biții din complementul măștii de rețea.
* Transform adresa intr-o adresa hibrida punand biti de 1 acolo unde se găsește masca de rețea.
* Adresa de retea are toti bitii de baza in momentul acesta setati pe 1.

#### Task 5
* Noile variabile "aux1" si "aux2" iau valorile lui IP_1 si IP_2, apoi fac "si logic" cu mask (fiecare dintre ip-uri).
* Daca adresele lor sunt egale(fac parte din aceeasi retea) afisez "DA", sau daca nu sunt egale, "NU".

#### Task 6
* Noua variabila MSK_1p ia valoarea mastii MSK_1, apoi daca MSK_1 este par si vom face modul de 2, si rezultatul este 0, MSK_1 va fi shiftat cu 1. Daca MSK_1 si masca sunt egale cu masca, va afisa DA, altfel NU.
* Noua variabila "nr" ia  valoarea 0, variabila care o folosesc pentru a scadea numarul de octeti, apoi se face shiftare la stanga lui 1, din care se scade 1 octet.
* Afisarea este una simpla cu ajutorul functiei "if".

#### Task 7
* M-am folosit de un "if" care afiseaza: daca MSK_1 si masca sunt egale cu masca, atunci va afisa MSK_1p. Pentru corectarea mastii, am folosit tot un if , incorporat cu un for care ajuta la MSK_1p, prin shiftare (valoarea lui i) apoi este decrementat, iar daca rezultatul este 0, MSK_1p va fi rezultatul dintre shiftarea lui MSK_1p, la dreapta cu valoarea lui i.
* Apoi masca rezultata va fi din nou shiftata la stanga cu i pana o corecteaza.

#### Task 8
* Reprezentarea in binar am realizat-o folosindu-ma de functia "binaryRepresentation".
* Functie simpla, ce are incorporata un for, se verifica daca numarul se divide cu 2 cu ajutorul operatorului modul %.
* Numarul il divide cu 2 si apoi il stocheaza, apoi il imparte la 2 pana cand catul devine 0.

#### Task 9
* Creeaza masca retelei de net, ca la task 2, unde networkIP face shiftari pentru stocarea ip-ului intr-un numar.
* Am declarat doua variabile pentru network sugestive. Daca networkMask este mai mare ca zero, mask va fi shiftat cu 1, apoi fac "sau logic" cu 1 schimband bitii in 1.
* Apoi networkMask este decrementat cu 1. Daca networkMask este 0, atunci mask va fi direct shiftat cu 1, la stanga.
* Daca indicii retelelor fac parte din IP_2, si sunt egale va afisa printr-un "if" 0.
