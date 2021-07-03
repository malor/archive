module Vcs.Hg (
    maybeHg
) where


import Data.Maybe
import qualified System.Directory as Dir
import qualified System.FilePath as FP

import qualified Vcs.Common as Common


data Hg = Hg {path :: String} deriving Show


maybeHg :: FP.FilePath -> IO (Maybe Hg)
maybeHg path = do
    valid <- isRepo repo
    if valid
        then (return $ Just $ Hg repo)
        else (return Nothing)
    where repo = FP.joinPath [path, ".hg"]


isRepo :: FP.FilePath -> IO Bool
isRepo path = do
    branchExists <- Dir.doesFileExist branch
    storeExists <- Dir.doesDirectoryExist store

    return $ branchExists && storeExists

    where branch = FP.joinPath [path, "branch"]
          store = FP.joinPath [path, "store"]


instance Common.Vcs Hg where
    vcsName _ = "hg"

    getBranch (Hg repoPath) =
        do
            branchContents <- readFile branchPath
            return $ takeWhile (/= '\n') branchContents
        where branchPath = FP.joinPath [repoPath, "branch"]
