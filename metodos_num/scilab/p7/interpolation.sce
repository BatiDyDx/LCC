// Ejercicio 1 de la práctica 7
// Polinomio interpolador de Lagrange
function w = lagrange(p,x,y)
    w = 0
    n = length(x)
    for i=1:n do
        w = w + L(p,i,x) * y(i)
    end
endfunction

// Función L_i(x) del polinomio interpolador de Lagrange
function w = L(p,i,x)
    w = 1
    n = length(x)
    for j=1:n do
        if j<>i then
            w = w*(p-x(j))/(x(i)-x(j))
        end
    end
endfunction

// Polinomio de interpolacion mediante diferencias divididas
function z = interpolate_DD(p, x, y)
    n = length(x);
    z = DD(x,y);
    for k = n-1:-1:1
        z = z * (p - x(k)) + DD(x(1:k), y(1:k));
    end
endfunction

// Diferencias divididas de Newton
function w = DD(x,y)
    n = length(x)
    if n == 1 then
        w = y(1);
    elseif n == 2 then
        w = (y(2)-y(1))/(x(2)-x(1));
    else
        w = (DD(x(2:n),y(2:n))-DD(x(1:n-1),y(1:n-1)))/(x(n)-x(1))
    end
endfunction

function p = interpolation_poly(x, y)
    n = length(x);
    p = poly(0, "x");
    z = DD(x,y);
    for k = n-1:-1:1
        z = z * (p - x(k)) + DD(x(1:k), y(1:k));
    end
endfunction

// Acotacion del error del polinomio de interpolacion
// p es el punto donde se interpola, x son los nodos y
// eps = max |f^(n)(x)| con n = cant. de nodos
function s = interpolation_error(p, x, eps)
    n = length(x);
    s = (prod(p * ones(n,1) - x) * eps) / factorial(n);
endfunction
