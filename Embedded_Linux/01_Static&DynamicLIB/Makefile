#@Copyright : Abdelaziz Maher

# Compiler
CC = 

# Compiler flags
CFLAGS = 
INCS = 


# Directories
SRC_DIR = Src
OBJ_DIR = Lib
APP_DIR = App

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Libraries
STATIC_LIB = $(OBJ_DIR)/LibStatic.a
DYNAMIC_LIB = $(OBJ_DIR)/libDynamic.so

# Output Names
STATIC_OUTPUT = CalcStatic
DYNAMIC_OUTPUT = CalcDynamic
DEFAULT_OUTPUT = Calc

# Default build type
BUILD_TYPE ?= default

all: $(BUILD_TYPE)

default:  
	@$(CC)gcc $(APP_DIR)/main.c $(SRC_DIR)/*.c -o $(DEFAULT_OUTPUT)
	
dynamic: $(OBJ)
	@$(CC)gcc -shared $(OBJ_DIR)/*.o -o $(DYNAMIC_LIB)
	@$(CC)gcc $(APP_DIR)/main.c -Wl,-rpath=./$(OBJ_DIR) -L./$(OBJ_DIR) -lDynamic -o $(DYNAMIC_OUTPUT)  
	
static: $(OBJ)	
	@$(CC)gcc $(APP_DIR)/main.c $(STATIC_LIB) -o $(STATIC_OUTPUT)
	
Lib/%.o: Src/%.c
ifeq ($(BUILD_TYPE),static) 
	@$(CC)gcc -c $(CFLAGS) $(INCS) $(<) -o $(@)
	@$(CC)ar rcs $(STATIC_LIB) $(@)
else ifeq ($(BUILD_TYPE),dynamic)
	@$(CC)gcc -fPIC -c $(INCS) $(CFLAGS) $(<) -o $(@)	
endif	
				
clean:
	@rm -rf $(OBJ_DIR)/*.o 

clean_all:
	@rm -rf $(OBJ_DIR)/*.o $(STATIC_LIB) $(DYNAMIC_LIB) $(DEFAULT_OUTPUT) $(STATIC_OUTPUT) $(DYNAMIC_OUTPUT)


