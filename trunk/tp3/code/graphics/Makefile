all: clean plottear

plottear: data/*.dat plot
	./plot
	ps2pdf eps/grafiquin.eps pdf/grafiquin.pdf
	

clean:
	rm -f eps/grafiquin.eps
