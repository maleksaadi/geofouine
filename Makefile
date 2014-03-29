
SOURCES = \
	utils/utils.cpp \
	geofouine.cpp

INCLUDES= -I. -I /usr/include/boost/

# add -fshort-enums if __DIRE__
# (or not, I'm a Makefile, not
# the police)
CFLAGS = -O3 \
	-std=c++11 \
	-Wall \
	-Wextra \
	-fopenmp

LFLAGS = -L/usr/lib/

LIBS  = -lboost_program_options \
	-lboost_system \
	-lcrypto \
	-lgps \
	-liw

# __DIRE__ can be specified to trigger
# memory optimizations (but may result
# in loss of performance) (and may or
# may not result in any significant
# memory optimizations) (also specify
# __48BITS__ with __DIRE__ to enable a
# specific memory model)

DEFINES=\
	-D__PROGNAME__=geofouine \
	-D__PROGVER__=0.5 \


all:	#$(SOURCES)
	g++ $(CFLAGS) \
	$(INCLUDES) $(DEFINES) $(SOURCES) $(LFLAGS) $(LIBS) -o geofouine

clean:
	rm -v *.o
	rm geofouine

installcheck:
	@check-script $(LIBS)
