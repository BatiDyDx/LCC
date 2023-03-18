// Ejercicio 1
x = [0.0 0.2 0.4 0.6];
y = [1.0 1.2214 1.4918 1.8221];

printf("Aproximacion de e ** (1/3) mediante interpolacion lineal y cubica\n");
p = 1/3;

printf("Interpolacion lineal\n");
disp("Polinomio de Lagrange: ", lagrange(p, x(2:3), y(2:3)));
disp("Diferencias divididas: ", interpolate_DD(p, x(2:3), y(2:3)));

printf("Interpolacion cubica\n");
disp("Polinomio de Lagrange: ", lagrange(p, x, y));
disp("Diferencias divididas: ", interpolate_DD(p, x, y));

// Ejercicio 4
x = (2.0:0.1:2.5)';
y = [0.2239, 0.1666, 0.1104, 0.0555, 0.0025, -0.0484];

eps = 1; // |J_0(x)| <= 1
p = interpolation_poly(x, y);
printf("Interpolacion en 2.15: %lf\n", horner(p, 2.15));
printf("Interpolacion en 2.35: %lf\n", horner(p, 2.35));
printf("Error maximo cometido (p = 2.15): %.10lf\n", interpolation_error(2.15, x, eps));
printf("Error maximo cometido (p = 2.35): %.10lf\n", interpolation_error(2.35, x, eps));


// Ejercicio 7
x = [0 0.15 0.31 0.5 0.6 0.75]';
y = [1 1.004 1.31 1.117 1.223 1.422]';

// Minimos cuadrados lineal
p1 = min_squares_poly(x, y, 1);

// Minimos cuadrados cuadratico
p2 = min_squares_poly(x, y, 2);

// Minimos cuadrados cubico
p3 = min_squares_poly(x, y, 3);

printf("Error de la aproximacion lineal: %lf\n", sum(abs(y - horner(p1, x))));
printf("Error de la aproximacion cuadratica: %lf\n", sum(abs(y - horner(p2, x))));
printf("Error de la aproximacion cubica: %lf\n", sum(abs(y - horner(p3, x))));

// Ejercicio 8
x = [4 4.2 4.5 4.7 5.1 5.5 5.9 6.3 6.8 7.1]';
y = [102.56 113.18 130.11 142.05 167.53 195.14 224.87 256.73 299.5 326.72]';

p1 = min_squares_poly(x, y, 1);
p2 = min_squares_poly(x, y, 2);
p3 = min_squares_poly(x, y, 3);

function ej8()
    xaxis = linspace(x(1), x(10), 500)';
    // Nota: La aproximacion de orden 2 y 3 son casi indistinguibles sin zoom
    plot2d(xaxis, [horner(p1, xaxis), horner(p2, xaxis), horner(p3, xaxis)]);
    scatter(x, y);
endfunction


// Ejercicio 9
function ej9(n)
    a = -5; b = 5;
    deff("y = f(x)", "y = 1 ./ (1 + x .^ 2)");
    x = linspace(a, b, n)';
    p = interpolation_poly(x, f(x));
    x = linspace(a, b, 1000)';
    y = f(x) - horner(p, x);
    // plot2d(x, [f(x) horner(p, x)])
    plot2d(x, y);
endfunction


// Ejercicio 10
k = 4;
f = "exp(x)";
p = interpolate_chebyshev(f, k);

plot_error(f, p, -1, 1);
x = linspace(-1, 1, 500)';
// plot2d(x, F(x) - horner(p, x));



// Ejercicio 11
a = 0; b = %pi/2;
n = 3;

g = "cos(x)";
x = raices_chebyshev(4);
for j = 1:4 do
    x(j) = ((b + a) + x(j) * (b - a)) / 2;
    y(j) = cos(x(j));
end

p = interpolation_poly(x, y);
