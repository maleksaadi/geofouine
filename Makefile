NAME	=	geofouine

SRCS	= 	utils/utils.cpp 		\
		gps/gps-utils.cpp 		\
		gps/gps-stream-decoder.cpp 	\
		geofouine.cpp

OBJS	=	$(SRCS:.cpp=.o)

INCL	=	-I. -I /usr/include/boost/

CFLAGS 	= 	-O3 		\
		-std=c++11 	\
		-Wall 		\
		-Wextra 	\
		-fopenmp

LFLAGS 	= 	-L/usr/lib/

LIBS  	= 	-lboost_program_options \
		-lboost_system 		\
		-lcrypto 		\
		-liw

DEFINES	=	-D__PROGNAME__=geofouine \
		-D__PROGVER__=0.5 \


all:		$(NAME)

$(NAME):	$(OBJS)
		g++ $(CFLAGS) $(INCL) $(DEFINES) $(OBJS) $(LFLAGS) $(LIBS) -o $(NAME)

clean:
		rm -rfv	$(OBJS)

fclean:		clean
		rm -rfv $(NAME)

re:		fclean all

installcheck:
	@check-script $(LIBS)
