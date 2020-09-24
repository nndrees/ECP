CXXFLAGS = -O0 -std=c++11 -g -Wall -Wextra -pedantic -Wshadow -Wpointer-arith \
           -Wcast-align -Wwrite-strings \
           -Wmissing-declarations -Wredundant-decls  -Winline \
           -Wno-long-long -Wuninitialized -Wconversion

ecp: ecp.cc
