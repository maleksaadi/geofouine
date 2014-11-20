NAME		=	geofouine

SRCS		= 	main.cpp			\
			utils/utils.cpp 		\
			gps/gps-utils.cpp 		\
			gps/gps-stream-decoder.cpp 	\
			Wifi.cpp			\
			Gps.cpp

OBJS		=	$(SRCS:.cpp=.o)

CXXFLAGS	=	-O3 		\
			-std=c++11 	\
			-W		\
			-Wall		\
			-Wextra		\
			-Werror		\
			-fopenmp	\
			-I$(CURDIR)	\
			-I/usr/include/boost/

LDFLAGS 	=	-L/usr/lib/		\
			-lboost_program_options \
			-lboost_system 		\
			-lcrypto 		\
			-liw			\
			-lpthread

DEFINES		=	-D__PROGNAME__=geofouine \
			-D__PROGVER__=0.5 \

all:			$(NAME)

$(NAME):		$(OBJS)
			g++ -o $(NAME) $(OBJS) $(DEFINES) $(LDFLAGS)

clean:
			rm -v	$(OBJS)

fclean:			clean
			rm -v $(NAME)

re:			fclean all

installcheck:
			@check-script $(LIBS)