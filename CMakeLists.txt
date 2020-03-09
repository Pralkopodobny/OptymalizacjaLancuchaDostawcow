cmake_minimum_required(VERSION 3.16)
project(OptymalizacjaLancuchaDostawcow)

set(CMAKE_CXX_STANDARD 11)

add_executable(OptymalizacjaLancuchaDostawcow main.cpp Matrix.cpp Matrix.h MscnProblem.cpp MscnProblem.h MscnSolution.cpp MscnSolution.h CRandom.cpp CRandom.h RandomSearch.cpp RandomSearch.h Problem.h Optimizer.h DiffEvol.cpp DiffEvol.h Timer.cpp Timer.h TrivialOptimizer.cpp TrivialOptimizer.h)