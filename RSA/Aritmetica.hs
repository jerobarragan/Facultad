module Aritmetica where
import Tipos
import Data.Tuple
import Data.Bits


--(1)
mcdExt :: Integer -> Integer -> (Integer, (Integer, Integer))
mcdExt a 0 = (a,(1,0))
mcdExt a b = (d,(t,s-t*k))
          where (k,r) = (div a b, mod a b)
                (d,(s,t)) = mcdExt b r 

--(2)
criba :: Integer -> Set Integer
criba n | n <= 0 = undefined
        | otherwise = cribaAux n 2

cribaAux :: Integer -> Integer -> Set Integer
cribaAux n p | p >= n = []
             | otherwise = p:(cribaAux n (minimoPrimoDesde(p+1)))

minimoPrimoDesde :: Integer -> Integer
minimoPrimoDesde n | esPrimo n = n
                   | otherwise = minimoPrimoDesde (n+1)

esPrimo :: Integer -> Bool
esPrimo n = esPrimoAux n 2

esPrimoAux :: Integer -> Integer -> Bool 
esPrimoAux n k | k == n = True
               | mod n k == 0 = False 
               | otherwise = esPrimoAux n (k+1)
--(3)
coprimoCon:: Integer -> Integer
coprimoCon n | n <= 2 = undefined
             | otherwise = coprimoConAux n (n-2)

coprimoConAux :: Integer -> Integer -> Integer
coprimoConAux n m | m == 1 = undefined {- Devuelve undefined si no existe m tal que n coprimo con n y 1 < m < (n-1) -}
                  | sonCoprimos n m = m
                  | otherwise = coprimoConAux n (m-1)

sonCoprimos :: Integer -> Integer -> Bool
sonCoprimos a b = mcd a b == 1

--Rehicimos el mcd con pattern matching.
mcd :: Integer -> Integer -> Integer
mcd 0 0 = undefined
mcd 0 b = b 
mcd a 0 = a 
mcd a b | a >= b = mcd (mod a b) b 
        | otherwise = mcd a (mod b a)

--(4)
inversoMultiplicativo:: Integer -> Integer -> Integer
inversoMultiplicativo n m | not (sonCoprimos n m) = undefined
                          | otherwise = mod x m 
                          where (d,(x,y)) = mcdExt n m


-- Función de regalo para exponenciar "rápido"
modExp :: Integer -> Integer -> Integer -> Integer
modExp b 0 m = 1
modExp b e m = t * modExp ((b * b) `mod` m) (shiftR e 1) m `mod` m
  where t = if testBit e 0 then b `mod` m else 1
