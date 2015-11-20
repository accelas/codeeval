
import System.Environment (getArgs)
import Control.Monad
import Control.Applicative
import Data.List


is_ugly num = elem 0 $ mod (abs num) <$> [2,3,5,7]

data Op = ADD | SUB | NON deriving (Eq, Ord, Enum, Read, Show)

opsGen num = replicateM num [ADD, SUB, NON]

char2Int '1' = 1
char2Int '2' = 2
char2Int '3' = 3
char2Int '4' = 4
char2Int '5' = 5
char2Int '6' = 6
char2Int '7' = 7
char2Int '8' = 8
char2Int '9' = 9
char2Int _   = 0

_calc :: (Int, Int) -> (Int, Op) -> ((Int, Int), Int)
_calc (sign, carry) (dig0, ADD) = ((1, 0), carry + sign * dig0)
_calc (sign, carry) (dig0, SUB) = ((-1, 0), carry + sign * dig0)
_calc (sign, carry) (dig0, NON) = ((sign, (carry + sign * dig0) * 10), 0)

calc ops num = sign * (last num) + carry + sum res
  where
    ((sign, carry), res) = mapAccumL _calc (1,0) (zip (init num) ops)

proc num = [calc o (char2Int <$> num) | o <- opsGen (length num - 1)]

result n = length $ (filter is_ugly) (proc n)

main = do
    [inpFile] <- getArgs
    input <- readFile inpFile
    mapM_ putStrLn $ show . result <$> lines input

_proc num = [(debug_calc o (char2Int <$> num)) | o <- opsGen (length num - 1)]

debug_calc ops num = (p_input l t) ++ (show $ calc ops num)
  where
    l = (zip (init num) ops)
    t = last num

p_input ::[(Int, Op)] -> Int -> String
p_input l t = concat $ [ show d ++ _show o | (d , o) <- l ] ++ [show t ++ " == "]
  where
    _show NON = ""
    _show ADD = " + "
    _show SUB = " - "
