# ##############################################################################
#
# Informática Gráfica (Grado Informática)
# Makefile (sirve para Linux y macOS)
#
# ##############################################################################

.SUFFIXES:
.PHONY: x

OBJ 				 := obj/
SRC				 := src/
INC    			 := include/
exe             := bin/pracs_exe
units_cc        := $(wildcard $(addprefix $(SRC), *.cc))
units_o         := $(addprefix $(OBJ), $(addsuffix .o, $(notdir $(basename $(units_cc)))))
headers         := $(wildcard $(addprefix $(INC), *.h*))
uname           := $(shell uname -s)
en_macos        := $(findstring Darwin,$(uname))
en_linux        := $(findstring Linux,$(uname))
compiler        := $(if $(en_linux), g++, clang++ )
sistoper        := $(if $(en_macos), macOS, Linux )

cc_flags_common := -std=c++11 -g -I/usr/include -I$(INC)
cc_flags_linux  := -DLINUX
cc_flags_macos  := -DMACOS
cc_flags        := $(cc_flags_common) $(if $(en_linux), $(cc_flags_linux), $(cc_flags_macos))

glu_flag_macos  := /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGLU.dylib
ld_libs_common := -ljpeg
ld_libs_linux  := -lGLEW -lGLU -lglut -lGL
ld_libs_macos  := -framework OpenGL -framework GLUT $(glu_flag_macos)
ld_libs        := $(ld_libs_common) $(if $(en_linux), $(ld_libs_linux), $(ld_libs_macos))


x: $(exe)
	@echo Enlazando para: $(sistoper)
	$(exe)

$(exe): $(units_o) makefile
	$(compiler) -o $(exe)  $(units_o) $(ld_libs)

$(OBJ)%.o : $(SRC)%.cc
	$(compiler) -o $@ -c $(cc_flags) $<

$(OBJ)%.o : $(SRC)%.ccp
	$(compiler) -o $@ -c $(cc_flags)

$(units_cc) : $(headers)
	touch $(units_cc)

clean:
	rm -rf obj/*.o bin/*_exe
