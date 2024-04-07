data Tree a = Empty | Node a (Tree a) (Tree a) deriving (Eq, Ord, Show)

renumber :: Tree a -> Int -> (Tree (a, Int), Int)
renumber Empty n = (Empty, n)
renumber (Node x l r) n = (Node (x, n) l' r', n'')
  where
    (l', n') = renumber l (n+1)
    (r', n'') = renumber r (n'+1)
    