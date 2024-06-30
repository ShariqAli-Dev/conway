build:
	@g++ main.cc -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o conway
run: build
	@./conway
	