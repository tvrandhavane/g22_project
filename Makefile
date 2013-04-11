.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO = /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGET = cs296_base
TARGET1 = cs296_base_analysis

# Project Paths
PROJECT_ROOT=$(HOME)/Videos/g22_project/cs296_base_code
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc
SRCPTDIR = $(PROJECT_ROOT)/scripts

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -O3 -Wall 
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

INSTALL_PATH = $(PROJECT_ROOT)
OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXCLUDES1 := $(filter-out $(OBJDIR)/main.o, $(OBJS)) 
EXCLUDES := $(filter-out $(OBJDIR)/mainwogui.o, $(OBJS))


.PHONY: all setup doc clean dist exe report plot install

all: setup $(BINDIR)/$(TARGET) doc report plot

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p obj
	@mkdir -p bin
	@mkdir -p plots
	@$(ECHO) "Installing Box2D..."
	@$(RM) -rf $(EXTERNAL_ROOT)/src/Box2D $(EXTERNAL_ROOT)/lib/* $(EXTERNAL_ROOT)/include/*
	@tar zxf $(EXTERNAL_ROOT)/src/Box2D.tgz -C $(EXTERNAL_ROOT)/src
	@mkdir -p $(EXTERNAL_ROOT)/src/Box2D/build296
	@cd $(EXTERNAL_ROOT)/src/Box2D/build296; cmake ../; make; make install;

$(BINDIR)/$(TARGET): $(EXCLUDES)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(EXCLUDES) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(OBJS:.o=.d)

$(BINDIR)/$(TARGET1): $(EXCLUDES1)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(EXCLUDES1) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiliimages/ng: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

report: $(DOCDIR)/Report.tex
	@cd $(DOCDIR)/; latex Report.tex; bibtex Report.aux; latex Report.tex;latex Report.tex;dvipdf Report.dvi Report.pdf;
	@cd $(DOCDIR)/; $(RM) *.aux *.dvi *.log *.out *.toc *.blg *.bbl;
	@python3 $(SRCPTDIR)/g22_gen_html.py

makecsv:setup $(BINDIR)/$(TARGET1)
	@$(ECHO) -n "Generating csv file..."
	@python3 $(SRCPTDIR)/g22_gen_csv.py > output
	@$(RM) -rf output

plot: 
	@$(ECHO) -n "Generating plots..."
	@python3 $(SRCPTDIR)/g22_gen_plots.py
	@$(RM) -rf $(BINDIR)/$(TARGET1)


exe:setup $(BINDIR)/$(TARGET)

install:
	@$(ECHO) -n $(INSTALL_PATH)
	@mkdir -p $(INSTALL_PATH)/cs296_base
	@mkdir -p $(INSTALL_PATH)/cs296_base/bin
	@cp $(BINDIR)/$(TARGET) $(INSTALL_PATH)/cs296_base/bin
	@mkdir -p $(INSTALL_PATH)/cs296_base/doc
	@cp -r $(DOCDIR)/html $(INSTALL_PATH)/cs296_base/doc/
	@cp $(DOCDIR)/Report.pdf $(INSTALL_PATH)/cs296_base/doc/
	@cp $(DOCDIR)/Report.html $(INSTALL_PATH)/cs296_base/doc/

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) $(BINDIR) $(DOCDIR)/html plots *~ $(DEPS) $(SRCDIR)/*~
	@$(RM) -rf $(DOCDIR)/Report.html
	@$(ECHO) "Done"

dist: clean
	@$(RM) -rf $(EXTERNAL_ROOT)/lib/* $(EXTERNAL_ROOT)/src/Box2D $(EXTERNAL_ROOT)/include/*
	@tar -zcvf ../cs296_base_code.tar.gz ../cs296_base_code