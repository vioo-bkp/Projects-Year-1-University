function [values, colind, rowptr] = matrix_to_csr(A)
  values = nonzeros(A.'); % imi elimina toate eleme 0 din matrice
  values = values';  
  
  [colind, ~] = find (A.'); % incepe sa numere locul elementelor diferite de 0
  colind = colind';
  
  z = [1; cumsum(sum(A ~=0,2))(1:end-1) + 1 ];
  
  x = z(end) + 2;
  
 rowptr = z;
 rowptr (end + 1) = x;
 rowptr = rowptr';

endfunction