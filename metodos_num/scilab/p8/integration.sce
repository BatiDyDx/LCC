
// Metodos de integracion numerica
// Metodo del trapecio simple
function w = trapecio(a, b, f)
    deff("y = F(x)", "y = " + f);
    w = (F(a) + F(b)) * (b - a) / 2;
endfunction

// Metodo del trapecio compuesto
function w = trapecio_compuesto(a, b, f, n)
    deff("y = F(x)", "y = " + f);
    h = (b - a) / n;
    w = 0;
    for j = 1:n-1 do
        xj = a + j * h;
        w = w + F(xj);
    end
    w = h * (0.5 * (F(a) + F(b)) + w);
endfunction

// Metodo de Simpson
function w = simpson(a, b, f)
    deff("y = F(x)", "y = " + f);
    h = (b - a) / 2;
    c = a + h; // c = (a + b) / 2
    w = (h / 3) * (F(a) + 4 * F(c) + F(b));
endfunction

// Metodo de Simpson compuesto
function w = simpson_compuesto(a, b, f, n)
    deff("y = F(x)", "y = " + f);
    h = (b - a) / n;
    w = 0;
    for j = 1:n-1 do
        xj = a + j * h;
        if modulo(j, 2) == 1 then
            w = w + 4 * F(xj);
        else
            w = w + 2 * F(xj);
        end
    end
    w = (h / 3) * (F(a) + F(b) + w);
endfunction

