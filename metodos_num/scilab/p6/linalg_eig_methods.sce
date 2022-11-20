
function circ(r,x,y)
    xarc(x-r,y+r,2*r,2*r,0,360*64)
endfunction

// Retorna las dimensiones del rectangulo a dibujar
function [mx, my, Mx, My] = gers(A)
    [n,m] = size(A);
    centros = diag(A);
    radios = sum(abs(A),'c') - abs(centros) ;
    
    // buscamos calcular un rectángulo que contenga a todos los circulos
    // esquina inferiro izquierda
    
    mx = round (min(centros - radios)-1);
    my = round (min(-radios)-1);
    
    // esquina superior derecha
    
    Mx = round(max(centros+radios)+1);
    My = round(max(radios)+1);
    
    rectangulo = [mx my Mx My];
    
    for i=1:n
        circ(radios(i),centros(i),0)
    end
    
endfunction

function CircGersValor(A)
    [mx my Mx My] = gers(A);
    // dibujamos los autovalores
    plot2d(real(spec(A)),imag(spec(A)),-1,"031","", [mx my Mx My])
    replot([mx my Mx My]);
    xgrid();
endfunction

function [lambda, z] = power_method(A, z0, tol, iters)
    w = A * z0;
    z = w / norm(w, %inf);
    i = 0;
    while norm(z - z0, 2) > tol && i < iters
        i = i + 1;
        z0 = z;
        w = A * z0;
        z = w / norm(w, %inf);
    end
    for k = 1:size(z0,1)
        if w(k) <> 0 && z0(k) <> 0 then
            lambda = w(k) / z0(k);
            break;
        end;
    end
    if i == iters then
        printf("Numero de iteraciones maximas alcanzado");
    end
    disp("Numero de iteraciones: ", i);
endfunction

// Ejercicio 5
// Compara el mayor autovalor de una matriz con
// el obtenido por el metodo de la potencia
function ej5(A)
    l = max(abs(spec(A))); // Mayor autovalor
    l1 = power_method(A, ones(size(n,1),1), 10 ** -8, 1000);
    disp("Mayor autovalor: ", l);
    disp("Autovalor obtenido por metodo de la potencia", l1);
    disp("Distancia: ", abs(l - l1));
endfunction
