% Mateescu Viorel-Cristian
% Grupa: 312CB

function triunghi = eq_triunghi(A, b)
  %Functie pentru a calcula sistem triung superior

  % Copiez marimea lui matricei A
  [n n] = size(A);
  triunghi(n) = b(n) / A(n, n);
  
  % Formula pentru calculul unui sistem superior-triunghiular
  % Algoritm folosit din Laborator
  for i = (n - 1) : -1 : 1
    t = 0;
    for j = (i + 1) : n
      t = t + A(i, j) * triunghi(j);
    endfor
    triunghi(i) = (b(i) - t) / A(i, i);
  endfor
endfunction
