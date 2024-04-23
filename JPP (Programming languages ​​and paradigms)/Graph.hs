{-# LANGUAGE TypeApplications #-}
module Graph where
import Set(Set)
import qualified Set as Set
class Graph g where
  empty   :: g a
  vertex  :: a -> g a
  union   :: g a -> g a -> g a
  connect :: g a -> g a -> g a

data Relation a = Relation { domain :: Set a, relation :: Set (a, a) }
    deriving (Eq, Show)

data Basic a = Empty
             | Vertex a
             | Union (Basic a) (Basic a)
             | Connect (Basic a) (Basic a)

instance Graph Relation where
  empty = Relation Set.empty Set.empty
  vertex v = Relation (Set.singleton v) Set.empty
  union (Relation v e) (Relation v' e') = Relation (Set.union v v') (Set.union e e')
  connect (Relation v e) (Relation v' e') = Relation (Set.union v v') (Set.union (Set.union e e') (Set.fromList([(x,y)| x <- (Set.toList v), y <- (Set.toList v')])))
                
instance (Ord a, Num a) => Num (Relation a) where
    fromInteger = vertex . fromInteger
    (+)         = union
    (*)         = connect
    signum      = const empty
    abs         = id
    negate      = id

instance Graph Basic where
  empty = Empty
  vertex = Vertex
  union = Union
  connect = Connect

castRelation :: Relation a -> Relation a
castRelation a = a

instance Ord a => Eq (Basic a) where
  g == g' = castRelation (fromBasic g) == castRelation (fromBasic g')



instance (Ord a, Num a) => Num (Basic a) where
    fromInteger = vertex . fromInteger
    (+)         = union
    (*)         = connect
    signum      = const empty
    abs         = id
    negate      = id

instance Semigroup (Basic a) where
  (<>) = union

instance Monoid (Basic a) where
  mempty = Empty

fromBasic :: Graph g => Basic a -> g a
fromBasic Empty = empty
fromBasic (Vertex v) = vertex v
fromBasic (Union g1 g2) = union (fromBasic g1) (fromBasic g2)
fromBasic (Connect g1 g2) = connect (fromBasic g1) (fromBasic g2)

singletonFstFromTuple :: (a,a) -> Set a
singletonFstFromTuple x = Set.Singleton(fst x)

singletonSndFromTuple :: (a,a) -> Set a
singletonSndFromTuple x = Set.Singleton(snd x)

getVerticesFromEdges :: (Ord a) => Relation a -> Set a
getVerticesFromEdges (Relation v e) = Set.Union (foldl Set.Union Set.Empty ((map (singletonFstFromTuple) (Set.toAscList e)))) (foldl Set.Union Set.Empty ((map (singletonSndFromTuple) (Set.toAscList e))))

diffAscLists :: (Ord a) => [a] -> [a] -> [a]
diffAscLists (x:xs) (y:ys) = if x == y then diffAscLists xs ys else (if x < y then x:(diffAscLists xs (y:ys)) else diffAscLists (x:xs) ys)
diffAscLists x [] = x
diffAscLists [] y = y

diffSets :: (Ord a) => Set a -> Set a -> Set a
diffSets s1 s2 = Set.fromList (diffAscLists (Set.toAscList s1) (Set.toAscList s2))
     
getIsolatedVerices :: (Ord a) => Relation a -> Set a
getIsolatedVerices (Relation v e) = diffSets v (getVerticesFromEdges (Relation v e))

showRelationGraph :: (Ord a, Show a) => Relation a -> String
showRelationGraph (Relation v e) = "edges " ++ (show (Set.toAscList e)) ++ " + " ++ "vertices " ++ (show (Set.toAscList (getIsolatedVerices (Relation v e))))
 
instance (Ord a, Show a) => Show (Basic a) where
  show a = showRelationGraph (fromBasic a)


-- | Example graph
-- >>> example34
-- edges [(1,2),(2,3),(2,4),(3,5),(4,5)] + vertices [17]

example34 :: Basic Int
example34 = 1*2 + 2*(3+4) + (3+4)*5 + 17

listEdgesToToDotString :: (Ord a, Show a) => [(a,a)] -> String
listEdgesToToDotString [] = ""
listEdgesToToDotString (x:xs) = (show (fst x)) ++ " -> " ++ (show (snd x)) ++ ";\n" ++ (listEdgesToToDotString xs)

listVerticesToToDotString :: (Ord a, Show a) => [a] -> String
listVerticesToToDotString [] = ""
listVerticesToToDotString (x:xs) = (show x) ++ ";\n" ++ (listVerticesToToDotString xs)

getEdgesFromRelation :: (Ord a, Show a) => Relation a -> Set (a,a)
getEdgesFromRelation (Relation v e) = e

todot :: (Ord a, Show a) => Basic a -> String
todot g = "digraph {\n" ++ listEdgesToToDotString (Set.toAscList (getEdgesFromRelation (fromBasic g))) ++ listVerticesToToDotString (Set.toAscList (getIsolatedVerices (fromBasic g))) ++ "}"

instance Functor Basic where

-- | Merge vertices
-- >>> mergeV 3 4 34 example34
-- edges [(1,2),(2,34),(34,5)] + vertices [17]

mergeV :: Eq a => a -> a -> a -> Basic a -> Basic a
mergeV a b c Empty = Empty
mergeV a b c (Vertex v) = if (v == a || v == b) then Vertex c else Vertex v
mergeV a b c (Union g g') = Union (mergeV a b c g) (mergeV a b c g')
mergeV a b c (Connect g g') = Connect (mergeV a b c g) (mergeV a b c g')

instance Applicative Basic where

instance Monad Basic where

-- | Split Vertex
-- >>> splitV 34 3 4 (mergeV 3 4 34 example34)
-- edges [(1,2),(2,3),(2,4),(3,5),(4,5)] + vertices [17]

splitV :: Eq a => a -> a -> a -> Basic a -> Basic a
splitV = undefined


prop1 = show example34 == "edges [(1,2),(2,3),(2,4),(3,5),(4,5)] + vertices [17]"
prop2 = show (vertex @Basic 1) == "edges [] + vertices [1]"
prop3 = show (connect @Basic 1 2) == "edges [(1,2)] + vertices []"
prop4 = show (vertex @Relation 1)-- == "Relation {domain = [1], relation = []}"
prop5 = show (connect @Relation 1 2) == "Relation {domain = [1,2], relation = [(1,2)]}"
prop6 = todot example34 == "digraph {\n1 -> 2;\n2 -> 3;\n2 -> 4;\n3 -> 5;\n4 -> 5;\n17;\n}"
prop7 = todot (vertex @Basic 1) == "digraph {\n1;\n}"
prop8 = todot (connect @Basic 1 2) == "digraph {\n1 -> 2;\n}"