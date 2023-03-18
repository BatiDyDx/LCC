function T = chebyshev(n)
    s = poly(0, "x", "r");
    T0 = poly(1, "x", "c");
    T1 = s
    T = T0;
    for k = 1:n
        T0 = T1;
        T1 = 2 * s * T0 - T;
        T = T0;
    end
endfunction

function x = chebyshev_roots(n)
    if n == 0 then
        return [];
    end
    for k = 1:n do
        theta = (2 * k - 1) * %pi / (2 * n);
        x(k) = cos(theta);
    end
endfunction

function x = chebyshev_roots_general(a, b, n)
    x = chebyshev_roots(n);
    x = ((b + a) + x * (b - a)) / 2;
endfunction

function p = interpolate_chebyshev(f, n)
    deff("y = F(x)", "y = " + f);
    x = chebyshev_roots(n);
    y = zeros(n, 1);
    for k = 1:n do
        y(k) = F(x(k));
    end
    p = interpolation_poly(x, y);
endfunction

// Coeficienets de aproximacion de minimos cuadrados de orden n
function a = min_squares(x, y, k)
    n = length(x);
    A = ones(n, 1);
    for j = 2:k+1 do
        A(1:n,j) = A(1:n,j-1) .* x;
    end
    if n == k+1 then
        a = solve_QR(A, y);
    else
        a = solve(A' * A, A' * y, %t);
    end
endfunction

// Polinomio obtenido de la aproximacion de minimos cuadrados de orden n
function p = min_squares_poly(x, y, k)
    a = min_squares(x, y, k);
    p = poly(a, "x", "c");
endfunction

// f es string y p es polinomio
function plot_error(f, p, a, b)
    deff("y = F(x)", "y = " + f);
    x = linspace(a, b, 500);
    plot2d(x, F(x) - horner(p, x));
endfunction
