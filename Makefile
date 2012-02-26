TARGET = Puzzlesquare

OBJDIRBASE = obj
DEPDIRBASE = dep
TARGETDIRBASE = bin

CPP = g++
ECHO = echo
RM = rm
CP = cp
MKDIR = mkdir
MAKE = make
EXIT = exit
LS = ls

CPPFILES = $(shell $(LS) -t *.cpp)

CPPFLAGS = `sdl-config --cflags`
LFLAGS = `sdl-config --libs` -lSDL_image -lSDL_ttf

OBJDIR = $(OBJDIRBASE)/$(CFGSUBDIR)
DEPDIR = $(DEPDIRBASE)/$(CFGSUBDIR)
TARGETDIR = $(TARGETDIRBASE)/$(CFGSUBDIR)

TARGETFILE = $(TARGETDIR)/$(TARGET)
OBJFILES = $(CPPFILES:%.cpp=$(OBJDIR)/%.o)
DEPFILES = $(CPPFILES:%.cpp=$(DEPDIR)/%.d)

$(TARGETFILE): dirs $(OBJFILES)
	@$(ECHO) "Linking" $(TARGETFILE)...
	@$(CPP) $(LFLAGS) $(OBJFILES) -o $(TARGETFILE)
	@$(CP) square.png $(TARGETDIRBASE)
	@$(CP) Verdana.ttf $(TARGETDIRBASE)

$(OBJDIR)/%.o: %.cpp
	@$(MKDIR) -p $(OBJDIR) $(DEPDIR)
	@$(ECHO) "Compiling" $*.cpp...
	@$(CPP) $(CPPFLAGS) -c $*.cpp -o $(OBJDIR)/$*.o
	@$(CPP) $(CPPFLAGS) -MM $*.cpp >> $(DEPDIR)/$*.d
	@$(ECHO) -n $(OBJDIR)"/" > $(DEPDIR)/$*.d ; $(CPP) $(CPPFLAGS) -MM $*.cpp >> $(DEPDIR)/$*.d
	
dirs:
	@$(MKDIR) -p $(OBJDIR) $(DEPDIR) $(TARGETDIR)
