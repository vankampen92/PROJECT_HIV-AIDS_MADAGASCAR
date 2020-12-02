#/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#/*                                                                           */
#/*                           David Alonso, 2011 (c)                          */
#/*                                                                           */
#/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
PROJECT_DIR=${HOME}/PROJECT_HIV-AIDS_MADAGASCAR/#########
TIME_TREND_DIR=${PROJECT_DIR}Definition_Time_Trend_Dependence/
IO_DIR=${PROJECT_DIR}Library/IO_Library/
OPT_DIR= ${PROJECT_DIR}Library/Optimization_Library/
ERROR_DIR=${PROJECT_DIR}Definition_Error_Model/
WKD=${PROJECT_DIR}MODEL_CALCULATIONS/TEMPORAL_EVOLUTION_PARAMETER_ESTIMATES/
C_NR=${PROJECT_DIR}Library/C_NumRecip/#############
GSL_DA=${PROJECT_DIR}Library/GSL_RANDOM/##########
HEAD.H =${PROJECT_DIR}Include/MODEL.h##############
INCLUDE_DIR=${PROJECT_DIR}Include##################
CPGPLOT = ${HOME}/CPGPLOT/#########################
# EXTRA_LIBRARY_PATH=-L/usr/local/pgplot#############
EXTRA_LIBRARY_PATH+=-L${CPGPLOT}###################
EXTRA_LIBRARY_PATH+=-L${CPGPLOT}library/###########
EXTRA_LIBRARY_PATH+=-L${CPGPLOT}library_basic_UTL/#
EXTRA_LIBRARY_PATH+=-L${C_NR}######################
EXTRA_LIBRARY_PATH+=-L${GSL_DA}####################
EXTRA_LIBRARY_PATH+=-L${IO_DIR}
EXTRA_LIBRARY_PATH+=-L${OPT_DIR}
EXTRA_LIBRARY_PATH+=-L${ERROR_DIR}
# EXTRA_INCLUDE_PATH=-I/usr/local/pgplot############# See custumized ./bashrc file on ${HOME} directory.
EXTRA_INCLUDE_PATH+=-I${INCLUDE_DIR}###############
EXTRA_INCLUDE_PATH+=-I${PROJECT_DIR}###############
EXTRA_INCLUDE_PATH+=-I${CPGPLOT}###################
EXTRA_INCLUDE_PATH+=-I${CPGPLOT}library/###########
EXTRA_INCLUDE_PATH+=-I${CPGPLOT}library_basic_UTL/#
EXTRA_INCLUDE_PATH+=-I${C_NR}######################
EXTRA_INCLUDE_PATH+=-I${GSL_DA}####################
EXTRA_INCLUDE_PATH+=-I${IO_DIR}
EXTRA_INCLUDE_PATH+=-I${OPT_DIR}
EXTRA_INCLUDE_PATH+=-I${ERROR_DIR}
##############################################################################################################
## C O M P I L A T I O N   O P T I O N   C O N T R O L I N G   N U M E R I C A L   R E C I P E S
NR=NUMERICAL_RECIPES###############################
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   P R O G R A M   O U T P U T
V=NON_VERBOSE###################################### Possibilities: 'VERBOSE' / 'NON_VERBOSE'
FILE=FILE_REPRESENTATION###################### Possibilities: 'FILE_REPRESENTATION' / 'NON_FILE_REPRESENTATION'
CPG=CPGPLOT_REPRESENTATION############## Possibilities: 'CPGPLOT_REPRESENTATION' / 'NON_CPGPLOT_REPRESENTATION'
STATIONARITY=NON_STATIONARY_POINT_REPRESENTATION# Possibilitites: 'STATIONARY_POINT_REPRESENTATION' / 'NON_STATIONARY_POINT_REPRESENTATION'
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   P A R A M E T E R   S P A C E ###############
TYPE_of_BOUNDARY=###
##############################################################################################################
RANDOM_SEED=CURRENT_TIME_RDN_SEED####### 'CURRENT_TIME_RDN_SEED' / 'FILE_RND_SIDE'
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   M O D E L   D E F I N I T I O N #############
X_MODEL=X2W2SILD# 'X2W2' 'XWSILD' 'X_' ######################################
Y_MODEL=YSILD#    'Y_'                  #######################################
ODE_MODEL=${X_MODEL}-${Y_MODEL}####################
################################################### (see rainTemperature.c) ##################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   N U M E R I C A L   I N T E G R A T I O N  ##
ODE_DIR_GENERAL=${PROJECT_DIR}Definition_Numerical_Integration/#########
ODE_DIR=${ODE_DIR_GENERAL}${ODE_MODEL}/#########
ODE_DEF=${ODE_DIR_GENERAL}ODE_Definitions/###########################
ODE_FIXED_POINTS=${PROJECT_DIR}Fixed_Points_Functions/###########
ODE_R_0=${PROJECT_DIR}R_0_Definition/${ODE_MODEL}/###########
TYPE_NUMERICAL_INTEGRATION=GSL_RKF45#############################
######################################## Possibilities:
######################################## 'GSL_BSIMP' uses the Jacobian matrix which has to be provided in JAC_sys${SYS}.c.
######################################## 'GSL_RKF45' is a general purpose integrator.
######################################## 'GSL_BSIMP' and GSL_RKF45 uses adaptive steps
######################################## 'GSL_RK4' does not uses adaptive steps
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   J A C O B I A N   T Y P E   #################
## To pass this 'JACOBIAN' variable to the compiling code is necessary whether you need to calculate stationary
## points or perform the numerical integration of the system
JACOBIAN=ODE# Options: 'ODE'
EXTRA_INCLUDE_PATH+=-I${ODE_DEF}Include_${JACOBIAN}/#####
##############################################################################################################
## D E F I N I T I O N   N A M E   E X E C U T B L E   C O D E ###############################################
### EXE=${JACOBIAN}_${ODE_MODEL}
EXE=${ODE_MODEL}
##############################################################################################################
EXTERN=#Possibilities: void (to be locally executed) / -static (to be non-locally executed) #
######################################## Possibilities: GA (locally executed) / GA_EXTERN (non-locally executed)
LDFLAGS+=-lm -lgsl -lgslcblas -lDa_GSL_UTL -lda_IO -lda_Optimization -lda_Error -lNumRec -lNRUTL -L${C_NR} -lda_cpgplot_XY_GRID_FILE -lda_cpgplot_BASIC ${EXTRA_LIBRARY_PATH}
CXXFLAGS+=${EXTRA_INCLUDE_PATH} -D${V} -D${CPG} -D${FILE}  -D${TYPE_NUMERICAL_INTEGRATION} -D${RANDOM_SEED}  -D${X_MODEL} -D${Y_MODEL} -D${JACOBIAN} -D${NR} -D${STATIONARITY} -DHAVE_INLINE ${EXTERN} -g #-Wall
##############################################################################################################
# either -g or some optimization opiton, for instance, -O3
# This makefile uses full power of conditional compilation. There is a bunch of variables that control this and
# are passed as flags -D[NAME_of_the_VARIABLE] to the compiler during compilation
##############################################################################################################
LIBS=-L/usr/lib -lX11
PGPLOT_LIB=-L/usr/lib -lpgplot -L/usr/lib -lpng
CPGPLOT_LIB=-L/usr/lib -lcpgplot -lpgplot -L/usr/lib -lpng
##############################################################################################################
OBJECTS = main.o report.o argumentControl.o argumentControl_fprintf.o assert_right_model_definition.o Observed_Data.o                         \
	Parameter_Model.o Time_Control.o Parameter_Table.o definition_OutPut_Variables.o assignCodes_to_Model_Parameters.o assignLabel_to_Model_Parameters.o assignLabel_to_Model_Variables.o assignLabel_to_Output_Variables.o assignStructValue_to_VectorEntry.o assignSymbol_to_Model_Parameters.o assignSymbol_to_Model_Variables.o assignSymbol_to_Output_Variables.o assignVectorEntry_to_Structure.o fprintf_Model_Parameters.o Model_Variable_Initial_Condition_into_Vector_Entry.o Vector_Entry_into_Model_Variable_Initial_Condition.o fprintf_Output_Variables.o                                                        \
	Latex_assignLabel_to_Model_Parameters.o  Latex_Write_Parameter_Table.o               \
	Parameter_Space.o Parameter_Space_Boundary_for_Trends${TYPE_of_BOUNDARY}.o  Initial_Condition_Boundary_Values.o  \
	deterministic_time_dynamics.o numerical_Integration_Driver.o Initial_Conditions_Numerical_Integration.o Initial_Condition_from_Parameter_Table.o  Random_Initial_Condition.o Random_Initial_Guess_within_Boundaries.o ODE_sys_${ODE_MODEL}.o JAC_sys_MODEL.o JACOBIAN_Matrix_${ODE_MODEL}.o  R_0_Function.o               \
	Model_Variables_Code.o Total_Effective_Fractions.o Total_Population_Numbers.o Total_Disease_Prevalence.o Total_Disease_Infection.o Total_Population_Fractions.o \
	stat.o                                                                               \
	CPGPLOT___X_Y___Parameter_Table.o                                                    \
	Fixed_Points_All.o Steady_State_x_Fraction.o x_y_Fixed_Points_Functions.o Feasibility_Condition.o Steady_State_y_Fraction.o intermediateRoot_x_Fraction.o Stable_Solution.o Stable_Solution_x.o Stable_Solution_y.o Generic_Root_Finder.o x_y_Intersection_Plots.o                                                         \
	Time_Dependence_Apply.o Time_Dependence_Resolve.o Time_Dependence_Control.o Trend_Control.o # index.Definition${TYPE_of_INDEX}.o

### Example:
RUN_ARGS =-sP 1 -I0 21 -H21 1.0 -n 1 -v0 6 -G0 1 -G1 1 -tn 17 -t0 2000.0 -t1 2016.0 -t4 1 -xn 0 -G5 1 -G6 0.0 -G7 1000000 -DP 4 -DC 0 -D0 0 -D1 4 -D2 0 -P0 13 -a0 0  -P1 2 -a1 0  -P2 3 -a2 0  -P3 4 -a3 0

CC=gcc##
FF=gfortran##

all: ${EXE} COMPILATION_OPTIONS

${EXE}:  	$(OBJECTS) library library_Error library_IO 
		$(FF) -o ${EXE} $(OBJECTS) $(LDFLAGS) $(CXXFLAGS) $(CPGPLOT_LIB) $(LIBS)

library:
	cd ${OPT_DIR}; rm *.o; rm *.a; make

library_Error:
	cd ${ERROR_DIR}; rm *.o; rm *.a; make

library_IO:
	cd ${IO_DIR}; rm *.o; rm *.a; make

# Main program functions:
main.o: main.c ${HEAD.H}
	$(CC) -c main.c $(CXXFLAGS)

report.o: report.c ${HEAD.H}
	${CC} -c report.c $(CXXFLAGS)

argumentControl.o: argumentControl.c ${HEAD.H}
	${CC} -c argumentControl.c $(CXXFLAGS)

argumentControl_fprintf.o: argumentControl_fprintf.c ${HEAD.H}
	${CC} -c argumentControl_fprintf.c $(CXXFLAGS)

# Funcions controling main data structures (Parameter_Model, Time_Control,
# Parameter_Table):
assert_right_model_definition.o: ${PROJECT_DIR}assert_right_model_definition.c ${HEAD.H}
	$(CC) -c ${PROJECT_DIR}assert_right_model_definition.c $(CXXFLAGS)

Parameter_Model.o: ${PROJECT_DIR}Parameter_Model.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Parameter_Model.c $(CXXFLAGS)

Time_Control.o: ${PROJECT_DIR}Time_Control.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Time_Control.c $(CXXFLAGS)

Observed_Data.o: ${PROJECT_DIR}Observed_Data.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Observed_Data.c $(CXXFLAGS)

Trend_Control.o: ${TIME_TREND_DIR}Trend_Control.c ${HEAD.H}
	${CC} -c ${TIME_TREND_DIR}Trend_Control.c $(CXXFLAGS)

Time_Dependence_Apply.o: ${TIME_TREND_DIR}Time_Dependence_Apply.c ${HEAD.H}
	${CC} -c ${TIME_TREND_DIR}Time_Dependence_Apply.c $(CXXFLAGS)

Time_Dependence_Resolve.o: ${TIME_TREND_DIR}Time_Dependence_Resolve.c ${HEAD.H}
	${CC} -c ${TIME_TREND_DIR}Time_Dependence_Resolve.c $(CXXFLAGS)

Time_Dependence_Control.o: ${TIME_TREND_DIR}Time_Dependence_Control.c ${HEAD.H}
	${CC} -c ${TIME_TREND_DIR}Time_Dependence_Control.c $(CXXFLAGS)

Parameter_Table.o: ${PROJECT_DIR}Parameter_Table.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Parameter_Table.c $(CXXFLAGS)

definition_OutPut_Variables.o: ${PROJECT_DIR}definition_OutPut_Variables.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}definition_OutPut_Variables.c ${CXXFLAGS}

assignLabel_to_Model_Parameters.o: ${PROJECT_DIR}assignLabel_to_Model_Parameters.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}assignLabel_to_Model_Parameters.c $(CXXFLAGS)

assignCodes_to_Model_Parameters.o:	${PROJECT_DIR}/assignCodes_to_Model_Parameters.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}$/assignCodes_to_Model_Parameters.c $(CXXFLAGS)

assignSymbol_to_Model_Parameters.o:	${PROJECT_DIR}/assignSymbol_to_Model_Parameters.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}$/assignSymbol_to_Model_Parameters.c $(CXXFLAGS)

assignLabel_to_Model_Variables.o: ${PROJECT_DIR}Assign_Model_Variables/${ODE_MODEL}/assignLabel_to_Model_Variables.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Assign_Model_Variables/${ODE_MODEL}/assignLabel_to_Model_Variables.c $(CXXFLAGS)

assignSymbol_to_Model_Variables.o: ${PROJECT_DIR}Assign_Model_Variables/${ODE_MODEL}/assignSymbol_to_Model_Variables.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Assign_Model_Variables/${ODE_MODEL}/assignSymbol_to_Model_Variables.c $(CXXFLAGS)

Model_Variable_Initial_Condition_into_Vector_Entry.o: ${PROJECT_DIR}Assign_Model_Variables/${ODE_MODEL}/Model_Variable_Initial_Condition_into_Vector_Entry.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Assign_Model_Variables/${ODE_MODEL}/Model_Variable_Initial_Condition_into_Vector_Entry.c $(CXXFLAGS)

Vector_Entry_into_Model_Variable_Initial_Condition.o: ${PROJECT_DIR}Assign_Model_Variables/${ODE_MODEL}/Vector_Entry_into_Model_Variable_Initial_Condition.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Assign_Model_Variables/${ODE_MODEL}/Vector_Entry_into_Model_Variable_Initial_Condition.c $(CXXFLAGS)

assignLabel_to_Output_Variables.o: ${PROJECT_DIR}assignLabel_to_Output_Variables.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}assignLabel_to_Output_Variables.c $(CXXFLAGS)

assignSymbol_to_Output_Variables.o: ${PROJECT_DIR}assignSymbol_to_Output_Variables.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}assignSymbol_to_Output_Variables.c $(CXXFLAGS)

assignVectorEntry_to_Structure.o: ${PROJECT_DIR}assignVectorEntry_to_Structure.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}assignVectorEntry_to_Structure.c $(CXXFLAGS)

assignStructValue_to_VectorEntry.o: ${PROJECT_DIR}assignStructValue_to_VectorEntry.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}assignStructValue_to_VectorEntry.c $(CXXFLAGS)

fprintf_Model_Parameters.o: ${PROJECT_DIR}fprintf_Model_Parameters.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}fprintf_Model_Parameters.c $(CXXFLAGS)

fprintf_Output_Variables.o: ${PROJECT_DIR}fprintf_Output_Variables.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}fprintf_Output_Variables.c $(CXXFLAGS)

Latex_assignLabel_to_Model_Parameters.o: ${PROJECT_DIR}Latex_assignLabel_to_Model_Parameters.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Latex_assignLabel_to_Model_Parameters.c  ${CXXFLAGS}

Latex_Write_Parameter_Table.o:  ${PROJECT_DIR}/Latex_Write_Parameter_Table.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Latex_Write_Parameter_Table.c ${CXXFLAGS}

# Functions to control the definition of a subspace from the whole parameter space
Parameter_Space.o: ${PROJECT_DIR}Definition_Parameter_Space/Parameter_Space.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Parameter_Space/Parameter_Space.c $(CXXFLAGS)

Parameter_Space_Boundary_for_Trends${TYPE_of_BOUNDARY}.o:  ${PROJECT_DIR}Definition_Parameter_Space/Parameter_Space_Boundary_for_Trends${TYPE_of_BOUNDARY}.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Parameter_Space/Parameter_Space_Boundary_for_Trends${TYPE_of_BOUNDARY}.c $(CXXFLAGS)

Initial_Condition_Boundary_Values.o:  ${PROJECT_DIR}Definition_Parameter_Space/Initial_Condition_Boundary_Values.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Parameter_Space/Initial_Condition_Boundary_Values.c $(CXXFLAGS)

# index.Definition${TYPE_of_INDEX}.o: ${PROJECT_DIR}Definition_Parameter_Space/index.Definition${TYPE_of_INDEX}.c ${HEAD.H}
#	${CC} -c ${PROJECT_DIR}Definition_Parameter_Space/index.Definition${TYPE_of_INDEX}.c $(CXXFLAGS)

# Functions to control graphical plots
CPGPLOT___X_Y___Parameter_Table.o: ${CPGPLOT}CPGPLOT_Parameter_Table/CPGPLOT___X_Y___Parameter_Table.c ${CPGPLOT}CPGPLOT_Parameter_Table/CPGPLOT___X_Y___Parameter_Table.h
	${CC} -c ${CPGPLOT}CPGPLOT_Parameter_Table/CPGPLOT___X_Y___Parameter_Table.c $(CXXFLAGS)

# R_0 (model-dependent definition)
R_0_Function.o: ${ODE_R_0}R_0_Function.c ${HEAD.H}
	$(CC) -c ${ODE_R_0}R_0_Function.c $(CXXFLAGS)

# Functions controling numerical integration of the ODE system
deterministic_time_dynamics.o: ${ODE_DIR_GENERAL}deterministic_time_dynamics.c ${HEAD.H}
	$(CC) -c ${ODE_DIR_GENERAL}deterministic_time_dynamics.c $(CXXFLAGS)

numerical_Integration_Driver.o: ${ODE_DIR_GENERAL}numerical_Integration_Driver.c ${HEAD.H}
	$(CC) -c ${ODE_DIR_GENERAL}numerical_Integration_Driver.c $(CXXFLAGS)

Initial_Conditions_Numerical_Integration.o: ${ODE_DIR_GENERAL}Initial_Conditions_Numerical_Integration.c ${HEAD.H}
	${CC} -c ${ODE_DIR_GENERAL}Initial_Conditions_Numerical_Integration.c $(CXXFLAGS)

Random_Initial_Condition.o: ${ODE_DIR_GENERAL}Random_Initial_Condition.c ${HEAD.H}
	${CC} -c ${ODE_DIR_GENERAL}Random_Initial_Condition.c $(CXXFLAGS)

Initial_Condition_from_Parameter_Table.o: ${ODE_DIR}Initial_Condition_from_Parameter_Table.c ${HEAD.H}
	${CC} -c ${ODE_DIR}Initial_Condition_from_Parameter_Table.c $(CXXFLAGS)

Random_Initial_Guess_within_Boundaries.o: ${PROJECT_DIR}Definition_Parameter_Space/Random_Initial_Guess_within_Boundaries.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Parameter_Space/Random_Initial_Guess_within_Boundaries.c $(CXXFLAGS)

JAC_sys_MODEL.o: ${ODE_DEF}JAC_sys_MODEL.c ${HEAD.H}
	$(CC) -c ${ODE_DEF}JAC_sys_MODEL.c $(CXXFLAGS)

JACOBIAN_Matrix_${ODE_MODEL}.o: ${ODE_DEF}JACOBIAN_Matrix_${ODE_MODEL}.c ${HEAD.H}
	$(CC) -c ${ODE_DEF}JACOBIAN_Matrix_${ODE_MODEL}.c $(CXXFLAGS)

ODE_sys_${ODE_MODEL}.o: ${ODE_DEF}ODE_sys_${ODE_MODEL}.c ${HEAD.H}
	$(CC) -c ${ODE_DEF}ODE_sys_${ODE_MODEL}.c $(CXXFLAGS)

# Auxiliary functions to specify model ODE definition
Model_Variables_Code.o: ${PROJECT_DIR}Model_Variables_Code.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Model_Variables_Code.c $(CXXFLAGS)

Total_Effective_Fractions.o: ${PROJECT_DIR}Total_Effective_Fractions.c ${HEAD.H}
	$(CC) -c ${PROJECT_DIR}Total_Effective_Fractions.c $(CXXFLAGS)

Total_Population_Numbers.o: ${PROJECT_DIR}Total_Population_Numbers.c ${HEAD.H}
	$(CC) -c ${PROJECT_DIR}Total_Population_Numbers.c $(CXXFLAGS)

Total_Population_Fractions.o: ${PROJECT_DIR}Total_Population_Fractions.c ${HEAD.H}
	$(CC) -c ${PROJECT_DIR}Total_Population_Fractions.c $(CXXFLAGS)

Total_Disease_Prevalence.o: ${PROJECT_DIR}Total_Disease_Prevalence.c ${HEAD.H}
	$(CC) -c ${PROJECT_DIR}Total_Disease_Prevalence.c $(CXXFLAGS)

Total_Disease_Infection.o: ${PROJECT_DIR}Total_Disease_Infection.c ${HEAD.H}
	$(CC) -c ${PROJECT_DIR}Total_Disease_Infection.c $(CXXFLAGS)

# R_0 related functions:
R_0.o: ${PROJECT_DIR}R_0.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}R_0.c $(CXXFLAGS)

# Funcions to calculate the fixed points of the ODE system
Fixed_Points_All.o: ${ODE_FIXED_POINTS}Fixed_Points_All.c ${HEAD.H}
	$(CC) -c ${ODE_FIXED_POINTS}Fixed_Points_All.c $(CXXFLAGS)

# fixed_ALL_Points_Intersection.o: ${ODE_FIXED_POINTS}fixed_ALL_Points_Intersection.c ${HEAD.H}
#	$(CC) -c ${ODE_FIXED_POINTS}fixed_ALL_Points_Intersection.c $(CXXFLAGS)

Steady_State_x_Fraction.o: ${ODE_FIXED_POINTS}Steady_State_x_Fraction.c ${HEAD.H}
	$(CC) -c ${ODE_FIXED_POINTS}Steady_State_x_Fraction.c $(CXXFLAGS)

Steady_State_y_Fraction.o: ${ODE_FIXED_POINTS}Steady_State_y_Fraction.c ${HEAD.H}
	$(CC) -c ${ODE_FIXED_POINTS}Steady_State_y_Fraction.c $(CXXFLAGS)

x_y_Fixed_Points_Functions.o: ${ODE_FIXED_POINTS}x_y_Fixed_Points_Functions.c ${HEAD.H}
	$(CC) -c ${ODE_FIXED_POINTS}x_y_Fixed_Points_Functions.c $(CXXFLAGS)

x_y_Intersection_Plots.o: ${ODE_FIXED_POINTS}x_y_Intersection_Plots.c ${HEAD.H}
	$(CC) -c ${ODE_FIXED_POINTS}x_y_Intersection_Plots.c $(CXXFLAGS)

intermediateRoot_x_Fraction.o: ${ODE_FIXED_POINTS}intermediateRoot_x_Fraction.c ${HEAD.H}
	$(CC) -c ${ODE_FIXED_POINTS}intermediateRoot_x_Fraction.c $(CXXFLAGS)

Stable_Solution.o: ${ODE_FIXED_POINTS}Stable_Solution.c ${HEAD.H}
	$(CC) -c ${ODE_FIXED_POINTS}Stable_Solution.c $(CXXFLAGS)

Stable_Solution_x.o: ${ODE_FIXED_POINTS}${X_MODEL}/Stable_Solution_x.c ${HEAD.H}
	$(CC) -c ${ODE_FIXED_POINTS}${X_MODEL}/Stable_Solution_x.c $(CXXFLAGS)

Stable_Solution_y.o: ${ODE_FIXED_POINTS}${Y_MODEL}/Stable_Solution_y.c ${HEAD.H}
	$(CC) -c ${ODE_FIXED_POINTS}${Y_MODEL}/Stable_Solution_y.c $(CXXFLAGS)

Generic_Root_Finder.o: ${ODE_FIXED_POINTS}Generic_Root_Finder.c ${HEAD.H}
	$(CC) -c ${ODE_FIXED_POINTS}Generic_Root_Finder.c $(CXXFLAGS)

Feasibility_Condition.o: ${ODE_FIXED_POINTS}Feasibility_Condition.c ${HEAD.H}
	$(CC) -c ${ODE_FIXED_POINTS}Feasibility_Condition.c $(CXXFLAGS)

# Functions involved in controling time dependent dynamics
# time_Oscillations_Parameter_Forcing.o: ${PROJECT_DIR}time_Oscillations_Parameter_Forcing.c ${HEAD.H}
# 	${CC} -c ${PROJECT_DIR}time_Oscillations_Parameter_Forcing.c $(CXXFLAGS)

# Library of generic statistical functions and generic basic libraries to perform stochatic simulations
stat.o:	${PROJECT_DIR}stat.c ${PROJECT_DIR}stat.h
	${CC} -c ${PROJECT_DIR}stat.c $(CXXFLAGS)
#

clean:
	rm -f *.o *~ core
#
COMPILATION_OPTIONS:
	echo "Main model definition compilation options:" > ${EXE}_COMPILATION_OPTIONS.txt
	echo "${ODE_MODEL}"                            >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${CPG}"                                  >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${TYPE_NUMERICAL_INTEGRATION}"           >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "---------------------------------------" >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "All compilation options as passed to the compiler through CXXFLAGS:" >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${CXXFLAGS}"                             >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "---------------------------------------" >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "All linking options as passed to the linker through LDFLAGS, CPGPLOT_LIG and LIBS:" >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "$(LDFLAGS) $(CPGPLOT_LIB) $(LIBS)"                                                  >> ${EXE}_COMPILATION_OPTIONS.txt

run:
	${WKD}${EXE} ${RUN_ARGS}
