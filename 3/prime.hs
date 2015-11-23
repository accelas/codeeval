

find_prime l' = head $ filter palindrome $ go l' []
  where
    go l result
      | length l == 1 = head l : result
      | otherwise = let
                      prime = head l
                      reminder = filter (\x -> mod x prime /= 0) l
                    in go reminder $ prime : result

    palindrome num = (show num) == (reverse $ show num)

main = print $ find_prime [2..1000]
