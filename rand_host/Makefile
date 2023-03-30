CC = gcc
SRCS = random.c
TARGET = random_host

all: $(SRCS)
	gcc $(SRCS) -o $(TARGET)
install: $(SRCS)
	gcc $(SRCS) -o $(TARGET) && \
	cp $(TARGET) /usr/bin && \
	cp RandomHost.service /etc/systemd/system/RandomHost.service
