#
# Lista dos arquivos fonte
#  Inclua seus arquivos aqui
#
FONTES = startup.c main.c

#
# Arquivos de saída
#  Altere se quiser
#
EXEC = kernel.elf
MAP = kernel.map

PREFIXO = arm-none-eabi-
LDSCRIPT = kernel.ld
AS = ${PREFIXO}as
LD = ${PREFIXO}ld
GCC = ${PREFIXO}gcc
OBJ = $(FONTES:.s=.o)
OBJETOS = $(OBJ:.c=.o)

#
# Opções do compilador C
#
OPTS = -g -mcpu=cortex-m4 -mthumb -nostdlib

#
# Opções do linker
#
LDOPTS = -L/usr/lib/gcc/arm-none-eabi/10.3.1/ -L/usr/lib/arm-none-eabi/lib
LDOPTS += -lc -lgcc

#
# Gerar executável
#
${EXEC}: ${OBJETOS}
		${LD} -T ${LDSCRIPT} -M=${MAP} ${OBJETOS} ${LDOPTS} -o $@

#
# Compilar arquivos em C
#
.c.o:
	${GCC} ${OPTS} -c -o $@ $<

#
# Montar arquivos em assembler
#
.s.o:
	${AS} -g -o $@ $<

#
# Limpar tudo
#
clean:
	rm -f *.o ${EXEC} ${MAP}

#
# Iniciar openocd
#
ocd: 
	@if pgrep openocd >/dev/null ; then\
		echo "openocd já está executando"; \
	else openocd -f evaluator7t.cfg & \
	fi

#
# Iniciar gdb
#
gdb: ${EXEC}
	gdb-multiarch -ex "set architecture arm" \
		      -ex "target extended-remote :3333" \
		      -ex "shell sleep 0.5" \
		      -ex "monitor init" \
		      -ex "shell sleep 0.5" \
		      -ex "monitor halt" \
		      -ex "shell sleep 0.5" \
		      -ex "load" \
					  ${EXEC}


