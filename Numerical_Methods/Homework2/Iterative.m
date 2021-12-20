% Mateescu Viorel-Cristian
% Grupa: 312CB

function R = Iterative(nume, d, eps)
	
  open_file = fopen(nume,'r');
  
  % Citesc numarul de noduri
  nr_noduri = fscanf(open_file, '%f', 1);
  
  % Initializez A cu zero-uri. In A voi retine matricea de adiacenta
  A = zeros(nr_noduri);
  
  % Retin in B un vector coloana cu nr_noduri linii pline de 1
  B = ones(nr_noduri,1);
  
  % pun 1 daca "x_coloana" este in lista de vecini a lui "x_linie"
  
  i = 1;
  while i <= nr_noduri
    x_linie = fscanf(open_file, '%f', 1);
    x_count = fscanf(open_file, '%f', 1);
    for j = 1 : x_count
      x_coloana = fscanf(open_file, '%f', 1);
      A(x_linie, x_coloana) = 1;
    endfor
    i = i + 1;
  endwhile
  
  fclose(open_file);
  % Pun 0 pe diagonala principala deoarece o pagina nu are link catre ea insasi
  
  i = 1;
  while i <= nr_noduri
    A(i, i) = 0;
  i = i + 1;
  endwhile
  
  % Calculez numarul de linkuri de fiecare pagina ca fiind suma elem linie
  i = 1;
  while i <= nr_noduri
    L(i) = 0;
    for j = 1 : nr_noduri
      L(i) = L(i) + A(i, j);
    endfor
    i = i + 1;
  endwhile
  
  % Am calculat inversul fiecarui element de pe diagonala.
  Z = zeros(nr_noduri);
  i = 1;
  while i <= nr_noduri
    invZ(i, i) = 1 / L(i);
    i = i + 1;
  endwhile
  
  M = (invZ * A)';
  R_initial(1 : nr_noduri, 1) = 1 / nr_noduri;
  R = d * M * R_initial + ((1 - d) / nr_noduri) * B;
  
  while norm(R - R_initial) >= eps
    R_initial = R;
    R = d * M * R_initial + (( 1 - d ) / nr_noduri) * B;
  endwhile

  R = R_initial; 
endfunction
	