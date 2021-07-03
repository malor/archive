module Vcs.Common where


data Status = Status {
    vcs :: String,
    branch :: String
} deriving (Show)


class Vcs a where
    vcsName :: a -> String

    getBranch :: a -> IO String

    getStatus :: a -> IO Status
    getStatus v = do
        branch <- getBranch v
        return $ Status (vcsName v) branch
