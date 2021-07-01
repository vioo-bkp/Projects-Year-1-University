% Mateescu Viorel-Cristian
% Grupa: 312CB

function R = Algebraic(nume, d)

  open_file = fopen(nume,'r');
  
  % Citesc numarul de noduri
  nr_noduri = fscanf(open_file, '%f', 1);
  A = zeros(nr_noduri);
  
  % Retin in B intr-un vector 
  B = ones(nr_noduri,1);
  i = 1;
  while i <= nr_noduri
    x_linie = fscanf(open_file, '%f', 1);
    temp = fscanf(open_file, '%f', 1);
    for j = 1 : temp
      y_coloana = fscanf(open_file, '%f', 1);
      A(x_linie, y_coloana) = 1;
    endfor
    i = i + 1;
  endwhile
  
  % Inchid fisierul pentru ca am terminat citirea
  fclose(open_file);
  
  % Pun 0 pe diagonala principala deoarece o pagina nu are link catre ea insasi
  i = 1;
  while i <= nr_noduri
    A(i, i) = 0;
    i = i + 1;
  endwhile
  
  % Calculez numarul de linkuri detinut de fiecare pagina ca fiind suma
  % elementelor de pe fiecare linie
  i = 1;
  while i <= nr_noduri
    Z(i) = 0;
    for j = 1 : nr_noduri
      Z(i) = Z(i) + A(i, j);
    endfor
    i = i + 1;
  endwhile
  
  % invY este inversul fiecarui element de pe diagonala.
  Y = zeros(nr_noduri);
  for i = 1 : nr_noduri
    invY(i, i) = 1 / Z(i);
  endfor
  
  M = (invY * A)';
  
  % Initializez Temp cu matricea identitate
  Temp = eye(nr_noduri);
  
  % Calculez inversa lui I - d * M folosind factorizari GramSchmidt
  inv_temp = PR_Inv(Temp - d * M);
  
  % Calculez R folosind algoritmul algebraic
  R = inv_temp * (1 - d ) / nr_noduri * B; 
endfunction
