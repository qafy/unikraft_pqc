LATEX=lualatex
BIBTEX=biber
SRC=document.tex
BIB=document.bib
OUT=document.pdf

all: $(OUT) 

$(OUT): $(SRC) $(BIB)
	$(LATEX) $(SRC)
	$(BIBTEX) $(basename $(SRC))
	$(LATEX) $(SRC) 

clean:
	rm -f *.aux *.bcf *.bbl *.blg *.log *.out *.run.xml *tex.bbl *.tex.blg *.toc $(OUT)

.PHONY: all clean