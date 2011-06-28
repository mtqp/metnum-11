all: informe.pdf

informe.pdf: informe.tex teoria.tex desarrollo.tex resultados.tex discusion.tex conclusiones.tex referencias.tex enunciado.tex gregory.tex machin.tex ramanujan.tex
	latex informe
	latex informe
	latex informe.tex dvips -p pdf
	dvipdf informe.dvi informe.pdf
	rm informe.dvi

clean:
	rm -f informe.pdf *.toc *.log *.aux *.bbl *.blg