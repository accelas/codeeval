
- brutal force version, way too slow

{-
    import qualified Data.Vector as V

    run n = length $ do
        v <- V.replicateM n [0..9]
        let (d0, d1) = V.splitAt (n `quot` 2) v
        guard $ V.sum d0 == V.sum d1
-}


- try a different approach.

multinomial coefficients:
(x^0 + x^1 + ... + x^9)^n -- n is one-indexed

{-
    result n = sum $ take (n*9 + 1) ((^ 2) <$> (_repeat n go base))
      where
        base :: [Integer]
        base = (replicate 10 1)

        go ls = [sum $ _slice i ls | i <- [0..]]

        _slice i = (take t_i) . (drop d_i)
          where
            t_i = if i + 1 <= 10 then i + 1 else 10
            d_i = if i - 9  >  0 then i - 9 else  0

        _repeat i f ls
          | i <= 1    = ls
          | otherwise = _repeat (i-1) f (f ls)

    run dig_total =  result dig_working
      where
        dig_working = dig_total `quot` 2
-}

> import System.Environment (getArgs)
> import Control.Applicative
> import Control.Monad
>
>  -- final version
>
> result :: Int -> Integer
> result n = go n base
>   where
>     base :: [Integer]
>     base = (replicate 10 1)
>
>     go i ls
>       | i <= 1    = foldl (\b a -> b + a^2) 0 ls
>       | otherwise = go (i-1) $ (count ls) <$> [0..(n*9 + 1)]
>
>     count ls' i = sum $ (take t_i) . (drop d_i) $ ls'
>       where
>         t_i = if i + 1 <= 10 then i + 1 else 10
>         d_i = if i - 9  >  0 then i - 9 else  0
>
> run dig_total =  result dig_working
>   where
>     dig_working = dig_total `quot` 2
>
> main = do
>     [inpFile] <- getArgs
>     input <- readFile inpFile
>     let res = do
>         s <- lines input
>         return $ run $ read s
>     mapM_ print res

