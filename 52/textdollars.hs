import System.Environment (getArgs)

-- prefix
prefix 2 = "Twen"
prefix 3 = "Thir"
prefix 4 = "For"
prefix 5 = "Fif"
prefix 6 = "Six"
prefix 7 = "Seven"
prefix 8 = "Eigh"
prefix 9 = "Nine"

convert c
    | c == 0 = ""
    | c == 1 = "One"
    | c == 2 = "Two"
    | c == 3 = "Three"
    | c == 4 = "Four"
    | c == 5 = "Five"
    | c == 6 = prefix 6
    | c == 7 = prefix 7
    | c == 8 = "Eight"
    | c == 9 = prefix 9
    | c == 10 = "Ten"
    | c == 11 = "Eleven"
    | c == 12 = "Twelve"
    | c == 14 = "Fourteen"
    | c < 20 = prefix (c - 10) ++ "teen"
    | c < 100 = prefix (quot c 10) ++ "ty" ++ convert (mod c 10)
    | c < 1000 = convert (quot c 100) ++ "Hundred" ++ convert (mod c 100)
    | c < 1000000 = convert (quot c 1000) ++ "Thousand" ++ convert (mod c 1000)
    | c < 1000000000 = convert (quot c 1000000) ++ "Million" ++ convert (mod c 1000000)
    | c < 1000000000000 = convert (quot c 1000000000) ++ "Billion" ++ convert (mod c 1000000000)

convert' s = if v == 0
    then "ZeroDollars" -- zero needs to be handled outside recusion
    else convert v ++ "Dollars" -- ++ if (v == 1) then "" else "s"
  where
    v = read s

main = do
    [inpFile] <- getArgs
    input <- readFile inpFile
    let contents = lines input
    let res = fmap convert' contents
    mapM_ putStrLn res

