include ../../$(PLAT).mk

SRC = $(wildcard $(FEBDIR)FEBio2/*.cpp)
OBJ = $(patsubst $(FEBDIR)FEBio2/%.cpp, %.o, $(SRC))
DEP = $(patsubst $(FEBDIR)FEBio2/%.cpp, %.d, $(SRC))

TARGET =  $(FEBDIR)build/bin/febio2.$(PLAT)

FELIBDIR = $(FEBDIR)build/lib/
FELIBS = -lfecore_$(PLAT) -lfebiolib_$(PLAT) -lfebioplot_$(PLAT) -lfebiomech_$(PLAT) -lfebiomix_$(PLAT) -lfebioxml_$(PLAT) -lnumcore_$(PLAT) -lfebioopt_$(PLAT) -lfebiotest_$(PLAT) -lfebiofluid_$(PLAT)

FEBIOLIBS = -L$(FELIBDIR) -Wl,--start-group $(FELIBS) -Wl,--end-group

$(TARGET): $(OBJ) 
ifeq ($(findstring lnx,$(PLAT)),lnx)
	$(CC) -o $(TARGET) $(DEF) $(FLG) $(INC) $(OBJ) $(FEBIOLIBS) $(LIBS) -ldl
else ifeq ($(findstring gcc,$(PLAT)),gcc)
	$(CC) -o $(TARGET) $(DEF) $(FLG) $(INC) $(OBJ) $(FEBIOLIBS) $(LIBS) -ldl
else ifeq ($(findstring sky,$(PLAT)),sky)
	$(CC) -o $(TARGET) $(DEF) $(FLG) $(INC) $(OBJ) $(FEBIOLIBS) $(LIBS) -ldl
else
	$(CC) -o $(TARGET) $(DEF) $(FLG) $(INC) $(OBJ) $(FELIBS) $(LIBS)
endif

%.o: $(FEBDIR)FEBio2/%.cpp
	$(CC) $(INC) $(DEF) $(FLG) -MMD -c $<

clean:
	$(RM) *.o *.d $(TARGET)

-include $(DEP)
