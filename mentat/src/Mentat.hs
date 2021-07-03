module Main where


import qualified System.Directory as Dir
import qualified System.Environment as Env

import qualified Vcs.Common as Common
import qualified Vcs.Base as Vcs


main = do
    args <- Env.getArgs
    cwd <- Dir.getCurrentDirectory

    let dir = case args of [] -> cwd
                           _ -> head args

    status <- Vcs.getStatus dir
    case status of
        Nothing -> putStr ""
        Just s -> putStr $ "[" ++ (Common.vcs s) ++ "]" ++ "(" ++ (Common.branch s) ++ ")"
