FLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

SPU_INCLUDES = -I./SPU/headers_spu
CALC_INCLUDES = -I./Calculator/calc_headers
STACL_INCLUDES = -I./stack/headers

SPU_FILES = SPU/spu.cpp SPU/str_func.cpp SPU/main_spu.cpp stack/stack1.cpp stack/checker.cpp SPU/fileopen.cpp
ASM_FILES = SPU/assembler/assembler.cpp SPU/spu.cpp SPU/str_func.cpp SPU/assembler/main_assembler.cpp stack/stack1.cpp stack/checker.cpp SPU/fileopen.cpp
CALC_FILES = Calculator/calculator.cpp Calculator/main.cpp stack/stack1.cpp stack/checker.cpp
VIDEO_FILES = SPU/str_func.cpp video/generator.cpp

all: help

video: $(VIDEO_FILES)
	@echo "-----------------------------------------------------------------------------------------"
	g++ $(FLAGS) $(VIDEO_FILES) $(SPU_INCLUDES) -o video.exe
	@echo "-----------------------------------------------------------------------------------------"


spu: $(SPU_FILES)
	@echo "-----------------------------------------------------------------------------------------"
	g++ $(FLAGS) $(SPU_FILES) $(SPU_INCLUDES) -o spu.exe
	@echo "-----------------------------------------------------------------------------------------"

asm: $(ASM_FILES)
	@echo "-----------------------------------------------------------------------------------------"
	g++ $(FLAGS) $(ASM_FILES) $(SPU_INCLUDES) -o assembler.exe
	@echo "-----------------------------------------------------------------------------------------"

calculator: $(CALC_FILES)
	@echo "-----------------------------------------------------------------------------------------"
	g++ $(FLAGS) $(CALC_FILES) $(CALC_INCLUDES) -o calc.exe
	@echo "-----------------------------------------------------------------------------------------"

run-video: video
	./video.exe

run-spu: spu
	./spu.exe

run-asm: asm
	./assembler.exe

run-calc: calculator
	./calc.exe

clean:
	rm -f spu.exe calc.exe assembler.exe

help:
	@echo "Available commands:"
	@echo "  make spu        - compile SPU"
	@echo "  make asm        - compile assembler"
	@echo "  make video      - compile video"
	@echo "  make calculator - compile calculator"
	@echo "  make run-spu    - compile and run SPU"
	@echo "  make run-video  - compile and run video"
	@echo "  make run-asm    - compile and run assembler"
	@echo "  make run-calc   - compile and run calculator"
	@echo "  make clean      - remove compiled programs" перепиши мейкафал дял винды