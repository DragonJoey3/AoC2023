default: compile

compile:
	g++ -g -o executable main.cpp

test: compile
	cp example.txt aoc.txt
	./executable

run: compile
	cp input.txt aoc.txt
	./executable

clean:
	rm aoc.txt
	rm executable
