// Coeficientes de la funcion f(x) = a1 + a2 * x
// donde f es la mejor aproximacion por minimos cuadrados lineal
function a = linear_min_squares(x, y)
    s0 = length(x);
    s1 = sum(x);
    s2 = sum(x .^ 2);
    
    m0 = sum(y);
    m1 = sum(y .* x);
    C = [s0, s1; s1, s2];
    b = [m0; m1];
    a = solve(C, b, %f); // solve se halla en linalg_direct.sce
endfunction

function a = square_min_squares(x, y)
    s0 = length(x);
    s1 = sum(x);
    s2 = sum(x .^ 2);
    s3 = sum(x .^ 3);
    s4 = sum(x .^ 4);

    m0 = sum(y);
    m1 = sum(y .* x);
    m2 = sum(y .* x .* x);
    C = [s0, s1 s2; s1, s2, s3; s2, s3, s4];
    b = [m0; m1; m2];
    a = solve(C, b, %f);
endfunction

function a = cube_min_squares(x, y)
    s0 = length(x);
    s1 = sum(x);
    s2 = sum(x .^ 2);
    s3 = sum(x .^ 3);
    s4 = sum(x .^ 4);
    s5 = sum(x .^ 5);
    s6 = sum(x .^ 6);
    
    m0 = sum(y);
    m1 = sum(y .* x);
    m2 = sum(y .* (x .^ 2));
    m3 = sum(y .* (x .^ 3));
    
    C = [s0, s1, s2, s3;
         s1, s2, s3, s4;
         s2, s3, s4, s5;
         s3, s4, s5, s6];
    
    b = [m0; m1; m2; m3];
    a = solve(C, b, %f);
endfunction
