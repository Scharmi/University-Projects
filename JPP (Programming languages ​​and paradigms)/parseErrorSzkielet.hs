{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE MultiParamTypeClasses #-} 
{-# LANGUAGE FunctionalDependencies #-} 

----------------------------------
--Wersja parsowania z MonadError
----------------------------------

import Data.Char (isHexDigit, digitToInt)
import Control.Monad (foldM)
import Control.Monad.Except

{-
class (Monad m) => MonadError e m | m -> e where
  throwError :: e -> m a
   catchError :: m a -> (e -> m a) -> m a
-}

{-
instance Monad (Either e) where
  return = Right 
  (Left x) >>= _ = Left x 
  (Right x) >>= f = f x
-}

{-
instance MonadError e (Either e) where
  throwError s = Left s 
  catchError (Left s) f = f s
  catchError (Right s) _ = Right s
-}

-- wersja parseHexDigit podnoszaca wyjatek
v4parseHexDigit :: Char -> Either String Int
v4parseHexDigit c = 
  if isHexDigit c then return (digitToInt c)
  else throwError (c:" is not a hexadecimal digit!")

v4parseHex :: String -> Either String Int
v4parseHex = foldM 
               (\n c -> do 
                          d <- v4parseHexDigit c
                          return (16*n+d)) 
               0

-- toString tez podnosi wyjatek
v4toString :: Int -> Either String String
v4toString n = 
   if n == 42 then throwError "Haha! 42!"
   else return (show n)


  
-- konwersja liczb szesnastkowych na dziesietne
-- z obsluga wyjatku:
v4convert :: String -> String
v4convert s = str where
   (Right str) = (do {n <- v4parseHex s ; v4toString n})
                 `catchError`           -- wywolujemy jako operator infiksowy
                  error
--return

-----------------------------------------------
--Wersja parsowania z Parse Error
-----------------------------------------------

data ParseError = Err {location::Int, reason::String}

type ParseMonad = Either ParseError

v5parseHexDigit :: Char -> Int -> ParseMonad Int
v5parseHexDigit c idx = 
  if isHexDigit c then return (digitToInt c)
  else undefined

v5parseHex :: String -> ParseMonad Int
v5parseHex s = foldM 
               (\n c -> do 
                          d <- v5parseHexDigit c 0
                          return (16*n+d)) 
               0 s


v5toString :: Int -> ParseMonad String
v5toString n = undefined


v5convert :: String -> String
v5convert s = str where
 (Right str) = tryParse s `catchError` printError
 tryParse s = do {n <- v5parseHex s; v5toString n} :: ParseMonad String 
 printError e = undefined    :: ParseMonad String 

