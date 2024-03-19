# OS specific part
# -----------------
ifeq ($(OS),Windows_NT)
    RM = del /F /Q
    RMDIR = -RMDIR /S /Q
    MKDIR = -mkdir
    ERRIGNORE = 2>NUL || (exit 0)
    SEP=\\
else
    RM = rm -rf 
    RMDIR = rm -rf 
    MKDIR = mkdir -p
    ERRIGNORE = 2>/dev/null
    SEP=/
endif

PROG                =   Assignment_4
SRC_DIR             =   src
BUILD_DIR           =   build
HEADER_DIR          =   include

SRC                 =   $(wildcard ${SRC_DIR}/*.c)
OBJ                 =   $(patsubst ${SRC_DIR}/%.c, ${BUILD_DIR}/%.o, ${SRC})
HEX_FILE            =   ${PROG}.hex

PORT               ?=   /dev/ttyACM0
MMCU                = 	atmega2560

# Compiler- and -flags
CC                  =   avr-gcc
CFLAGS              =   -mmcu=${MMCU} -Os -Wall -Wextra
CPPFLAGS            =   -I${HEADER_DIR}	
LDFLAGS             =   

# Objcopy- and -flags
OBJCOPY             =   avr-objcopy
OBJCOPY_FLAGS       =   -O ihex -R .eeprom

# Avrdude- and -flags
AVRDUDE             =   avrdude
AVRDUDE_flags       =   -p m2560 -c stk500v2 -P ${PORT} -b 115200 #-C /etc/avrdude/avrdude.conf # TODO: check OS and include the correct path on Windows



all: build/${HEX_FILE}

build/%.o: ${SRC_DIR}/%.c | ${BUILD_DIR}
	$(CC) ${CFLAGS} ${CPPFLAGS} -c $< -o $@

build/%.hex: build/${PROG}
	$(OBJCOPY) ${OBJCOPY_FLAGS} $< $@

build/${PROG}: ${OBJ} | ${BUILD_DIR}
	$(CC) ${CFLAGS} ${LDFLAGS} -o $@ ${OBJ}

${BUILD_DIR}:
	${MKDIR} ${BUILD_DIR}

flash: build/${HEX_FILE}
	$(AVRDUDE) ${AVRDUDE_flags} -D -U flash:w:$<

clean:
	${RMDIR} build

.PHONY: all flash clean
