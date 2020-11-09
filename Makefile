#!smake
include $(ROOT)/usr/include/make/PRdefs

FINAL = YES

ifeq ($(FINAL), YES)
# OPTIMIZER       = -O2 -std=gnu90 -mno-shared
OPTIMIZER       = -g
LCDEFS			= -DNDEBUG -D_FINALROM -Werror
N64LIB          = -lultra_rom
else
OPTIMIZER       = -g -std=gnu90 -mno-shared
LCDEFS          = -DDEBUG -Werror
N64LIB          = -lultra_d
endif

APP =		game.out

TARGETS =	game.n64

GO_SOURCE = $(wildcard ./levelbuilder/*.go)

levelbuilder/levelbuilder: $(GO_SOURCE)
	go build -o levelbuilder/levelbuilder ./levelbuilder/

LEVELS = cadet_intro \
	robot_intro \
	robot_platform \
	lava_platform \
	switch_tutorial \
	debug
	
LEVEL_GEO = $(foreach level, $(LEVELS), src/levels/$(level)/geo.c)
LEVEL_DATA = $(foreach level, $(LEVELS), levels/$(level).level)

src/levels/%/geo.c: levels/%.level levelbuilder/levelbuilder
	@mkdir -p $(@D)
	levelbuilder/levelbuilder level $* $< $@

COLLISION_SHAPES = solid_block tunnel_block ramp_block stair_block
COLLISION_GEO = $(foreach shape, $(COLLISION_SHAPES), src/collision/geo/$(shape).inc.c)

src/collision/geo/%.inc.c: collision/%.ply levelbuilder/levelbuilder
	@mkdir -p $(@D)
	levelbuilder/levelbuilder collision $* $< $@

src/collision/geo/geo.c: $(COLLISION_GEO)

PLAYER_SOUNDS = sound/clips/test.wav

build/audio/player.sounds: $(PLAYER_SOUNDS)
	@mkdir -p $(@D)
	/home/james/go/src/github.com/lambertjamesd/sfz2n64/sfz2n64 $@ $^

DEBUGGERHFILES = src/debugger/serial.h \
	src/debugger/debugger.h

DEBUGGERFILES = src/debugger/serial.c \
	src/debugger/debugger.c

HFILES = $(DEBUGGERHFILES) \
	src/game.h	\
	src/audio/audio.h		\
	src/boot.h		\
	src/graphics/graphics.h

CODEFILES = $(DEBUGGERFILES) \
	src/audio/audio.c		\
	src/audio/audiomgr.c	\
	src/cadet/cadet.c   	\
	src/cadet/geo/model.c \
	src/collision/collisiondata.c \
	src/collision/collisionscene.c \
	src/collision/boxcollision.c \
	src/collision/geo/geo.c \
	src/collision/levelcollisiongrid.c \
	src/collision/meshcollision.c \
	src/collision/sphereactor.c \
	src/collision/sparsecollisiongrid.c \
	src/effects/shadow.c	\
	src/graphics/dynamic.c	\
	src/graphics/graphics.c	\
	src/graphics/levelgraphics.c	\
	src/graphics/levelthemegraphics.c	\
	src/graphics/renderscene.c	\
	src/input/controller.c  \
	src/input/inputfocus.c  \
	src/level/level.c	\
	src/levels/levels.c \
	src/levelthemes/alienworld/theme.c	\
	src/math/basictransform.c   	\
	src/math/mathf.c   	\
	src/math/plane.c		\
	src/math/quaternion.c   \
	src/math/ray.c   		\
	src/math/vector.c   	\
	src/math/vector2.c   	\
	src/robot/robot.c \
	src/robot/geo/model.c \
	src/puzzle/breakable.c  \
	src/puzzle/door.c  \
	src/puzzle/movingplatform.c  \
	src/puzzle/signal.c  \
	src/puzzle/switch.c  \
	src/system/assert.c		\
	src/time/time.c		\
	src/boot.c				\
	src/game.c				\
	src/system/memory.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

CODESEGMENT =	codesegment.o

# Data files that have thier own segments:

DATAFILES =	$(LEVEL_GEO) \
	src/graphics/init.c \
	src/levelthemes/alienworld/materials.c \
	src/system/heapstart.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

DEPS = $(CODEFILES:.c=.d) $(DATAFILES:.c=.d)

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCINCS =	-I. -I$(ROOT)/usr/include/PR -I $(ROOT)/usr/include
LCOPTS =	-mno-shared -G 0
LDFLAGS =	$(MKDEPOPT) -L$(ROOT)/usr/lib $(N64LIB) -L$(N64_LIBGCCDIR) -L$(N64_NEWLIBDIR) -lgcc -lc

LDIRT  =	$(APP)

default:	$(TARGETS)

%.d: %.c
	$(CC) $(GCINCS) $(LCINCS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.c=.o)" "$<"

-include $(DEPS)

include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

ifeq ($(FINAL), YES)
$(TARGETS) $(APP):      spec $(OBJECTS)
	$(MAKEROM) -s 9 -r $(TARGETS) spec
	makemask $(TARGETS)
else
$(TARGETS) $(APP):      spec $(OBJECTS)
	$(MAKEROM) -r $(TARGETS) spec
endif

cleanall: clean
	rm -f $(CODEOBJECTS) $(OBJECTS) $(DEPS)