all: inv_vs_lu ajuste_epsilon
	
inv_vs_lu: plot_inv_vs_lu 
	./plot_inv_vs_lu
	ps2pdf graficos/inv_vs_lu.eps ../informe/graficos/inv_vs_lu.pdf

ajuste_epsilon: plot_ajuste_epsilon
	./plot_ajuste_epsilon
	ps2pdf graficos/ajuste_epsilon.eps ../informe/graficos/ajuste_epsilon.pdf
	
clean:
	rm graficos/*.eps
	rm ../informe/graficos/*.pdf