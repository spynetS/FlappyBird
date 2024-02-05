##
# Project Title
#
# @file
# @version 0.1
CC = gcc
CCFLAG = -lprinter -lm
all:
	$(CC) $(CCFLAG) ./src/main.c ./src/Flappy.c -o main
run: all
	alacritty -e ./main
# end
