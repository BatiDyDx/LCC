
function c = biseccion(fun, a, b, tol)
    fa = fun(a);
    fb = fun(b);
    if fa * fb >= 0 then error("Intervalo invalido") end
    c = (a + b) / 2;
    while (b - c > tol)
        fc = fun(c);
        if fb * fc < 0 then
            a = c;
            fa = fc;
        else
            b = c;
            fb = fc;
        end
        c = (a + b) / 2;
    end
endfunction

function y = newton(fun, x0, tol, iter_max)
    
endfunction

function y = regula_falsi(fun, tol)
  y = 0;
  error("No implementado");
endfunction
