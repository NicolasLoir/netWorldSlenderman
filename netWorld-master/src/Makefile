include ../config

all: testNetWorld testIA testUtils slenderman

testNetWorld: networld.o edge.o node.o tests/testNetworld.o utils.o
	$(CC) -o ../nw-$@ $^ $(LIBS)

testIA: networld.o edge.o node.o ia.o entity.o tests/testIA.o utils.o aStar.o
	$(CC) -o ../nw-$@ $^ $(LIBS)

testUtils: tests/testUtils.o utils.o
	$(CC) -o ../nw-$@ $^ $(LIBS)

slenderman: networld.o edge.o node.o ia.o entity.o utils.o game.o gameMain.o aStar.o event.o gameEntity.o audio.o menu.o
	$(CC) -o ../nw-$@ $^ $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o tests/*.o
