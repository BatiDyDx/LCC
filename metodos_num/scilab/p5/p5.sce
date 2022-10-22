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

function t = ej4(N, eps)
    A = 8 * eye(N,N) + 2 * diag(ones(N-1,1),1) + 2 * diag(ones(N-1,1),-1)
    + diag(ones(N-3,1),3) + diag(ones(N-3,1),-3);
    b = ones(N,1);
    tic();
    jacobi(A, b, zeros(N, 1), eps, 10000);
    t = toc();
endfunction

function ej5()
    A = [4  3  0;
         3  4 -1;
         0 -1 4];
    b = [24; 30; -24];
    x0 = [3.5; 3.8; -4.8]; // Solucion del sistema: x = [3; 4; -5]
    eps = 10 ** -7;
    Tj = eye(3,3);
    for i=1:3
        Tj(i,:) = Tj(i,:) - A(i,:) / A(i,i);
    end
    x = poly(0, 'x', 'r');
    p = max(abs(roots(det(Tj - x * eye(3,3))))); // Radio espectral de Tj
    w = 2 / (1 + sqrt(1 - p ** 2));
    gauss_seidel(A, b, x0, eps, 1000);
    SOR(A, b, x0, w, eps, 1000);
endfunction

