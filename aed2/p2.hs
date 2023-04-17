zip3' :: [a] -> [b] -> [c] -> [(a,b,c)]
zip3' [] _ _ = []
zip3' _ [] _ = []
zip3' _ _ [] = []
zip3' (x:xs) (y:ys) (z:zs) = (x,y,z) : zip3' xs ys zs

zip3'' :: [a] -> [b] -> [c] -> [(a,b,c)]
zip3'' xs ys zs = map join (zip (zip xs ys) zs)
                  where join ((x, y), z) = (x, y, z)

{- Implementacion copada
zip3'' :: [a] -> [b] -> [c] -> [(a,b,c)]
zip3'' xs ys zs = apply (map join (zip xs ys)) zs
               where join (x, y) z = (x, y, z)
                     apply fs xs = case xs of
                                     [] -> []
                                     (x:xs) -> case fs of
                                                 [] -> []
                                                 (f:fs) -> (f x) : apply fs xs
-}

type NumBin = [Bool]

sumBin [] ys = ys
sumBin xs [] = xs
sumBin (x:xs) (y:ys) | x && y = let zs = sumBin ys [True] in False : sumBin xs zs
                     | x || y = True : sumBin xs ys
                     | otherwise = False : sumBin xs ys

prodBin :: NumBin -> NumBin -> Numbin
prodBin 

div2Bin :: NumBin -> NumBin
div2Bin = tail

mod2Bin :: NumBin -> NumBin
mod2Bin ns = [head ns]

-- Le agrego show para verificar mas rapido los resultados
printBin :: NumBin -> String
printBin [] = []
printBin (b:bs) = let c = if b then '1' else '0' in c : printBin bs


-- Ejercicio 13
divisors :: Integral a => a -> [a]
divisors n = [k | k <- [2..n], (mod n k) == 0 ]

matches :: (Num a, Eq a) => a -> [a] -> [a]
matches n ms = [k | k <- ms, k == n]

cuadruplas :: (Integral a, Eq a) => a -> [(a, a, a, a)]
cuadruplas n = [(x,y,z,w) | x <- ns, y <- ns, z <- ns, w <- ns, (x ^ 2) + (y ^ 2) == (z ^ 2) + (w ^ 2)]
               where ns = [1..n]

unique :: (Num a, Eq a) => [a] -> [a]
unique [] = []
unique (x:xs) = x : filter (/= x) (unique xs)

-- Ejercicio 14
scalarProduct :: Num a => [a] -> [a] -> a
scalarProduct xs ys = sum [x * y | (x, y) <- zip xs ys]


