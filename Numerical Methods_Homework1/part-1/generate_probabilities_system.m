function [A, b] = generate_probabilities_system(rows)
  
   A = zeros (sum(1:rows));
   A (1,1) = 4; %primul element din matrice este mereu 4
   A (1, 2:3) = -1;
   prim = 1;
   
  i=2;
  while i <= sum(1:rows-1)
      if i > sum(1:prim)
         prim=prim+1;
      end
      if (i == sum(1:prim)) || (i == sum(1:prim-1)+1)
          A(i,i) = 5;
      else
         A(i,i) = 5 + 1;
     end
     i=i+1;
  end
   
   for i = sum(1: (rows - 1)) + 1: sum(1: (rows))
     if (( i == sum(1: (rows - 1)) + 1) || ( i == sum(1: (rows)) ))
       A (i,i) = 4;
     else
       A (i,i) = 4 + 1;
     endif
   endfor
   
   reminder = -1;
   prim = 2;
   for i = 2: sum(1: (rows))
     for j = 1: i - 1
       if (A(j,i) == -1)
         A(i,j) = -1;
       endif
     endfor
     
     if ( i > sum(1: (prim)) )
       prim ++;
       reminder = -1;
     endif
     reminder ++;
     if (prim != rows)
       A(i, sum(1:(prim))+ 1 + reminder: sum(1:(prim))+ 1 +reminder + 1) = -1;
     endif
     if (reminder != prim - 1)
       A(i, i+1) = -1;
     endif
   endfor
   
   b( sum(1:(rows-1)) + 1: sum(1:(rows)) ) = 1;
   b( 1:sum (1:(rows-1)) ) = 0;
   b = b';
  
  
endfunction
