# ##############################################################################
#
# Informática Gráfica (Grado Informática)
# Makefile (sirve para Linux y macOS)
#
# ##############################################################################

.SUFFIXES:
.PHONY: x

exe             := pracs_exe
units_cc        := $(wildcard $(addprefix src/, *.cc)) $(wildcard $(addprefix src/, *.cpp))
units_o         := $(addprefix obj/, $(addsuffix .o, $(notdir $(basename $(units_cc)))))
headers         := $(wildcard $(addprefix include/, *.h*))
uname           := $(shell uname -s)
en_macos        := $(findstring Darwin,$(uname))
en_linux        := $(findstring Linux,$(uname))
compiler        := $(if $(en_linux), g++, clang++ )
sistoper        := $(if $(en_macos), macOS, Linux )

cc_flags_common := -std=c++11 -g -I/usr/include -I./include
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
	./$(exe)

$(exe): $(units_o) makefile
	$(compiler) -o $(exe)  $(units_o) $(ld_libs)

%.o : %.cc
	$(compiler) -c  $(cc_flags) $<

%.o : %.cpp
	$(compiler) -c  $(cc_flags) $<

$(units_cc) : $(headers)
	touch $(units_cc)

clean:
	rm -rf *.o *_exe

echo:
	@echo $(units_cc)
	@echo $(headers)
	@echo $(units_o)
	@echo $(compiler) -o $(exe)  $(units_o) $(ld_libs)
	@echo $(compiler) -c  $(cc_flags) $<
	@echo $(exe): $(units_o) makefile
