% Mateescu Viorel-Cristian
% Grupa: 312CB

function [R1 R2] = PageRank(nume, d, eps)
  
  % Deschid fisierul din care se citeste
  open_file = fopen(nume,'r');
  nr_noduri = fscanf(open_file, '%f',1);
  
  % Parcurg tot fisierul pana ajung la ultimile 2 numere
  i = 1;
  while i <= nr_noduri
    temp_1 = fscanf(open_file, '%f', 1);
    temp_2 = fscanf(open_file, '%f', 1);
    for j = 1 : temp_2
      temp_3 = fscanf(open_file, '%f', 1);
    endfor
    i = i + 1;
  endwhile
  
  % Citesc val1 si val2
  val1 = fscanf(open_file, '%f', 1);
  val2 = fscanf(open_file, '%f', 1);

  fclose(open_file);
  
  % Construiesc numele fisierului de output
  last_output = strcat(nume, '.out'); 
  
  last_file = fopen(last_output, 'w'); 
  
  % Scriu pe prima linie numarul de pagini web
  fprintf(last_file, '%i \n', nr_noduri);
  
  R1 = Iterative(nume, d, eps);
  fprintf(last_file, '%.6f \n', R1);
  fprintf(last_file, '\n');
  
  R2 = Algebraic(nume, d);
  fprintf(last_file, '%.6f \n', R2);
  fprintf(last_file, '\n');

  % Sortez descrescator vectorul obtinut si il salvez in temp
  [temp, index] = sort(R2, 'descend');
  
  for i = 1 : nr_noduri
    % Calculez apartenenta si afisez
    y = Apartenenta(temp(i), val1, val2);
    fprintf(last_file, '%i %i %.6f\n', i, index(i), y);
  endfor
  
  fclose(last_file);
endfunction
