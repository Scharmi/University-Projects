module Set(Set(..), empty, null, singleton, union, fromList
              , member, toList, toAscList, elems
              ) where
import Prelude hiding(null)
import Data.List(sort)

data Set a = Empty
           | Singleton a
           | Union (Set a) (Set a)

empty :: Set a
empty = Empty

null :: Set a -> Bool
null Empty = True
null _ = False

member :: Eq a => a -> Set a -> Bool
member _ Empty = False
member x (Singleton y) = x == y
member el (Union s1 s2) = member el s1 || member el s2 

singleton :: a -> Set a
singleton a = Singleton a

fromList :: [a] -> Set a
fromList [] = Empty
fromList (x:xs) = Union (Singleton x) (fromList xs)

toList :: Set a -> [a]
toList Empty = []   
toList (Singleton a) = [a]
toList (Union a b) = toList a ++ toList b

removeDuplicatesFromAscList :: Ord a => [a] -> [a]
removeDuplicatesFromAscList (x:y:xs) = if x == y then removeDuplicatesFromAscList (y:xs) else x:(removeDuplicatesFromAscList (y:xs))
removeDuplicatesFromAscList x = x

toAscList :: Ord a => Set a -> [a]
toAscList a = removeDuplicatesFromAscList (sort (toList a)) 


elems :: Set a -> [a]
elems = toList

union :: Set a -> Set a -> Set a
union x y = Union x y

insert :: a -> Set a -> Set a
insert el s = Union (Singleton el) s

instance Ord a => Eq (Set a) where
    x == y = toAscList x == toAscList y

instance Semigroup (Set a) where
    (<>) = union

instance Monoid (Set a) where
    mempty = empty
    mappend = union
instance Show a => Show (Set a) where
    show s = "Elements: " ++ show (toList s)

instance Functor Set where
    fmap f Empty = Empty
    fmap f (Singleton a) = Singleton (f a)
    fmap f (Union a b) = Union (fmap f a) (fmap f b)

example :: Set Int
example = fromList [3,2,1,4,5,8]

leftUnit :: Set Int -> Bool
leftUnit a = mempty <> a == a