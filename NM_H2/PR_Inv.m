% Mateescu Viorel-Cristian
% Grupa: 312CB

function B = PR_Inv(A)
  % Algoritmul de factorizare folosit la laborator
	x = size(A); 
  
  % Initializez matricile Q si R cu 0
  Q = zeros(x);
  R = zeros(x);
  
  i = 1;
  while i <= x
    R(i, i) = norm(A(:, i));
    Q(:, i) = A(:, i) / R(i, i);
    R(i, i + 1 : x) = Q(:, i)' * A(:, i + 1 : x);
    A(:, i + 1 : x ) = A(:, i + 1 : x) - Q(:, i) * R(i, i+1 : x);
    i = i + 1;
  endwhile

  B = zeros(x);
  temp = eye(x);

  for i = 1 : x
    x = eq_triunghi(R, Q' * temp(:, i));
    B(:, i) = x;
  endfor
endfunction
