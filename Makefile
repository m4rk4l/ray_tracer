#
# Makefile
#

CC=-gcc

#DEBUG = -DDBG_PIX -DDBG_WORLD -DDBG_HIT -DDBG_FND -DDBG_AMB
#DEBUG += -DDBG_PIX_2_WORLD
#DEBUG += -DDBG_MAKE_PIXEL -DDBG_CLAMP_INTENSITY
#DEBUG += -DDBG_HITS_PLANE
#DEBUG += -DDBG_HITS_SPHERE -DDBG_SPHERE_GETAMB

INPUT = 640 480 < input/v2/d05.txt 2> runtime.info > img.ppm

# Location of header files
INCDIR = include/
# Location of object files
OBJDIR = objects/
# location of c files
SRCDIR = src/

CFLAGS = -I $(INCDIR) $(DEBUG) -Wall -Wextra -g
LIBS = -lm

# grab all the c files from the src dir
SRC = $(wildcard $(SRCDIR)*.c)

# grab all the c files from the src dir
HEADERS = $(wildcard $(INCDIR)*.h)

# we want objects that dont yet exist so we create them from the list of c
# files.
OBJECTS = $(addprefix $(OBJDIR), $(addsuffix .o, $(basename $(notdir $(SRC)))))

PROG = ray


#---------------------------------------------------------------------------
# builds the .o files from a .c file
#---------------------------------------------------------------------------
$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@ 2> $(@:.o=.err)


#---------------------------------------------------------------------------
# The default compilation
#---------------------------------------------------------------------------
default all: $(PROG)


#---------------------------------------------------------------------------
# Just compiling we require that we have all o files, all o files require
# their correspoinding c file.
#---------------------------------------------------------------------------
$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROG) $(LIBS)



#---------------------------------------------------------------------------
# Clean out all transient files
#---------------------------------------------------------------------------
clean:
	$(RM) $(PROG)
	$(RM) $(OBJECTS)
	$(RM) $(OBJDIR)*.err
	$(RM) runtime.info
	$(RM) img.ppm


#---------------------------------------------------------------------------
# when called, it would run clean, clearscr and compile
#---------------------------------------------------------------------------
fresh: clean clearscr all

clearscr:
	clear

#---------------------------------------------------------------------------
# Run the executable through valgrind
#---------------------------------------------------------------------------
valgrind: clean clearscr all
	valgrind --leak-check=full --malloc-fill=AA --free-fill=BB\
	 --track-origins=yes ./$(PROG) $(INPUT) 



#---------------------------------------------------------------------------
# Run the executable through gdb
#---------------------------------------------------------------------------
gdb: $(PROG)
	gdb $(PROG)



#---------------------------------------------------------------------------
# run executable through ddd
#---------------------------------------------------------------------------
ddd: $(PROG)
	ddd $(PROG)



#---------------------------------------------------------------------------
# Just run the executable
#---------------------------------------------------------------------------
run: $(PROG)
	./$(PROG) $(INPUT)

show:
	display img.ppm
