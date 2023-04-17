-- Practica 3

-- Ejercicio 1
type Color = (Int, Int, Int)

mezclar :: Color -> Color -> Color
mezclar (r1, g1, b1) (r2, g2, b2) = (mid r1 r2, mid g1 g2, mid b1 b2)
                                    where mid x y = (x + y) `div` 2

-- Ejercicio 2
type Linea = (String, Int)

vacia :: Linea
vacia = ([], 0)

moverIzq :: Linea -> Linea
moverIzq (s, p) = let p' = if p > 0 then p - 1 else 0 in (s, p')

moverDer :: Linea -> Linea
moverDer (s, p) = let p' = if p' < length s then p + 1 else p in (s, p')

moverIni :: Linea -> Linea
moverIni (s, _) = (s, 0)

moverFin :: Linea -> Linea
moverFin (s, _) = (s, length s)

insertar :: Char -> Linea -> Linea
insertar c (s, p) = (take p s ++ [c] ++ drop p s, p + 1)

borrar :: Linea -> Linea
borrar (s, 0) = (s, 0)
borrar (s, p) = (take (p - 1) s ++ drop p s, p - 1)

-- Ejercicio 3
data CList a = EmptyCL | CUnit a | Consnoc a (CList a) a
               deriving Show

-- a)
headCL :: CList a -> a
headCL (CUnit x) = x
headCL (Consnoc x _ _) = x

tailCL :: CList a -> CList a
tailCL (CUnit _) = EmptyCL
tailCL (Consnoc _ l _) = l

isEmptyCL :: CList a -> Bool
isEmptyCL EmptyCL = True
isEmptyCL _ = False

isCUnit :: CList a -> Bool
isCUnit (CUnit _) = True
isCUnit _ = False

-- b)
reverseCL' :: CList a -> CList a -> CList a
reverseCL' prev EmptyCL = prev
reverseCL' prev (Consnoc x next y) = reverseCL' (Consnoc x prev y) next

reverseCL :: CList a -> CList a
reverseCL = reverseCL' EmptyCL


-- Ejercicio 4

data Exp = Lit Int | Add Exp Exp | Sub Exp Exp | Prod Exp Exp | Div Exp Exp
           deriving Show

eval :: Exp -> Int
eval (Lit n) = n
eval (Add e1 e2) = eval e1 + eval e2
eval (Sub e1 e2) = eval e1 - eval e2
eval (Prod e1 e2) = eval e1 * eval e2
eval (Div e1 e2) = eval e1 `div` eval e2

-- Ejercicio 5
type Token = (String, String)

nextToken :: String -> Token
nextToken [] = ([], [])
nextToken (c:s) | c == ' '  = ([], s)
                | otherwise = let (tok, s') = nextToken s in (c:tok, s')

isOp :: String -> Bool
isOp "+" = True
isOp "-" = True
isOp "*" = True
isOp "/" = True
isOp  _  = False

parseOp :: Token -> [Exp] -> [Exp]
parseOp (tok, toks) stack
                 | tok == "+" = let e = (Add e1 e2)  in parseRPN' toks' (e:stack')
                 | tok == "-" = let e = (Sub e1 e2)  in parseRPN' toks' (e:stack')
                 | tok == "*" = let e = (Prod e1 e2) in parseRPN' toks' (e:stack')
                 | tok == "/" = let e = (Div e1 e2)  in parseRPN' toks' (e:stack')
                 where toks' = nextToken toks
                       (e2:e1:stack') = stack

parseRPN' :: Token -> [Exp] -> [Exp]
parseRPN' ([], []) stack = stack
parseRPN' (tok, toks) stack = if isOp tok then parseOp (tok, toks) stack
                              else let n = (read tok) :: Int
                                       e = (Lit n) in parseRPN' (nextToken toks) (e:stack)

parseRPN :: String -> Exp
parseRPN s = head (parseRPN' (nextToken s) [])

evalRPN :: String -> Int
evalRPN = eval . parseRPN

-- Ejericio 6
-- a) Las divisiones por 0 no se manejan, causando una excepcion cuando alguna sucede

-- b)

ifJust :: Maybe a -> Maybe b -> (a -> b -> Maybe c) -> Maybe c 
ifJust Nothing _ _ = Nothing
ifJust _ Nothing _ = Nothing
ifJust (Just x) (Just y) op = op x y

seval :: Exp -> Maybe Int
seval (Lit n) = Just n
seval (Add e1 e2)  = ifJust (seval e1) (seval e2) (\x y -> Just (x + y))
seval (Sub e1 e2)  = ifJust (seval e1) (seval e2) (\x y -> Just (x - y))
seval (Prod e1 e2) = ifJust (seval e1) (seval e2) (\x y -> Just (x * y))
seval (Div e1 e2)  = ifJust (seval e1) (seval e2) (\x y -> if y == 0 then Nothing else Just (x `div` y))

