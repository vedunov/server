INC_DIR=../include
INC_FILES+=$(INC_DIR)/server.h
INC_FILES+=$(INC_DIR)/packet.h
VPATH=../tcp_server
SRC_FILES=server_user.c
SRC_FILES+=packet.c
PROG=server_user
OBJS=server_user.o
OBJS+=packet.o
CPPFLAGS+=-I$(INC_DIR)

all: $(PROG)

$(OBJS): $(SRC_FILES) $(INC_FILES)
$(PROG): $(OBJS)
	@echo $<
	$(CC) -o $@ $^
clean:
	@rm -fv $(OBJS) $(PROG)
