function x = jacobi(A, b, x0, tol, iters)
    n = size(A, 1)
    x(1) = (b(1) - A(1,2:n) * x0(2:n)) / A(1,1)
    for i = 2:n-1
        x(i) = (b(i) - A(i,1:i-1) * x0(1:i-1) - A(i,i+1:n) * x0(i+1:n)) / A(i,i)
    end
    x(n) = (b(n) - A(n,1:n-1) * x0(1:n-1)) / A(n,n)
    m = 0
    while norm(x - x0, 2) > tol && m < iters
        x0 = x
        x(1) = (b(1) - A(1,2:n) * x0(2:n)) / A(1,1)
        for i = 2:n-1
            x(i) = (b(i) - A(i,1:i-1) * x0(1:i-1) - A(i,i+1:n) * x0(i+1:n)) / A(i,i)
        end
        x(n) = (b(n) - A(n,1:n-1) * x0(1:n-1)) / A(n,n)
        m = m + 1
    end
    if m == iters then
        disp("Numero de iteraciones excedido");
    end
    disp("Numero de iteraciones", m);
endfunction

function x = gauss_seidel(A, b, x0, tol, iters)
    n = size(A, 1)
    s = zeros(n, 1)
    x = x0
    x(1) = (b(1) - A(1,2:n) * x(2:n)) / A(1,1);
    for i = 2:n-1
        x(i) = (b(i) - A(i,1:i-1) * x(1:i-1) - A(i,i+1:n) * x(i+1:n)) / A(i,i);
    end
    x(n) = (b(n) - A(n,1:n-1) * x(1:n-1)) / A(n,n);
    m = 0
    while norm(x - x0, 2) > tol && m < iters
        x0 = x
        x(1) = (b(1) - A(1,2:n) * x(2:n)) / A(1,1);
        for i = 2:n-1
            x(i) = (b(i) - A(i,1:i-1) * x(1:i-1) - A(i,i+1:n) * x(i+1:n)) / A(i,i);
        end
        x(n) = (b(n) - A(n,1:n-1) * x(1:n-1)) / A(n,n);
        m = m + 1
    end
    if m == iters then
        disp("Numero de iteraciones excedido");
    end
    disp("Numero de iteraciones", m);
endfunction

// Chequea si las condiciones de para la convergencia de los metodos iterativos
// de Jacobi y Gauss-Seidel se cumplen
function [b1, b2] = check_conditions_convergence(A, p)
    n = size(A, 1);
    N1 = diag(diag(A));
    disp(N1)
    N2 = zeros(n,n);
    N2(:,1) = A(:,1)
    for k = 2:n
        N2(k:n,k) = A(k:n,k);
    end
    disp(N2)
    b1 = norm(eye(n,n) - (N1 ** -1) * A, p) < 1;
    b2 = norm(eye(n,n) - (N2 ** -1) * A, p) < 1;
endfunction

function x = SOR(A, b, x0, w, tol, iters)
    n = size(A, 1)
    s = zeros(n, 1)
    x = x0
    x(1) = (1 - w) * x0(1) + (b(1) - A(1,2:n) * x0(2:n)) * (w / A(1,1));
    for i = 2:n-1
        x(i) = (1 - w) * x0(i) + (b(i) - A(i,1:i-1) * x(1:i-1) - A(i,i+1:n) * x(i+1:n)) * (w / A(1,1));
    end
    x(n) = (1 - w) * x0(n) + (b(n) - A(n,1:n-1) * x(1:n-1)) * (w / A(n,n));
    m = 0
    while norm(x - x0, 2) > tol && m < iters
        x0 = x
        x(1) = (1 - w) * x0(1) + (b(1) - A(1,2:n) * x0(2:n)) * (w / A(1,1));
        for i = 2:n-1
            x(i) = (1 - w) * x0(i) + (b(i) - A(i,1:i-1) * x(1:i-1) - A(i,i+1:n) * x(i+1:n)) * (w / A(1,1));
        end
        x(n) = (1 - w) * x0(n) + (b(n) - A(n,1:n-1) * x(1:n-1)) * (w / A(n,n));
        m = m + 1
    end
    if m == iters then
        disp("Numero de iteraciones excedido");
    end
    disp("Numero de iteraciones", m);
endfunction
