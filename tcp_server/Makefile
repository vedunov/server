INC_DIR=../include
INC_FILES+=$(INC_DIR)/packet.h
INC_FILES+=$(INC_DIR)/conn.h
INC_FILES+=$(INC_DIR)/packet_queue.h
INC_FILES+=$(INC_DIR)/conn_queue.h
SRC_FILES=server.c
PROG=server
OBJS=server.o packet.o packet_queue.o conn.o conn_queue.o
CPPFLAGS+=-I$(INC_DIR)
CPPFLAGS+=${DEBUG}

all: $(PROG)

$(OBJS): $(SRC_FILES) $(INC_FILES)
$(PROG): $(OBJS)
	$(CC) -o $@ $^
clean:
	@rm -fv $(OBJS) $(PROG)
