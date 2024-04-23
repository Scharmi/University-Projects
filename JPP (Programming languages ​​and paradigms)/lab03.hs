data Tree a = Empty | Node a (Tree a) (Tree a)

instance Show a => Show (Tree a) where
    show t = show' t
        where
            show' Empty = "Empty"
            show' (Node x l r) = "Node " ++ show x ++ " (" ++ show' l ++ ") (" ++ show' r ++ ")"
    
instance Eq a => Eq (Tree a) where
    t1 == t2 = tEq t1 t2
        where
            tEq Empty Empty = True
            tEq (Node x1 l1 r1) (Node x2 l2 r2) = x1 == x2 && tEq l1 l2 && tEq r1 r2
            tEq _ _ = False

toList :: Tree a -> [a]
toList Empty = []
toList (Node x l r) = toList l ++ [x] ++ toList r

class BST t where
    empty :: t a
    insert :: Ord a => a -> t a -> t a
    member :: Ord a => a -> t a -> Bool




    