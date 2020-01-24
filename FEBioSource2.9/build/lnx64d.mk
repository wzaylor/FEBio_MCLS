# Make include file for FEBio on Linux 64 bit

CC = icpc

# Remove -DHAVE_LEVMAR and $(LEV_LIB) from LIBS if not linking with the Lourakis levmar routine.
DEF = -DLINUX -DMKL_ISS -DPARDISO -DHAVE_LEVMAR -DHAVE_ZLIB -DSVN #-DHAVE_GSL

FLG = -O3 -fPIC -fopenmp -static-intel -no-intel-extensions -std=c++11 -static-libstdc++ -g -O0

# Intel Compiler
INTELROOT = $(subst /mkl,,$(MKLROOT))/compiler
INTEL_INC = $(INTELROOT)/include
INTEL_LIB = $(INTELROOT)/lib/intel64

# Pardiso solver
MKL_PATH = $(MKLROOT)/lib/intel64
MKL_LIB = -Wl,--start-group $(MKL_PATH)/libmkl_intel_lp64.a
MKL_LIB += $(MKL_PATH)/libmkl_core.a $(MKL_PATH)/libmkl_intel_thread.a -Wl,--end-group
#MKL_LIB += $(INTEL_LIB)/libiomp5.a -pthread -lz
MKL_LIB += -liomp5 -pthread -lz

# Levmar library
LEV_LIB = -L/home/will/Programs/levmar-2.6 -llevmar
LEV_INC = /home/will/Programs/levmar-2.6

# GSL library
#GSL_LIB = -lgsl -lgslcblas

# SuperLU library
SUPERLU_INC = /home/sci/mherron/Resources/SuperLU/4.3/SRC/
SUPERLU_LIB =	-lsuperlu_4.3

# SuperLU_MT library
SUPERLUMT_INC = /home/sci/mherron/Resources/SuperLU_MT_2.2/SRC/
SUPERLUMT_LIB =	-lsuperlu_mt_OPENMP

LIBS = -L$(FEBDIR)/build/lib $(LEV_LIB) $(MKL_LIB) $(GSL_LIB) '-Wl,-rpath,$$ORIGIN'

INC = -I$(INTEL_INC) -I$(FEBDIR) -I$(LEV_INC) -I$(FEBDIR)build/include
