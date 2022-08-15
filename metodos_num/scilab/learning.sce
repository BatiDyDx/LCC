function y = power(f, x, k, n)
    if n == 0 then
        y = x
    else
        y = f(power(f, x, k, n - 1), k)
    end
endfunction

function y = f(x, k) // Ackermann succesion functions
    if k == 0 then
        y = x + 1
    else
        y = power(f, x, k-1, x + 2)
    end
endfunction

function y = ack(x)
    y = f(x, x)
endfunction

function y = derivate(f, x, h, n)
    if n == 0 then
        deff('y = F(x)', 'y = ' + f)
        y = F(x)
    else
        y = (derivate(f, x + h, h, n - 1) - derivate(f, x, h, n - 1)) / h
    end
endfunction

function p = char_poly(A)
    s = size(A)(1)
    y = poly(0, 'x')
    i = eye(s, s)
    p = det(A - y * i)
endfunction

function eig_values = get_eigen_values(A)
    p = char_poly(A)
    eig_values = unique(roots(p))
endfunction

function eig_vectors = get_eigen_vectors(A)
    vals = get_eigen_values(A)
    I = eye(size(A)(1), size(A)(1))
    eig_vectors = [ ]
    k = 1
    for i = [1:size(vals)(2)]
        m = kernel(A - vals(i) * I)
        for j = [1:size(m)(1)]
            eig_vectors(k) = m(:,j)
            k = k + 1
        end
    end
endfunction
