# Tema 3 - Image_Processing
Nume: Mateescu F. Viorel-Cristian

Grupa: 312CB

### Task01:
* Functia "free_img", dezaloca imaginea primita de input.
* Functia "black_white", primeste imaginea din input.
* Pentru schimbarea output-ului imaginii, copiez denumirea "test", in variabila fileT.
* adaug acestei variabile sufixul "_black_white.bmp", cu ajutorul la strcat.
* Creez o matrice de pixeli, bitmap, care se afla pe o dimensiune height x width.
* Ignor paddingul in plus, cu fseek, si setez toti octetii in valoarea 0;
* Cu fseek, pun cursorul in fisier, de la fileheader (= y), de la inceputul imaginii, apoi cu for, construiesc imaginea (fiecare pixel din infoheader-ul).
* Functia "main", deschide fisierul input.txt, generat de checker, apoi apeleaza functiile pentru fiecare task.
* Functia "no_crop", adauga o bordare alba deasupra si dedesubtul imaginii.
