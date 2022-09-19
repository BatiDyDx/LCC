
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
        elseif fb * fc > 0
            b = c;
            fb = fc;
        else
            return; // c es raiz
        end
        c = (a + b) / 2;
    end
endfunction

// Numero de iteraciones para el metodo de biseccion dada una cota de error
function k = iteraciones_biseccion(a, b, err)
    k = ceil(log2((b - a) / err));
endfunction

function y = newton(fun, x0, tol, iter_max)
    x1 = x0 - fun(x0) / numderivative(fun, x0);
    i = 1;
    while abs(x1- x0) > tol && i < iter_max
        x0 = x1; // x0 corresponde a x_i
        x1 = x1 - fun(x1) / numderivative(fun, x1); // x1 corresponde a x_(i+1)
        i = i + 1;
    end
    if i == iter_max then
        disp("Numero de iteraciones maximas alcanzado");
    end
    printf("Numero de iteraciones: %d\n", i);
    y = x1;
endfunction

function c = secante(fun, a, b, tol, iter_max)
    fb = fun(b);
    c = b - fb * (b - a) / (fb - fun(a));
    i = 1;
    while abs(b - c) > tol && i < iter_max
        a = b; // a = x_i
        b = c; // b = x_(i+1)
        fb = fun(b)
        c = b - fb * (b - a) / (fb - fun(a)); // c = x_(i+2)
        i = i + 1;
    end
    if i == iter_max then
        disp("Numero de iteraciones maximas alcanzado");
    end
    printf("Numero de iteraciones: %d\n", i);
endfunction

function c = regula_falsi(fun, a, b, tol)
  fa = fun(a);
  fb = fun(b);
  if fa * fb >= 0 then error("Intervalo invalido") end
  
  i = 1;
  c = b - fb * (b - a) / (fb - fun(a));
  fc = fun(c);

  while abs(b - c) > tol
    if fc == 0 then
      return; // c es raiz de f
    elseif fa * fc < 0 then
      b = c;
      fb = fc;
    else
      a = c;
      fa = fc;
    end
    c = b - fb * (b - a) / (fb - fun(a));
    fc = fun(c);
    i = i + 1;
  end
  printf("Numero de iteraciones: %d\n", i);
endfunction
