module RSA where
import Tipos
import Aritmetica


--(3)
claves :: Integer -> Integer -> (Integer, Integer, Integer)
claves p q | not (esPrimo p && esPrimo q) = undefined
           | otherwise = (e, d, n)
  where m = (p-1)*(q-1)
        n = p*q
        e = coprimoCon m  
        d = inversoMultiplicativo e m

--(6)
codificador :: Clpub -> Mensaje -> Cifrado
codificador c m = codificarCadaElemento c (aEnteros m) 

codificarCadaElemento :: Clpub -> [Integer] -> Cifrado 
codificarCadaElemento c [] = []
codificarCadaElemento c (x:xs) = (codificar c x):(codificarCadaElemento c xs) 

codificar :: Clpub -> Integer -> Integer
codificar c m | mcd m n == 1 = modExp m e n 
              | otherwise = (-m)
              where (e, n) = c 

--(7)
decodificador :: Clpri -> Cifrado -> Mensaje
decodificador c m = aChars (decodificarCadaElemento c m)

decodificarCadaElemento :: Clpri -> [Integer] -> [Integer]
decodificarCadaElemento c [] = []
decodificarCadaElemento c (x:xs) = (decodificar c x):(decodificarCadaElemento c xs)

decodificar :: Clpri -> Integer -> Integer
decodificar c m | m >= 0 = modExp m d n
                | otherwise = -m
                where (d, n) = c
