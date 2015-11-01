import System.Environment (getArgs)
import Data.Functor

coin n = n `div` 5 + n `mod` 5 `div` 3 + n `mod` 5 `mod` 3 `div` 1

proc input = (show . coin . read ) <$> lines input

main = do
    [inpFile] <- getArgs
    input <- readFile inpFile
    mapM_ putStrLn $ proc input