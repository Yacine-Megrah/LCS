all: $(prog).c
	gcc ./src/$(prog).c -o ./bin/$(prog).exe;
	./bin/$(prog).exe;
