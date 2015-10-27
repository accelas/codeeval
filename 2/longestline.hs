

import Data.Ord
import Data.List
import System.Environment (getArgs)

takeLines num xs = take num $ reverse $ sortBy (comparing length) xs

main = do
    args <- getArgs
    content <- readFile (head args)
    let ls = lines content
    let num = read (head ls)
    let body = tail ls
    mapM_ putStrLn $ takeLines num body





