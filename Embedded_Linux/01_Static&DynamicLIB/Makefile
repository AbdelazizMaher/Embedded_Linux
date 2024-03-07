#@Copyright : Abdelaziz Maher
CC=
CFLAGS=
INCS=
SRC =$(wildcard Src/*.c)
OBJ = $(patsubst Src/%.c, Lib/%.o, $(SRC))

ifeq ($(BUILD_TYPE),static) 
LIBS=Lib/LibStatic.a 
Output_Name=CalStatic
static: static_build
else ifeq ($(BUILD_TYPE),dynamic)
LIBS=Lib/libDynamic.so
Output_Name=CalcDynamic
dynamic: dynamic_build
else
default:
	@$(CC)gcc App/main.c Src/* -o Calc	
endif


dynamic_build: $(OBJ)
	@$(CC)gcc -shared Lib/*.o -o $(LIBS)
	@$(CC)gcc App/main.c -Wl,-rpath=./Lib -L./Lib -lDynamic -o $(Output_Name)  
	
static_build: $(OBJ)	
	@$(CC)gcc App/main.c $(LIBS) -o $(Output_Name) 
	
Lib/%.o: Src/%.c
ifeq ($(BUILD_TYPE),static) 
	@$(CC)gcc -c $(INCS) $(CFLAGS) $(<) -o $(@)
	@$(CC)ar rcs  Lib/LibStatic.a $(@)
else ifeq ($(BUILD_TYPE),dynamic)
	@$(CC)gcc -fPIC -c $(INCS) $(CFLAGS) $(<) -o $(@)	
endif	
	
			
clean:
	@rm Lib/*.o 


