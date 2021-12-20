## Data Structures - H3 - Parse Tree
Author: Mateescu Viorel-Cristian
Grupa: 312CB

In "lib.h" se gasesc prototipurile functiilor utilizate in redactarea acestei teme + structura pentru arbore.
In "structures.h" se gsaesc prototipurile functiilor pentru lista generica + structura pentru aceasta.


# "lib.c":

	Functia "NewNode" creeaza un nou nod. Se aloca memorie petru noul nod si pentru campul info al acestuia si se verifica alocarile. Se returneaza NULL(alocare nereusita) sau adresa nodului creat.

	Functia "AddChild" adauga un noud nod in arbore si ii genereaza acestuia un id pe baza id-ului parintelui sau. Exceptie fac nodurile "head"(1) si "body"(2) al caror parinte are id-ul setat pe NULL. Se face legatura atat cu parintele nodului, cat si cu un evetual frate.

	Functia "GetCurrentNode" returneaza(si elimina din lista de noduri) ultimul element din aceasta(nodul curent). Am folosit aceasta lista generica pentru a tine evidenta ultimul nod adaugat in arbore. Astfel de fiecare data cand se deschide un nou tag html acesta este intrdus in lista de noduri, iar cand acesta se inchide il scot din lista.

	Functia "CreateNode" se foloseste de functiile "NewNode" si "AddChild" pentru a creea si insera in arbore un nou nod. Pentru a completa campurile specifice unui nod din arbore ma folosesc de functia "Interpret". Pe baza starii curente(currentState) si a celei viitoare(futureState) imi dau seama ce camp trebuie completat si cu ce.

	Functia "DelNodeContent" elibereaza memoria ocupata de campurile unui nod din arbore(contents, style si otherAttributes).

	Functiile "FreeElem" si "Elim" elibereaza memoria ocupata de arbore/de o parte a acestuia. Pentru eliberarea continului unui nod se apeleaza functia "DelNodeContent". Nu am planificat sa se apeleze una pe cealalta, but it works asa ca le-am lasat asa.


# "style.c":
	
	Urmatoare trei functii le folosesc pentru a "formata" corect(dupa caz) sirurile de caractere citite din fisiere.

		Functia "Trim" elimina "leading, respectiv trailing spaces"	dintr-un sir de caractere.

		Functia "StripExtraSpaces" elimina spatiile extra dintr-un sir de caractere(lasa un sigur spatiu intre oricare doua caractere alfanumerice).

		Functia "RemoveSpaces" elimina toate spatiile dintr-un sir de caractere.


	Functia "CreateAttribute" creeaza un element de tip atribut. Se aloca memorie pentru acesta si se verifica alocarea. Se returneaza adresa atributului sau NULL.

	Functia "InsertAttribute" insereaza un atribut in lista de atribute a unui nod precizat din arbore.

	Functia "AppendStyle" realizeaza operatia de "appendStyle" asupra nodurilor ce au fost alese din arbore si inserate intr-o lista pe baza unui anumit selector. Selectie o realizez in functiile din fisierul getNodesByCriteria printr-o parcurgere in adancime(pe forum scria ca daca am facut parcurgere in adancime putem lasa asa, sa nu mai modificam). In cazul in care un atribut ce se doreste a fi adaugat in cadrul unui nod deja exista in lista de atribute de stil a acestuia se actualizeaza valoarea atributului respectiv, altfel se creeaza un nou atribut si se insereaza acesta in lista de stiluri a nodului respectiv.

	Functia "DelStyleFromList" goleste lista de stiluri a unui nod.(O apelez in functia "OverrideStyle".)

	Functia "OverrideStyle" aplica operatia de "overrideStyle" asupra nodurilor ce au fost alese din arbore si inserate intr-o lista pe baza unui anumit selector.Selectie o realizez in functiile din fisierul getNodesByCriteria printr-o parcurgere in adancime. Se goleste lista de atribute de stil a nodurilor selectate si se insereaza in aceasta noile atribute de stil precizate.

	Functia "Print" afiseaza "pe niveluri" arborele/continutul lui.(O folosesc pentru comanda "format".)

	Functiile "GetnewID" si "AdaptID" genereaza id-uri noi pentru nodurile din arbore dupa operatia de stergere a unor noduri din acesta.  Se reconstruiesc id-urile doar pentru nodurile ce "au avut de suferit" dupa operatia de stergere recursiva. Practci daca un nod si-a pierdut un frate ce se afla in lista de copii a altui nod inaintea acestuia trebuie scazuta o unitatea din grupul de pe ultimul punct din id si numerotatea nodurile copil ale acestuia.

# "getNodesByCriteria.c":

	Acest fisier contine functiile care realizeaza cautarea nodurilor care se incadreaza in anumite cerinte ale unui selector. Aceste functii au la baza parcurgerea in adancime a arborelui.

	Am explicat functionalitatea acestora in fisier.

	Functiile fie returneaza adresa nodului cautat sau NULL(in cazul functiei "GetNodesByID"), fie insereaza intr-o lista generica nodurile care se incadreaza in cerintele selectorului respectiv.

	In cazul in care lista este goala sau functia a returnat NULL se afiseaza un mesaj de eroare.

		Functia "GetNodesByID" pentru cautarea recursiva a nodurilor pe baza id-ului.
		Functia "GetNodesByTag" pentru cautarea recursiva a nodurilor pe baza numelui acestora.
		Functia "GetNodesByTagAndRelative" pentru cautarea recursiva a nodurilor pe baza numelui acestora si care au un stramos cu un anumit nume. 
		Functia "GetNodesByTagAndParent" pentru cautarea recursiva a nodurilor pe baza numelui acestora si care au un parinte cu un anumit nume. 
		Functia "GetNodesByClass" pentru cautarea recursiva a nodurilor pe baza atributului "class".
		Functia "GetNodesByTagAndClass" pentru cautarea recursiva a nodurilor pe baza atributului "class" si al numelui acestora.

# "delNodesByCriteria.c":
	
	Acest fisier contine functiile care realizeaza stergerea recursiva a nodurilor care se incadreaza in anumite cerinte ale unui selector. Aceste functii au la baza parcurgerea in adancime a arborelui. 

	Am explicat functionalitatea acestora in fisier.

	Apelarea acestora in main o realizez astfel: apelez mai intai functia pereche din fisierul getNodesByCriteria, iar in cazul in care exista noduri care sa se incadreze in selectorul dorit apelez functia de stergere recursiva. In cazul in care nu exista noduri care sa respecte criteriile dorite afisez un mesaj de eroare din main.

		Functia "DelNodesByID" pentru stergerea recursiva a nodurilor pe baza id-ului.
		Functia "DelNodesByTag" pentru stergerea recursiva a nodurilor pe baza numelui acestora.
		Functia "DelNodesByTagAndRelative" pentru stergerea recursiva a nodurilor pe baza numelui acestora si care au un stramos cu un anumit nume. 
		Functia "DelNodesByTagAndParent" pentru stergerea recursiva a nodurilor pe baza numelui acestora si care au un parinte cu un anumit nume. 
		Functia "DelNodesByClass" pentru stergerea recursiva a nodurilor pe baza atributului "class".
		Functia "DelNodesByTagAndClass" pentru stergerea recursiva a nodurilor pe baza atributului "class" si al numelui acestora.


In "interpret.c" se gaseste functia de pe acs pe care am modificat-o putin ca sa o folosesc la construirea arborelui.


# "lista.c":
	
	Acest fisier contine functiile pentru lista generica din tema anterioara.

	Functia "DistrLG" elibereaza memoria ocupata de o lista generica.
	Functia "InsLG" aloca memorie pentru un element si il insereaza la finalul listei generice.


# "main"(e cam aiurea facut, sincer):
	
	Citesc codul html dintr-un fisier si generez arborele corespunzator acestuia pe baza functiilor explicate mai sus, apoi realizez operatiile precizate in fisierul cu comenzi asupra arborelui:
		- add;
		- appendStyle;
		- overrideStyle;
		- deleteRecursively;
		- format.

# Local Checker
Total: [85/85]
Bonus: [20/20]
