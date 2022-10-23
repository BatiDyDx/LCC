function ej2()
    A = [10 1  2  3  4 ;
         1  9 -1  2 -3 ;
         2 -1  7  3 -5 ;
         3  2  3 12 -1 ;
         4 -3 -5 -1 15];
    b = [12; -27; 14; -17; 12];
    x0 = zeros(5, 1);
    eps = 10 ** -6;
    
    printf("Jacobi:");
    x = jacobi(A, b, x0, eps, 1000);
    disp("x: ", x);
    printf("Gauss-Seidel:")
    x = gauss_seidel(A, b, x0, eps, 1000);
    disp("x: ", x);
endfunction

function [A, b] = ej4(N)
    A = 8 * eye(N,N) + 2 * diag(ones(N-1,1),1) + 2 * diag(ones(N-1,1),-1)
    + diag(ones(N-3,1),3) + diag(ones(N-3,1),-3);
    b = ones(N,1);
endfunction

function ej5()
    A = [4  3  0;
         3  4 -1;
         0 -1 4];
    b = [24; 30; -24];
    x0 = [3.5; 3.8; -4.8]; // Solucion del sistema: x = [3; 4; -5]
    eps = 10 ** -7;
    w = 1.2404082; // Calculado en cuaderno de practica
    gauss_seidel(A, b, x0, eps, 1000);
    SOR(A, b, x0, w, eps, 1000);
endfunction

