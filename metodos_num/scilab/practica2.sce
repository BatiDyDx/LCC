// Ejercicio 1
// Metodo robusto de calculo de raices cuadraticas
function r = raices_robusto(p)
    a = coeff(p, 2)
    b = coeff(p, 1)
    c = coeff(p, 0)
    delta = b ** 2 - 4 * a * c
    if b < 0 then
        r(1) = (-b + sqrt(delta)) / (2 * a)
        r(2) = (2 * c) / (-b - sqrt(delta))
    else
        r(1) = (2 * c) / (-b - sqrt(delta))
        r(2) = (-b - sqrt(delta)) / (2 * a)
    end
endfunction

// Ejercicio 3 b)
// Algoritmo de Horner
function y = horner_algo(p, x)
    k = degree(p)
    y = coeff(p, k)
    while k > 0
        k = k - 1
        y =  y * x + coeff(p, k)
    end
endfunction

// Ejercicio 3 c)
// Algoritmo de Horner generalizado
// Evalua polinomio y derivada en x
function v = horner_derivative(p, x)
    k = degree(p)
    v(1) = coeff(p, k)
    v(2) = 0
    while k > 0
        if k == degree(p)
            v(2) = coeff(p, k)
        else
            v(2) = v(2) * x + v(1)
        end
        k = k - 1
        v(1) = v(1) * x + coeff(p, k)
    end
endfunction

function y = derivate(f, x, h, n)
    if n == 0 then
        deff('y = F(x)', 'y = ' + f)
        y = F(x)
    else
        y = (derivate(f, x + h, h, n - 1) - derivate(f, x, h, n - 1)) / h
    end
endfunction

function y = taylor(f, x, n)
    y = 0
    for k = (0:n)
        y = y + (derivate(f, 0, 0.0001, k) / factorial(k)) * x ** k
    end
endfunction
