NAME	=	geofouine

SRCS	= 	utils/utils.cpp 		\
		gps/gps-utils.cpp 		\
		gps/gps-stream-decoder.cpp 	\
		geofouine.cpp

OBJS	=	$(SRCS:.cpp=.o)

INCL= -I. -I$(CURDIR) -I/usr/include/boost/


LDFLAGS 	= 	-L/usr/lib/

LIBS  	= 	-lboost_program_options \
		-lboost_system 		\
		-lcrypto 		\
		-liw

DEFINES	=	-D__PROGNAME__=geofouine \
		-D__PROGVER__=0.5 \

CXXFLAGS= 	$(INCL) \
		-O3 		\
		-std=c++11 	\
		-Wall 		\
		-Wextra 	\
		-fopenmp	\
		$(LIBS)

all:		$(NAME)

$(NAME):	$(OBJS)
		g++
		#g++ $(INCL) $(DEFINES) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)

clean:
		rm -rfv	$(OBJS)

fclean:		clean
		rm -rfv $(NAME)

re:		fclean all

installcheck:
	@check-script $(LIBS)
