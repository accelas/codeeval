import System.Environment (getArgs)
import Control.Monad
import Control.Applicative
import Data.Traversable
import qualified Data.Vector as V

data Op = ADD | SUB | NON -- deriving (Eq, Ord, Enum, Read, Show)

data S = S {-# UNPACK #-} !Int {-# UNPACK #-} !Int
data I = I {-# UNPACK #-} !Int {-# UNPACK #-} !Op

isUgly num
    | mod num 2 == 0 = True
    | mod num 3 == 0 = True
    | mod num 5 == 0 = True
    | mod num 7 == 0 = True
    | otherwise = False

opsGen num = V.replicateM num [ADD, SUB, NON]

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

calc :: V.Vector Op -> V.Vector Int -> Int
calc ops num = sign * V.last num + carry + V.sum res
  where
    _calc :: S -> I -> (S, Int)
    _calc (S sign carry) (I dig0 ADD) = (S   1  0, carry + sign * dig0)
    _calc (S sign carry) (I dig0 SUB) = (S (-1) 0, carry + sign * dig0)
    _calc (S sign carry) (I dig0 NON) = (S sign ((carry + sign * dig0) * 10), 0)

    (S sign carry, res) = mapAccumL _calc (S 1 0) (V.zipWith I (V.init num) ops)

result :: String -> String
result num =
    let _num = V.fromList $ char2Int <$> num
        _len = length num - 1
    in show . length $ do
        o <- opsGen _len
        void $ guard (isUgly . abs $ calc o _num)

main = do
    [inpFile] <- getArgs
    input <- readFile inpFile
    let res = result <$> lines input
    mapM_ putStrLn res

