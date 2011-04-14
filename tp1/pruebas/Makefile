all: digitos terminos cotas

digitos: plot_comparacion_1a42it_51p
	./plot_comparacion_1a42it_51p
	ps2pdf truncamiento/graficos/comparacion_1a42it_51p.eps ../informe/graficos/comparacion_1a42it_51p.pdf
	ps2pdf truncamiento/graficos/comparacion_machin-ram.eps ../informe/graficos/comparacion_machin-ram.pdf

terminos: plot_comparacion_42it_1a51p
	./plot_comparacion_42it_1a51p
	ps2pdf truncamiento/graficos/comparacion_42it_1a51p.eps ../informe/graficos/comparacion_42it_1a51p.pdf
	ps2pdf truncamiento/graficos/comparacion_5it_1a51p.eps ../informe/graficos/comparacion_5it_1a51p.pdf

cotas: plot_cotas 
	./plot_cotas
	ps2pdf truncamiento/graficos/cotas.eps ../informe/graficos/cotas.pdf
	
clean:
	rm truncamiento/graficos/*.eps

clean_all:
	rm truncamiento/graficos/*.eps
	rm ../informe/graficos/*.pdf
