CC=g++-13
CFLAGS=-O2
IFLAGS=-ICSML/include -Iinclude
LFLAGS=-LCSML -lCSML_Client -lCSML_Server -lSDL2 -lSDL2main -lSDL2_image

DEP=.deps
DEPFLAGS=-MT $@ -MMD -MP -MF $(DEP)/$*.d

CLIENT_OBJ=.obj/client
SERVER_OBJ=.obj/server
OBJ=.obj
CLIENT_SRC=src/client
SERVER_SRC=src/server
SRC=$(CLIENT_SRC) $(SERVER_SRC) 
SRCS=$(foreach DIR,$(SRC),$(wildcard $(DIR)/*.cpp))
CLIENT_SRCS=$(filter $(CLIENT_SRC)/%.cpp, $(SRCS))
SERVER_SRCS=$(filter $(SERVER_SRC)/%.cpp, $(SRCS))
CLIENT_OBJS=$(patsubst $(CLIENT_SRC)/%.cpp, $(CLIENT_OBJ)/%.o, $(CLIENT_SRCS))
SERVER_OBJS=$(patsubst $(SERVER_SRC)/%.cpp, $(SERVER_OBJ)/%.o, $(SERVER_SRCS))

BINDIR=bin
CLIENT_BIN=$(BINDIR)/client
SERVER_BIN=$(BINDIR)/server
BIN=$(CLIENT_BIN) $(SERVER_BIN)

all: $(BIN)

$(CLIENT_BIN): $(CLIENT_OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LFLAGS) -o $@

$(SERVER_BIN): $(SERVER_OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(LFLAGS) -o $@

$(CLIENT_OBJ)/%.o: $(CLIENT_SRC)/%.cpp $(DEP)/%.d | $(DEP) $(OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) $(DEPFLAGS) $< -c -o $@

$(SERVER_OBJ)/%.o: $(SERVER_SRC)/%.cpp $(DEP)/%.d | $(DEP) $(OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) $(DEPFLAGS) $< -c -o $@

$(DEP): ; @mkdir -p $@

$(OBJ): ; @mkdir -p $@

$(BINDIR): ; @mkdir -p $@

CLIENT_DEPFILES=$(patsubst $(CLIENT_SRC)/%.cpp, $(DEP)/%.d, $(CLIENT_SRCS))
SERVER_DEPFILES=$(patsubst $(SERVER_SRC)/%.cpp, $(DEP)/%.d, $(SERVER_SRCS))
DEPFILES=$(CLIENT_DEPFILES) $(SERVER_DEPFILES)
$(DEPFILES):
include $(wildcard $(DEPFILES))

clean:
	rm -rf $(BINDIR)/* $(OBJ)/*.o $(DEP)/*.d
