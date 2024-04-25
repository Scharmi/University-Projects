inits :: [a] -> [[a]]
inits [] = [[]]
inits(x:xs) = []:[x:ys | ys <- inits xs]

incAll :: [[Int]] -> [[Int]]
incAll [] = []
incAll (x:xs) = (map (+1) x) : incAll xs

sumFold :: [Int] -> Int
sumFold xs = foldr (+) 0 xs

factFold :: Int -> Int
factFold n = foldr (*) 1 [1..n]

triples :: Int -> [(Int, Int, Int)]
triples n = [(x,y,z) | x <- [1..n], y <- [1..n], z <- [1..n]]

triads :: Int -> [(Int, Int, Int)]
triads n = [(x,y,z) | x <- [1..n], y <- [x..n], z <- [y..n], x^2 + y^2 == z^2]

incMaybe :: Maybe Int -> Maybe Int
incMaybe Nothing = Nothing
incMaybe (Just x) = Just (x+1)

safeDiv :: Int -> Int -> Maybe Int
safeDiv _ 0 = Nothing
safeDiv x y = Just (x `div` y)



