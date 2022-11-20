// Practica 8
// Ejercicio 1

function ej1(a, b, f, I)
    T = trapecio(a, b, f);
    S = simpson(a, b, f);

    disp("f(x) = " + f);
    printf("Valor real: %lf\n", I);
    printf("Aproximacion por trapecio: %lf\n", T);
    printf("Aproximacion por Simpson: %lf\n", S);
    printf("Error con metodo de trapecio %lf\n", abs(I - T));
    printf("Error con metodo de Simpson %lf\n", abs(I - S));
endfunction

// a)
// $\int_1^2{\ln(x)\,dx}$
a = 1; b = 2;
f = "log(x)";
I = (2 * (log(2) - 1)) + 1; // Antiderivada de ln(x): x * ln(x) - x
ej1(a, b, f, I);

// b)
// $\int_0^{0.1}{x^{\frac{1}{3}}\,dx}$

a = 0; b = 0.1;
f = "x ** (1/3)";
I = 0.75 * (0.1) ** (4/3); // Antiderivada de x ** (1/3): 0.75 * x ** (4/3)
ej1(a, b, f, I);

// c)
// $\int_0^{\frac{\pi}{3}}{\sin^2(x)}\,dx}$

a = 0; b = %pi / 3;
f = "sin(x) ** 2";
// Antiderivada de sin^2(x): 0.5 * (x - 0.5 * sin(2x))
I = 0.5 * (b - 0.5 * sin(2 * b)) - 0.5 * (a - 0.5 * sin(2 * a));
ej1(a, b, f, I);


// Ejercicio 2 y 3
function ej2(a, b, f, n)
    Tn = trapecio_compuesto(a, b, f, n);
    I = integrate(f, "x", a, b);
    disp("f(x) = " + f);
    printf("Valor real (aproximado por SciLab): %lf\n", I);
    printf("Valor aproximado por trapecio compuesto: %lf\n", Tn);
    printf("Error cometido: %lf\n", abs(I - Tn));
endfunction

function ej3(a, b, f, n)
    Sn = simpson_compuesto(a, b, f, n);
    I = integrate(f, "x", a, b);
    disp("f(x) = " + f);
    printf("Valor real (aproximado por SciLab): %lf\n", I);
    printf("Valor aproximado por simpson compuesto: %lf\n", Sn);
    printf("Error cometido: %lf\n", abs(I - Sn));
endfunction

// a)
// $\int_1^3{\dfrac{dx}{x}}$
n = 4; a = 1; b = 3;
f = "1/x";
ej2(a, b, f, n);
ej3(a, b, f, n);

// b)
// $\int_0^2{x^3dx}$
n = 4; a = 0; b = 2;
f = "x**3";
ej2(a, b, f, n);
ej3(a, b, f, n);

// c)
// $\int_0^3{x(1 + x^2)^{1/2}dx}$
n = 6; a = 0; b = 3;
f = "x * sqrt(1 + x ** 2)";
ej2(a, b, f, n);
ej3(a, b, f, n);

// d)
// $\int_0^1{\sin(\pi x)dx}$
n = 8; a = 0; b = 1;
f = "sin(%pi * x)";
ej2(a, b, f, n);
ej3(a, b, f, n);

// e)
// $\int_0^{2\pi}{x\sin(x)dx}$
n = 8; a = 0; b = 2 * %pi;
f = "x * sin(x)";
ej2(a, b, f, n);
ej3(a, b, f, n);

// f)
// $\int_0^1{x^2 e^xdx}$
n = 8; a = 0; b = 1;
f = "x ** 2 * exp(x)";
ej2(a, b, f, n);
ej3(a, b, f, n);


// Ejercicio 4
// $I = \int_0^{1.5}{(x + 1)^{-1}dx}$
n = 10; a = 0; b = 1.5;
f = "1 / (x + 1)";
Tn = trapecio_compuesto(a, b, f, n);
Sn = simpson_compuesto(a, b, f, n);
I = 0.9262907;

disp("f(x) = " + f);
printf("Valor aproximado por trapecio compuesto: %lf\n", Tn);
printf("Valor aproximado por simpson compuesto: %lf\n", Sn);
printf("Error absoluto (trapecio): %lf\n", abs(I - Tn));
printf("Error absoluto (simpson): %lf\n", abs(I - Sn));
