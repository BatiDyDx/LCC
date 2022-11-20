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
printf("Error maximo cometido (p = 2.15): %lf\n", interpolation_error(2.15, x, eps));
printf("Error maximo cometido (p = 2.35): %lf\n", interpolation_error(2.35, x, eps));


// Ejercicio 7
x = [0 0.15 0.31 0.5 0.6 0.75]';
y = [1 1.004 1.31 1.117 1.223 1.422]';

// Minimos cuadrados lineal
a1 = linear_min_squares(x,y);

// Minimos cuadrados cuadratico
a2 = square_min_squares(x,y);

// Minimos cuadrados cubico
a3 = cube_min_squares(x,y);

// Funciones de minimos cuadrados obtenidas
deff("y = f1(x)", "y = a1(1) + a1(2) * x");
deff("y = f2(x)", "y = a2(1) + a2(2) * x + a2(3) * x .^ 2");
deff("y = f3(x)", "y = a3(1) + a3(2) * x + a3(3) * x .^ 2 + a3(4) * x .^ 3");

printf("Error de la aproximacion lineal: %lf\n", sum(abs(y - f1(x))));
printf("Error de la aproximacion cuadratica: %lf\n", sum(abs(y - f2(x))));
printf("Error de la aproximacion cubica: %lf\n", sum(abs(y - f3(x))));

// Ejercicio 8
x = [4 4.2 4.5 4.7 5.1 5.5 5.9 6.3 6.8 7.1]';
y = [102.56 113.18 130.11 142.05 167.53 195.14 224.87 256.73 299.5 326.72]';

a1 = linear_min_squares(x,y);
a2 = square_min_squares(x,y);
a3 = cube_min_squares(x,y);


// Ejercicio 9
deff("y = f(x)", "y = 1 ./ (1 + x .^ 2)");
n = [2 4 6 10 14]';

a = -5; b = 5;
for j = 1:length(n) do
    x = linspace(a, b, n(j));
    p = interpolation_poly(x, f(x));
    x = linspace(a, b, 1000);
    y = zeros(1000, 1); // vector de errores: y = f(x) - p(x)
    for i = 1:1000 do
        y(i) = f(x(i)) - horner(p, x(i));
    end
    plot2d(x, y);
end

