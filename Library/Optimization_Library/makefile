# =======================
#     LIBRARY make
# =======================

# Gnu C make cpgplot_GRID UTILS (libda_cpgplot_GRID.a)
PROJECT_DIR          = ${HOME}/PROJECT_HIV-AIDS_MADAGASCAR/
CPGPLOT              = ${HOME}/CPGPLOT/#########################
LIB_DIR              = ${PROJECT_DIR}Library/Optimization_Library/
RANDOM_DIR           = ${PROJECT_DIR}Library/GSL_RANDOM/
IO_DIR               = ${PROJECT_DIR}Library/IO_Library/
ERROR_DIR            = ${PROJECT_DIR}Definition_Error_Model/
INCLUDE_R_DIR        =/usr/share/R/include/
# Mac users, please: 
# INCLUDE_DIR        =/opt/local/include/
EXTRA_INCLUDE_PATH   = -I${LIB_DIR} -I${PROJECT_DIR} -I${PROJECT_DIR}Include/ -I${RANDOM_DIR} -I${IO_DIR} -I${INCLUDE_R_DIR} -I${ERROR_DIR}
# Mac users, plese
# EXTRA_INCLUDE_PATH   = -I${LIB_DIR} -I${PROJECT_DIR} -I${PROJECT_DIR}Include/ -I${RANDOM_DIR} -I${IO_DIR} -I${INCLUDE_DIR} -I${ERROR_DIR}
EXTRA_INCLUDE_PATH+=-I${CPGPLOT}###################
EXTRA_INCLUDE_PATH+=-I${CPGPLOT}library/###########
EXTRA_INCLUDE_PATH+=-I${CPGPLOT}library_basic_UTL/#

FILE=FILE_REPRESENTATION###################### Possibilities: 'FILE_REPRESENTATION' / 'NON_FILE_REPRESENTATION'
CPG=CPGPLOT_REPRESENTATION############## Possibilities: 'CPGPLOT_REPRESENTATION' / 'NON_CPGPLOT_REPRESENTATION'

CFLAGS=-g -Wall -DHAVE_INLINE -D${CPG} ${EXTRA_INCLUDE_PATH}
###CFLAGS= -Wall -O21

COMPILER=gcc -fPIC -DSHARED_OBJECT

OBJECTS=GSL_Function_to_Minimize.o GSL_Function_to_Minimize_AIDS.o GSL_Function_to_Minimize_Error_Model.o GSL_neglog_Error_Probability_Model.o GSL_neglog_Error_Probability_Model_Gaussian.o GSL_neglog_Error_Probability_Model_Gamma.o GSL_Minimization_Simplex.o GSL_CPGPLOT_Minimization_Simplex.o GSL_Minimization_Driver.o Checking_for_Parameter_Boundaries.o Inspecting_Likelihood_of_Final_Solution.o Inspecting_Solution_Driver.o generic_Function_Parameter_2Dim_Scan.o

.SUFIXES:       .o .c

.c.o:
	${COMPILER} $(CFLAGS) -c $<

da_Optimization: ${OBJECTS}
	ar -q libda_Optimization.a ${OBJECTS}

da_Optimization_SO: ${OBJECTS}
	gcc -shared -o libda_Optimization.so ${OBJECTS}

clean:
	rm -f *.o *~
