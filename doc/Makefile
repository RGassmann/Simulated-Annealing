TEXFILES = sa.tex sadoc.tex

SimulatedAnnealing.pdf:	sadoc.tex $(TEXFILES) sadoc.ind 
	pdflatex sadoc.tex

sadoc.ind:	sadoc.tex $(TEXFILES)
	touch sadoc.ind
	pdflatex sadoc.tex
	makeindex sadoc.idx
