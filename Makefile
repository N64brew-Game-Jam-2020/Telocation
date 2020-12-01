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

SLIDE_BUILDER_SOURCE = $(wildcard ./slidebuilder/*.go)

slidebuilder/slidebuilder: $(SLIDE_BUILDER_SOURCE)
	go build -o slidebuilder/slidebuilder ./slidebuilder/

LEVELS = cadet_intro \
	robot_intro \
	robot_platform \
	lava_platform \
	switch_tutorial \
	inverted_doors \
	switch_tagteam \
	loop_around \
	radioactive_river \
	double_crossing \
	raised_platform \
	moving_platforms \
	switch_mania \
	raise_robot \
	final

	
LEVEL_GEO = $(foreach level, $(LEVELS), src/levels/$(level)/geo.c)
LEVEL_DATA = $(foreach level, $(LEVELS), levels/$(level).level)

src/levels/%/geo.c: levels/%.level levels/%.meta levelbuilder/levelbuilder
	@mkdir -p $(@D)
	levelbuilder/levelbuilder level $* $< $@

build/spec/level_segs build/spec/level_include src/levels/levels.c src/levels/levels.h: levelbuilder/levelbuilder $(LEVEL_DATA)
	@mkdir -p build/spec
	levelbuilder/levelbuilder levelpack all_levels 0 src/levels/levels.c build/spec/level_segs build/spec/level_include $(LEVELS)

IMAGE_SLIDES = _00_rocket \
	_01_insidecockpit \
	_02_fuelgauge \
	_03_mapcloseup \
	_04_seebutton \
	_05_pushbutton \
	_06_mapchanged \
	_08_rocket_turn \
	_09_see_planet \
	_00_bad_ending \
	_01_see_robot \
	_02_sad_cadet \
	_03_leave_robot \
	_04_leave_planet \
	_00_good_ending \
	_03_leave_with_robot


SLIDE_IMAGES = $(foreach slide, $(IMAGE_SLIDES), imageslides/$(slide).png)
SLIDE_FILES = $(foreach slide, $(IMAGE_SLIDES), imageslides/$(slide)_0x0.551)

imageslides/%_0x0.551: imageslides/%.png
	@mkdir -p $(@D)
	tools/png2n64.py $<

src/cutscene/slides.h src/cutscene/slides.c build/spec/slide_segs build/spec/slide_include: slidebuilder/slidebuilder $(SLIDE_IMAGES)
	slidebuilder/slidebuilder src/cutscene/slides.h src/cutscene/slides.c build/spec/slide_segs build/spec/slide_include $(IMAGE_SLIDES)

COLLISION_SHAPES = solid_block tunnel_block ramp_block stair_block entrance_exit rocket_collision
COLLISION_GEO = $(foreach shape, $(COLLISION_SHAPES), src/collision/geo/$(shape).inc.c)

src/collision/geo/%.inc.c: collision/%.ply levelbuilder/levelbuilder
	@mkdir -p $(@D)
	levelbuilder/levelbuilder collision $* $< $@

src/collision/geo/geo.c: $(COLLISION_GEO)

PLAYER_SOUNDS = sound/clips/Jump.aifc \
	sound/clips/JumpPeakBeep.aifc \
	sound/clips/Landing.aifc \
	sound/clips/AstronautFootsteps.aifc \
	sound/clips/AstronautSlide1.aifc \
	sound/clips/AstronautSlide2.aifc \
	sound/clips/WarpAstronautOnly.aifc \
	sound/clips/WarpRobotOnly.aifc \
	sound/clips/WarpBoth.aifc \
	sound/clips/AstronautDeath_Fall.aifc \
	sound/clips/RobotDeath_Fall.aifc \
	sound/clips/Land_onRobotHead.aifc \
	sound/clips/MetalFootsteps_RoboHead.aifc \
	sound/clips/RobotDestroy.aifc \
	sound/clips/RobotMovement.aifc \
	sound/clips/SwitchBackChar.aifc \
	sound/clips/SwitchChar.aifc \
	sound/clips/BigButton.aifc \
	sound/clips/SmallButton.aifc \
	sound/clips/WarpGoGreen_Big.aifc \
	sound/clips/WarpGoGreen_Small.aifc

PLAYER_SOUNDS_AS_AIF = $(PLAYER_SOUNDS:%.wav=%.aif)

PLAYER_SOUNDS_AS_AIFC = $(PLAYER_SOUNDS_AS_AIFC:%.aif=%.aifc)

sound/clips/%.aif: sound/clips/%.wav
	/home/james/go/src/github.com/lambertjamesd/sfz2n64/sfz2n64 $< $@

sound/clips/%.table: sound/clips/%.aif
	/home/james/go/src/github.com/lambertjamesd/sfz2n64/sfz2n64 $< $@

sound/clips/%.aifc: sound/clips/%.aif sound/clips/%.table
	wine /home/james/Documents/AudioTools/tools/ADPCMENC.EXE -c $(word 2,$^) $< $@

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
	src/audio/soundarray.c \
	src/audio/playersounds.c \
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
	src/cutscene/slides.c \
	src/cutscene/cutscene.c \
	src/cutscene/introcutscene.c \
	src/cutscene/badendingcutscene.c \
	src/cutscene/goodendingcutscene.c \
	src/effects/explosion.c	\
	src/effects/leveltitle.c	\
	src/effects/tutorial.c	\
	src/effects/rockfragments.c	\
	src/effects/shadow.c	\
	src/effects/teleport.c	\
	src/effects/walkanim.c \
	src/font/font.c	\
	src/font/fontrenderer.c	\
	src/font/buttons/buttons.c	\
	src/font/endlessbossbattle/endlessbossbattle.c	\
	src/graphics/dynamic.c	\
	src/graphics/graphics.c	\
	src/graphics/levelgraphics.c	\
	src/graphics/levelthemegraphics.c	\
	src/graphics/renderscene.c	\
	src/input/controller.c  \
	src/input/inputfocus.c  \
	src/level/level.c	\
	src/levels/levels.c \
	src/levelthemes/allthemes.c	\
	src/levelthemes/alienworld/theme.c	\
	src/levelthemes/menu/theme.c	\
	src/math/basictransform.c   	\
	src/math/box.c   \
	src/math/mathf.c   	\
	src/math/plane.c		\
	src/math/quaternion.c   \
	src/math/ray.c   		\
	src/math/vector.c   	\
	src/math/vector2.c   	\
	src/menu/mainmenu.c   	\
	src/menu/menu.c   	\
	src/menu/pausemenu.c   	\
	src/menu/spinninglogo.c   	\
	src/robot/robot.c \
	src/robot/geo/model.c \
	src/rocket/geo/model.c \
	src/rocket/rocket.c \
	src/puzzle/breakable.c  \
	src/puzzle/door.c  \
	src/puzzle/entranceexit.c  \
	src/puzzle/gem.c  \
	src/puzzle/movingplatform.c  \
	src/puzzle/signal.c  \
	src/puzzle/switch.c  \
	src/system/assert.c		\
	src/save/savefile.c	\
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
	src/menu/geo/spinninglogo.c \
	src/system/heapstart.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

DEPS = $(CODEFILES:.c=.d) $(DATAFILES:.c=.d)

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS) build/audio/player.sounds

LCINCS =	-I. -I$(ROOT)/usr/include/PR -I $(ROOT)/usr/include
LCOPTS =	-mno-shared -G 0
LDFLAGS =	$(MKDEPOPT) -L$(ROOT)/usr/lib $(N64LIB) -L$(N64_LIBGCCDIR) -L$(N64_NEWLIBDIR) -lgcc -lc

LDIRT  =	$(APP)

default:	$(TARGETS)

%.d: %.c
	$(CC) $(GCINCS) $(LCINCS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.c=.o)" "$<"

-include $(DEPS)

include $(COMMONRULES)

spec: build/spec/level_segs build/spec/level_include build/spec/slide_segs build/spec/slide_include $(SLIDE_FILES)

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