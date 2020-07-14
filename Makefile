####################################################################
# Makefile                                                         #
####################################################################

.SUFFIXES: all				
.PHONY: clean all dox splint

####################################################################
# Path Definitions                                                 #
####################################################################
OUT_DIR     = ./output
OBJ_DIR     = $(OUT_DIR)/build
EXE_DIR     = $(OUT_DIR)/exe
DOX_DIR     = $(OUT_DIR)/docu
SRC_DIR     = ./src
INCLUDE_DIR = ./include

####################################################################
# Flag Definitions                                                 #
####################################################################
FLAGS = -Wall -c -ansi -g

SPLINTFLAGS = +skip-sys-headers +posixlib +standard +matchanyintegral -mustfreeonly \
			  -likelybool -dependenttrans -noeffect -exportlocal -usedef \
			  -temptrans -nullstate -mustdefine -compdef -compdestroy \
			  -unrecog -nullpass +slashslashcomment -unreachable
## -warnposix -preproc 
INCLUDEPATHS =-I$(INCLUDE_DIR)

####################################################################
# Create build and ouput directory								   #
####################################################################
$(OBJ_DIR):
	mkdir -p $(OUT_DIR)
	mkdir -p $(OBJ_DIR)
	@echo "Created build directory."

$(EXE_DIR):
	mkdir -p $(EXE_DIR)
	@echo "Created executable directory."

####################################################################
# Build instructions			 								   #
####################################################################
all: $(OBJ_DIR) $(EXE_DIR) $(EXE_DIR)/covlist

$(EXE_DIR)/covlist: $(OBJ_DIR)/main.o $(OBJ_DIR)/str_serialize.o $(OBJ_DIR)/opt.o 
	gcc $(OBJ_DIR)/main.o $(OBJ_DIR)/str_serialize.o $(OBJ_DIR)/opt.o -o $(EXE_DIR)/covlist

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c 
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.c 

$(OBJ_DIR)/str_serialize.o: $(SRC_DIR)/str_serialize.c $(INCLUDE_DIR)/str_serialize.h
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/str_serialize.o $(SRC_DIR)/str_serialize.c

$(OBJ_DIR)/opt.o: $(SRC_DIR)/opt.c $(INCLUDE_DIR)/opt.h
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/opt.o $(SRC_DIR)/opt.c

dox:
	mkdir -p $(DOX_DIR)
	@echo "Created doxygen directory."

	doxygen ./doc/covlist.dox

splint:
	splint $(SPLINTFLAGS) $(INCLUDEPATHS) $(SRC_DIR)/main.c
	splint $(SPLINTFLAGS) $(INCLUDEPATHS) $(SRC_DIR)/str_serialize.c
	splint $(SPLINTFLAGS) $(INCLUDEPATHS) $(SRC_DIR)/opt.c

clean:
	rm -rf $(OBJ_DIR) $(DOX_DIR) $(EXE_DIR) $(OUT_DIR) 
