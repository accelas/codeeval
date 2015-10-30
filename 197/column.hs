import System.Environment (getArgs)
import Data.Char

base :: Int
base = 27

toDigits 0 = [0]
toDigits n = reverse $ go n
  where
    go 0 = []
    go n = m : go d
      where
        (d, m) = divMod n base

base27Symbols = filter (notElem 0) $ toDigits <$> [1..]

toLetter :: Int -> String
toLetter n = (toEnum . (+ (fromEnum 'A' - 1 ))) <$> base27Symbols !! (n-1)

proc_line str = toLetter n
  where
    n = read str

main = do
    [inpFile] <- getArgs
    input <- readFile inpFile
    let contents = lines input
    let res = proc_line <$> contents
    mapM_ putStrLn res
