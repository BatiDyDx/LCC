function a = gausselim(A,b)
[nA,mA] = size(A) 
[nb,mb] = size(b)

if nA<>mA then
    error('gausselim - La matriz A debe ser cuadrada');
    abort;
elseif mA<>nb then
    error('gausselim - dimensiones incompatibles entre A y b');
    abort;
end;

a = [A b]; // Matriz aumentada

// Cantidad de operaciones en eliminacion progresiva
ops = 0;

// Eliminación progresiva
n = nA;
for k=1:n-1
    for i=k+1:n
        a(i,k+1:n+1) = a(i,k+1:n+1) - (a(i,k)/a(k,k)) * a(k,k+1:n+1)
        ops = ops + (n - k + 1) * 3;
        a(i,k) = 0;
    end;
end;

printf("Numero de operaciones: %d\n", ops);

endfunction

function a = gausselimPP(A,b)
// La función implementa el método de Eliminación Gaussiana con pivoteo parcial.

[nA,mA] = size(A) 
[nb,mb] = size(b)

if nA<>mA then
    error('gausselimPP - La matriz A debe ser cuadrada');
    abort;
elseif mA<>nb then
    error('gausselimPP - dimensiones incompatibles entre A y b');
    abort;
end;

a = [A b]; // Matriz aumentada
n = nA;    // Tamaño de la matriz

// Cantidad de operaciones en eliminacion progresiva
ops = 0;

// Eliminación progresiva con pivoteo parcial
for k=1:n-1
    kpivot = k; amax = abs(a(k,k));  //pivoteo
    for i=k+1:n
        if abs(a(i,k))>amax then
            kpivot = i; amax = a(i,k);
        end;
    end;
    temp = a(kpivot,:); a(kpivot,:) = a(k,:); a(k,:) = temp;
    
    for i=k+1:n
        a(i,k+1:n+1) = a(i,k+1:n+1) - (a(i,k)/a(k,k)) * a(k,k+1:n+1)
        ops = ops + (n - k + 1) * 3;
        a(i,k) = 0;
    end;
end;

printf("Numero de operaciones: %d\n", ops);

endfunction

function x = solve_upper(A, b)
    n = size(A, 1);
    x(n) = b(n) / A(n, n)
    for k = n-1:-1:1
        x(k) = (b(k) - A(k, k+1:n) * x(k+1:n)) / A(k, k);
    end
endfunction

function x = solve_lower(A, b)
    n = size(A, 1);
    x(1) = b(1) / A(1, 1);
    for k = 2:n
        x(k) = (b(k) - A(k, 1:k-1) * x(1:k-1)) / A(k, k);
    end
endfunction

function x = solve(A, b, use_pivot)
    n = size(A, 1);
    if use_pivot then
        a = gausselimPP(A,b);
    else
        a = gausselim(A,b);
    end;
    x = solve_upper(a(1:n,1:n), a(:,n+1));
endfunction

function [X, a] = gausselim_multi_sys(A,B)
[nA,mA] = size(A) 
[nB,mB] = size(B)

if nA<>mA then
    error('gausselim_multi_sys - La matriz A debe ser cuadrada');
    abort;
elseif mA<>nB then
    error('gausselim_multi_sys - dimensiones incompatibles entre A y B');
    abort;
end;

a = [A B]; // Matriz aumentada

// Cantidad de operaciones en eliminacion progresiva y sustitucion regresiva
ops = 0;

// Eliminación progresiva
n = nA;
m = mB;
for k=1:n-1
    for i=k+1:n
        a(i,k+1:n+m) = a(i,k+1:n+m) - (a(i,k)/a(k,k)) * a(k,k+1:n+m)
        ops = ops + (n + m - k) * 3;
        a(i,k) = 0;  // no hace falta para calcular la solución x
    end;
end;

// Sustitución regresiva
X = zeros(n, m);
X(n, :) = a(n,n+1:n+m)/a(n,n);
for i = n-1:-1:1
    X(i, 1:m) = (a(i,n+1:n+m) - a(i,i+1:n) * X(i+1:n,1:m)) / a(i,i);
    ops = ops + (m * (n - i) * 2 + 2);
end;

printf("Numero de operaciones: %d\n", ops);

endfunction

function B = inverse_gauss(A)
    [nA, mA] = size(A);
    if nA<>mA then
        error('inverse_gauss - La matriz A debe ser cuadrada');
        abort;
    end
    [B, _] = gausselim_multi_sys(A, eye(nA, nA));
    disp(B);
endfunction

function x = gausselim_det(A)
    [nA,mA] = size(A)

    if nA<>mA then
        error('gausselim_det - La matriz A debe ser cuadrada');
        abort;
    end;

    // Contador de operaciones
    ops = 0;

    // Eliminación progresiva
    n = nA;
    for k=1:n-1
        for i=k+1:n
            A(i,k+1:n) = A(i,k+1:n) - (A(i,k)/A(k,k)) * A(k,k+1:n);
            A(i,k) = 0;
        end;
    end;

    x = prod(diag(A));
endfunction

function [x, a] = gausselim_tridiag(A, b)
    [nA, mA] = size(A);
    if nA<>mA then
        error('gausselim_tridiag - La matriz A debe ser cuadrada');
        abort;
    end;
    
    a = [A b];
    n = nA;
    
    // Eliminacion progresiva
    for k = 1:n-1
        a(k+1,k) = 0;
        a(k+1,k+1) = a(k+1,k+1) - a(k,k+1) * a(k+1,k) / a(k,k);
        a(k+1,n+1) = a(k+1,n+1) - a(k,n+1) * a(k+1,k) / a(k,k);
    end;
    ops = (n - 1) * 2 * 3;
    
    // Sustitucion regresiva
    x(n) = b(n) / a(n,n);
    for k = n-1:-1:1
        x(k) = (b(k) - a(k,k+1) * x(k+1)) / a(k,k);
    end
    ops = ops + (n - 1) * 3;
    printf("Numero de operaciones: %d\n", ops);
endfunction

function [P, L, U] = gausselimPP_PALU(A)
    [n, m] = size(A);
    if n<>m then
        error('gausselimPP_PALU - La matriz A debe ser cuadrada');
        abort;
    end;
    
    P = eye(n,n);
    L = eye(n,n);
    U = A;
    
    for k = 1:n-1
        i = k; pivot_max = abs(A(k,k));
        for j = k+1:n
            if abs(A(j,j)) > pivot_max
                i = j; pivot_max = abs(A(j,j));
            end
        end
        
        if i <> k then
            tmp = U(k,k:n); U(k,k:n) = U(i,k:n); U(i,k:n) = tmp;
            tmp = L(k,1:k-1); L(k,1:k-1) = L(i,1:k-1); L(i,1:k-1) = tmp;
            tmp = P(k,:); P(k,:) = P(i,:); P(i,:) = tmp;
        end
        
        for j = k+1:n
            L(j,k) = U(j,k) / U(k,k);
            U(j,k:n) = U(j,k:n) - L(j,k) * U(k,k:n);
        end
    end
endfunction

function [L, U] = doolittle(A)
    [n, m] = size(A);
    if n<>m then
        error('doolittle - La matriz A debe ser cuadrada');
        abort;
    end;
    
    L = eye(n, n);
    U = zeros(n, n);
    
    U(1,:) = A(1,:);
    L(:,1) = A(:,1) / U(1,1);
    for k = 2:n
        U(k,k:n) = A(k,k:n) - L(k,1:k-1) * U(1:k-1,k:n);
        for j = k+1:n
            L(j, k) = (A(j, k) - L(j,1:k-1) * U(1:k-1,k)) / U(k,k);
        end
    end
endfunction

function [L, U, P] = doolittle_pivoting(A)
    [n, m] = size(A);
    if n<>m then
        error('doolittle_pivoting - La matriz A debe ser cuadrada');
        abort;
    end;
    
    L = eye(n, n);
    U = zeros(n, n);
    // P = eye(n,n);
    /*
    kpivot = 1; amax = abs(A(1,1));  //pivoteo
    for i=2:n
        if abs(A(i,1))>amax then
            kpivot = i; amax = A(i,1);
        end;
    end;
    temp = A(kpivot,:); A(kpivot,:) = A(1,:); A(1,:) = temp;
    temp = P(kpivot,:); P(kpivot,:) = P(1,:); P(1,:) = temp;
    */
    U(1,:) = A(1,:);
    if U(1,1) <> 0 then
        L(:,1) = A(:,1) / U(1,1);
    end
    for k = 2:n
        /*
        kpivot = 1; amax = abs(A(k,k));  //pivoteo
        for i=k+1:n
            if abs(A(i,k))>amax then
                kpivot = i; amax = A(i,k);
            end;
        end;
        temp = A(kpivot,:); A(kpivot,:) = A(k,:); A(k,:) = temp;
        temp = P(kpivot,:); P(kpivot,:) = P(k,:); P(k,:) = temp;
        */
        U(k,k:n) = A(k,k:n) - L(k,1:k-1) * U(1:k-1,k:n);
        if U(k,k) <> 0 then
            for j = k+1:n
                L(j, k) = (A(j, k) - L(j,1:k-1) * U(1:k-1,k)) / U(k,k);
            end
       end
    end
endfunction


function [L, U] = crout(A)
    [n, m] = size(A);
    if n<>m then
        error('crout - La matriz A debe ser cuadrada');
        abort;
    end;
    
    L = zeros(n, n);
    U = eye(n, n);
    
    L(:,1) = A(:,1);
    U(1,:) = A(1,:) / L(1,1);
    for k = 2:n
        L(k:n,k) = A(k:n,k) - L(k:n,1:k-1) * U(1:k-1,k);
        for j = k+1:n
            U(k,j) = (A(k,j) - L(k,1:j-1) * U(1:j-1,j)) / L(k,k);
        end
    end
endfunction

function [Q, R] = QR(A)
    [n, m] = size(A);
    if n < m then
        error('QR - La matriz A no cumple con las dimensiones');
        abort;
    end
    R(1,1) = norm(A(:,1), 2);
    Q(:,1) = A(:,1) / R(1,1);
    for k = 2:n
        Q(:,k) = A(:,k);
        for i = 1:k-1
            R(i, k) = A(:,k)' * Q(:,i)
            Q(:,k) = Q(:,k) - R(i, k) * Q(:,i);
        end
        R(k,k) = norm(Q(:,k), 2);
        Q(:,k) = Q(:,k) / R(k,k);
    end
endfunction

function [U,ind] = cholesky(A)
// Factorización de Cholesky.
// Trabaja únicamente con la parte triangular superior.
//
// ind = 1  si se obtuvo la factorización de Cholesky.
//     = 0  si A no es definida positiva
//
//******************
eps = 1.0e-8
//******************

n = size(A,1)
U = zeros(n,n)

t = A(1,1)
if t <= eps then
    printf('Matriz no definida positiva.\n')
    ind = 0
    return
end
U(1,1) = sqrt(t)
for j = 2:n
    U(1,j) = A(1,j)/U(1,1)
end
    
for k = 2:n
    t = A(k,k) - U(1:k-1,k)'*U(1:k-1,k)
    if t <= eps then
        printf('Matriz no definida positiva.\n')
        ind = 0
        return
    end
    U(k,k) = sqrt(t)
    for j = k+1:n
        U(k,j) = ( A(k,j) - U(1:k-1,k)'*U(1:k-1,j) )/U(k,k)
    end
end
ind = 1

endfunction

function x = solve_chol(A, b)
    R = chol(A);
    y = solve_lower(R', b);
    x = solve_upper(R, y);
endfunction

function x = solve_QR(A, b)
    [Q, R] = QR(A);
    x = solve_upper(R, Q' * b);
endfunction
