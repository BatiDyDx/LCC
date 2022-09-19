
function l = wave_length(tol)
    d = 1;
    h = 4;
    T = 5;
    l0 = 2 * %pi / d;
    g = 9.8;
    lambda = 0.7;
    l1 = T ** 2 * g * tanh(h * d) / (2 * %pi);
    n = ceil(log(tol * (1 - lambda) / abs(l1 - l0)) / log(lambda));
    i = 2;
    while i <= n
        l1 = T ** 2 * g * tanh(h * 2 * %pi / l1) / (2 * %pi);
        i = i + 1;
    end
    l = l1;
endfunction

function [x, y] = ej10(v0, iters)
    deff("z = f1(x,y)", "z = 1 + x ** 2 - y ** 2 + (%e ** x) * cos(y)");
    deff("z = f2(x,y)", "z = 2 * x * y + (%e ** x) * sin(y)");
    deff("z = f1x(x,y)", "z = 2 * x + (%e ** x) * cos(y)");
    deff("z = f1y(x,y)", "z = -2 * y - (%e ** x) * sin(y)");
    x0 = v0(1);
    y0 = v0(2);
    i = 1;
    dx = f1x(x0, y0);
    dy = f1y(x0, y0);
    J = [
          dx, dy;
         -dy, dx
        ];
    v1 = v0 - (J ** -1) * [f1(x0, y0); f2(x0, y0)];
    while i < iters
        i = i + 1;
        x1 = v1(1);
        y1 = v1(2);
        dx = f1x(x1, y1);
        dy = f1y(x1, y1);
        J = [
                dx, dy;
               -dy, dx // f2_x = -f1_y y f2_y = f1_x
            ];
        v1 = v1 - (J ** -1) * [f1(x1, y1); f2(x1, y1)];
    end
    x = v1(1);
    y = v1(2);
endfunction

function [x, y] = ej10(v0, tol, iter_max)
    deff("z = f1(x,y)",  "z = x ** 2 + x * y ** 3 - 9");
    deff("z = f2(x,y)",  "z = 3 * (x ** 2) * y  - 4 - y ** 3");
    deff("z = f1x(x,y)", "z = 2 * x + y ** 3");
    deff("z = f1y(x,y)", "z = 3 * x * y ** 2");
    deff("z = f2x(x,y)", "z = 6 * x * y");
    deff("z = f2y(x,y)", "z = 3 * x ** 2 -3 * y ** 2");
    x0 = v0(1);
    y0 = v0(2);
    i = 1;
    J = [
          f1x(x0, y0), f1y(x0, y0);
          f2x(x0, y0), f2y(x0, y0)
        ];
    v1 = v0 - (J ** -1) * [f1(x0, y0); f2(x0, y0)];
    while norm(v1 - v0) > tol && i < iter_max
        i = i + 1;
        v0 = v1;
        x0 = v0(1);
        y0 = v0(2);
        J = [
                f1x(x0, y0), f1y(x0, y0);
                f2x(x0, y0), f2y(x0, y0)
            ];
        v1 = v0 - (J ** -1) * [f1(x0, y0); f2(x0, y0)];
    end
    if i == iter_max then
        disp("Numero de iteraciones maximas alcanzadas");
    end
    x = v1(1);
    y = v1(2);
endfunction

function [x, y] = ej11(iter_max)
    v0 = [1; 1];
    tol = 10 ** -12;
    deff("z = fx(v)", "z = 2 + 4 * v(1) * %e ** (2 * v(1) ** 2 + v(2) ** 2)");
    deff("z = fy(v)", "z = 6 * v(2) + 2 * v(2) * %e ** (2 * v(1) ** 2 + v(2) ** 2)")
    deff("z = gradf(v)", "z = [ fx(v); fy(v) ]");
    J = numderivative(gradf, v0);
    v1 = v0 - (J  ** -1) * gradf(v0);
    i = 1;
    while norm(v1 - v0) ** 2 > tol && i < iter_max
        i = i + 1;
        v0 = v1;
        J = numderivative(gradf, v0);
        v1 = v0 - (J  ** -1) * gradf(v0);
    end
    x = v1(1);
    y = v1(2);
endfunction

function b = ej11_chequear_condicion()
    [x, y] = ej11(50);
    deff("z = f(v)", "z = 2 * v(1) + 3 * v(2) ** 2 + %e ** (2 * v(1) ** 2 + v(2) ** 2)");
    [_, H] = numderivative(f, [x, y], 10 ** -5, 1, "blockmat");
    b = definida_positiva(H);
endfunction

// Retorna True si A es definida positiva
function b = definida_positiva(A)
    b = A(1, 1) > 0 && det(A) > 0;
endfunction

// Ejercicio 12
function [k1, k2, k3] = ej12_a()
    deff("y = f1(k)", "y = k(1) * %e ** k(2) + k(3) - 10");
    deff("y = f2(k)", "y = k(1) * %e ** (k(2) * 2) + k(3) * 2 - 12");
    deff("y = f3(k)", "y = k(1) * %e ** (k(2) * 3) + k(3) * 3 - 15");
    deff("y = f(k)", "y = [f1(k); f2(k); f3(k)]");
    /*for i = 1:3
        deff("y = f" + string(i) + "(k)", "y = k(1) * %e ** (k(2) * r(" + string(i) + "
    end*/
    v0 = [ 1; 2; 3 ];
    i = 0;
    tol = 10 ** -10;
    J = numderivative(f, v0);
    v1 = v0 - (J ** -1) * f(v0);
    while norm(v1 - v0) > tol && i < 100
        i = i + 1;
        v0 = v1;
        J = numderivative(f, v0);
        v1 = v0 - (J ** -1) * f(v0);
    end
    k1 = v1(1);
    k2 = v1(2);
    k3 = v1(3);
endfunction

function r = ej12_b()
    [k1 k2 k3] = ej12_a();
    deff("y = f(r)", "y = %pi * r ** 2 * (" + string(k1) + " * %e ** (" + string(k2) + "* r) + " + string(k3) + " * r) - 500");
    // f(r) = pi * r^2 * (k1 * e^(k2 * r) + k3 * r) - 500
    tol = 10 ** -8;
    i = 0;
    iter_max = 100;
    r0 = 1;
    r1 = r0 - f(r0) / numderivative(f, r0);
    while abs(r1 - r0) > tol && i < iter_max
        i = i + 1;
        r0 = r1;
        r1 = r1 - f(r1) / numderivative(f, r1);
    end
    r = r1;
endfunction
