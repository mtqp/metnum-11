data_digitos = truncamiento/data/gregory/gregory_1a42it_51p.dat truncamiento/data/machin/machin_1a42it_51p.dat truncamiento/data/ramanujan/ramanujan_1a42it_51p.dat
data_terminos = truncamiento/data/gregory/gregory_42it_1a51p.dat truncamiento/data/machin/machin_42it_1a51p.dat truncamiento/data/ramanujan/ramanujan_42it_1a51p.dat	

all: digitos terminos

digitos: plot_comparacion_1a42it_51p $(data_digitos)
	./plot_comparacion_1a42it_51p
	ps2pdf truncamiento/graficos/comparacion_1a42it_51p.eps ../informe/graficos/comparacion_1a42it_51p.pdf

terminos: plot_comparacion_42it_1a51p $(data_terminos)
	./plot_comparacion_42it_1a51p
	ps2pdf truncamiento/graficos/comparacion_42it_1a51p.eps ../informe/graficos/comparacion_42it_1a51p.pdf

clean:
	rm truncamiento/graficos/*.eps

clean_all:
	rm truncamiento/graficos/*.eps
	rm ../informe/graficos/*.pdf
