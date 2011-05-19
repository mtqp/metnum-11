all: inv_vs_lu prom_vs_direct ajuste_epsilon
	
inv_vs_lu: plot_inv_vs_lu
	./plot_inv_vs_lu
	ps2pdf graficos/inv_vs_lu.eps ../informe/graficos/inv_vs_lu.pdf
	ps2pdf graficos/inv_vs_lu_promedio.eps ../informe/graficos/inv_vs_lu_promedio.pdf

prom_vs_direct: plot_prom_vs_direct
	./plot_prom_vs_direct
	ps2pdf graficos/prom_vs_direct.eps ../informe/graficos/prom_vs_direct.pdf

ajuste_epsilon: plot_ajuste_epsilon
	./plot_ajuste_epsilon
	ps2pdf graficos/ajuste_epsilon.eps ../informe/graficos/ajuste_epsilon.pdf
	
clean:
	rm graficos/*.eps
	rm ../informe/graficos/*.pdf