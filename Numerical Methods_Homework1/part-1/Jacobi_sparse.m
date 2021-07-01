function [x] = Jacobi_sparse(G_values, G_colind, G_rowptr, c, tol)

  lungimev = length (c);
  x = zeros (lungimev,1);
  aproximare = 0;  % vectorul de aproximare = 0
  
  do %apelez functia pana cand aprox < tol si rezulta x
    indexare = x;
    x = csr_multiplication(G_values, G_colind, G_rowptr, indexare) + c;
    aproximare = norm (x-indexare);
  until aproximare < tol %vect aprox sa fie mai mic ca toleranta
  
endfunction