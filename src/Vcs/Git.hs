module Vcs.Git (
  maybeGit
) where


import Data.Maybe
import qualified System.Directory as Dir
import qualified System.FilePath as FP
import qualified Text.Regex as Regex

import qualified Vcs.Common as Common


data Git = Git {path :: String} deriving (Show)


isRepo :: FP.FilePath -> IO Bool
isRepo repo = do
    headExist <- Dir.doesFileExist $ FP.joinPath [repo, "HEAD"]
    refsExist <- Dir.doesDirectoryExist $ FP.joinPath [repo, "refs"]
    return $ headExist && refsExist


maybeGit :: FP.FilePath -> IO (Maybe Git)
maybeGit repo =
    do
        isBare <- isRepo bare
        isPlain <- isRepo plain

        if isBare
            then return $ Just (Git bare)
            else if isPlain
                then return $ Just (Git plain)
                else return Nothing
    where bare = repo
          plain = FP.joinPath [repo, ".git"]


branchFromRef :: String -> String
branchFromRef r =
    case Regex.matchRegex pattern r of
        Just groups -> head groups
        Nothing -> "detached HEAD"
    where pattern = Regex.mkRegex "ref: refs/heads/(.+)"


instance Common.Vcs Git where
    vcsName _ = "git"

    getBranch (Git repoPath) =
        do
            headContents <- readFile headPath
            return $ branchFromRef headContents
        where headPath = FP.joinPath [repoPath, "HEAD"]
