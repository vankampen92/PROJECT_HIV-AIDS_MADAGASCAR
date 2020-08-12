#/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#/*                                                                           */
#/*                           David Alonso, 2011 (c)                          */
#/*                                                                           */
#/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
PROJECT_DIR=${HOME}/PROJECT_HIV-AIDS_MADAGASCAR/#########

IO_DIR=${PROJECT_DIR}Library/IO_Library/

WKD=${PROJECT_DIR}MODEL_CALCULATIONS/OBSERVED_DATA_FILE_PREPARATION/

INCLUDE_DIR=${PROJECT_DIR}Include##################

EXTRA_LIBRARY_PATH+=-L${IO_DIR}
EXTRA_INCLUDE_PATH+=-I${INCLUDE_DIR}###############
EXTRA_INCLUDE_PATH+=-I${PROJECT_DIR}###############
EXTRA_INCLUDE_PATH+=-I${IO_DIR}

##############################################################################################################
## D E F I N I T I O N   N A M E   E X E C U T B L E   C O D E ###############################################
EXE=Data_File_Generation
##############################################################################################################
EXTERN=#Possibilities: void (to be locally executed) / -static (to be non-locally executed) #
######################################## Possibilities: GA (locally executed) / GA_EXTERN (non-locally executed)
LDFLAGS+=-lm -lda_IO ${EXTRA_LIBRARY_PATH}
CXXFLAGS+=${EXTRA_INCLUDE_PATH} -DHAVE_INLINE ${EXTERN} -g #-Wall
##############################################################################################################
# either -g or some optimization opiton, for instance, -O3

OBJECTS = main.o

### Example:
RUN_ARGS =

CC=gcc##
FF=gfortran##

all: ${EXE} 

${EXE}:  	$(OBJECTS)
		$(CC) -o ${EXE} $(OBJECTS) $(LDFLAGS) $(CXXFLAGS)

# Main program functions:
main.o: main.c 
	$(CC) -c main.c $(CXXFLAGS)

clean:
	rm -f *.o *~ core
#
run:
	${WKD}${EXE} ${RUN_ARGS}
