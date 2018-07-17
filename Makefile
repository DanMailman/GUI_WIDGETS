EXE  = TstWdg
CC = g++
CFLAGS = -g -Wall -Wno-write-strings -std=c++17
LFLAGS = -L../lib -lboost_iostreams -lboost_system -lfltk

BASE_NAMES = Utilities tWndW tHimW tWdgD tBtnW tInpW tPolyWD 
SRC = $(BASE_NAMES:=.cpp) TstWdg.cpp

#$(info SRC="$(SRC)")

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@  $(LFLAGS) $(LIBS)
