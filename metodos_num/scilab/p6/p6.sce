function ej3()
    A = [ 1 -1  0;
         -2  4 -2;
          0 -1  1];
    for k = 1:10
        A(3,3) = 1 + 0.1 * k;
        disp("Raices de polinomio caracteristico: ", roots(poly(A, 'x')));
        disp("Autovalores: ", spec(A));
    end
endfunction
