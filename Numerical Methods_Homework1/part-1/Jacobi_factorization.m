function [G_J, c_J] = Jacobi_factorization(A, b)
  
  [n m] = size(A); %imi afiseaza o matrice format din diag princip
  D = zeros (n,m);
  for i = 1 : n
    D(i, i) = A (i, i);
  endfor
  
  U = -triu(A, 1);
  L = -tril (A, -1);
  
  P = L + U;

  G_J = inv(D) * P; % matricea de iteratie

  c_J = inv(D) * b; % vectorul de iteratie

endfunction