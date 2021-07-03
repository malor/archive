{-# LANGUAGE ExistentialQuantification #-}

module Vcs.Base where


import qualified System.FilePath as FP

import qualified Vcs.Common as Common
import qualified Vcs.Git as Git
import qualified Vcs.Hg as Hg


data AnyVcs = forall v. (Common.Vcs v) => AnyVcs v


maybeVcs :: FP.FilePath -> IO (Maybe AnyVcs)
maybeVcs = maybeVcs' fs
    where maybeVcs' [] _ = return Nothing
          maybeVcs' (f:fs) path = do
              vcs <- f path
              case vcs of
                  Nothing -> maybeVcs' fs path
                  v@(Just x) -> return $ v
          toMaybeAnyVcs f = \path -> do
             vcs <- f path
             return $ vcs >>= \x -> Just $ AnyVcs x
          fs = [toMaybeAnyVcs Git.maybeGit, toMaybeAnyVcs Hg.maybeHg]


getStatus :: FP.FilePath -> IO (Maybe Common.Status)
getStatus "/" = return Nothing
getStatus path = do
    vcs <- maybeVcs path
    case vcs of
        Nothing -> getStatus $ FP.takeDirectory path
        Just (AnyVcs v) -> do s <- Common.getStatus v
                              return $ Just s
