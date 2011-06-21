all: plot

plot: data/*.dat
	./plot
	ps2pdf eps/grafiquin.eps pdf/grafiquin.pdf

clean:
	rm -f eps/grafiquin.eps
