---
title: Zplot Usage
tags: zplot
categories:
  - Tools
date: 2023-07-24 16:41:43
index_img: https://img.xjh.me/random_img.php?type=bg&ctype=nature&return=302
---



#### 1. Zplot-folder Contents

|--breakdown
    |--Makefile
    |--breakdown1.py
    |--breakdown1.data
    |--breakdown2.py
    |--breakdown2.data
|--eval_lineplot
    |--Makefile
|--...
|--makefig.sh

1. You only need to run the ```makefig.sh`` file. If you want to modify the directory where all generated pdfs are located, directly modify makefig.sh

2. The aim of commands in ```Makefile  ``` is mainly to run the current py file to generate the eps file, then use ps2pdf to convert it to pdf and use pdf2crop to crop the generated pdf file

   

   **Note**: Be sure to make the name of the python file same as the name of the data file, otherwise an error will occur.

#### 2. prequisuite

```bash
pip install zplot 
#due to the incompatibility between python2 and python3, there may be a list error. solution: just change the ListType in zplot.py to list.

sudo apt-get install texlive-extra-utils  
```

#### 3. Analyse Makefile

```bash
PY=python
EPS2PDF=ps2pdf
CROP=pdfcrop

SRC := $(wildcard *.py) #list all py files
SRC := $(filter-out zplot.py, $(SRC))
EPS = $(patsubst %.py,%.eps,$(SRC))
PDF = $(patsubst %.py,%.pdf,$(SRC)) #list all generated eps and pdf files

all: $(EPS) $(PDF)

%.eps: %.py  # target file: source file
	$(PY) $< eps  #$< reprents source files  $@ represents target files; Official explanation: $< represents the first dependent file, $@ represents the target set.

%.pdf: %.eps
	$(EPS2PDF) $<
	$(CROP) $@ $@
	rm -rf $<

fig:
	# mv -f *.pdf ../../../fig/	 # move all the files to the image root directory
	mv -f *.pdf ../../
	rm -rf *.eps *.pdf
```
[Reference link for makefile syntax]( https://seisman.github.io/how-to-write-makefile/rules.html)

#### 4. Analyse makefig.sh

```bash

rm -rf *.pdf #Before executing the generation, delete the previously generated pdf file, it should not be necessary

for  dir  in  `find .  -name Makefile`  #Find the dir which containis the Makefile
do
	path=`dirname $dir` #find the path of above dir
    # echo $path
    # echo $dir
	if  [ $path  !=  . ]
	then
	echo $path #print the path
	cd $path  
	make    #run make and makefile command
	make fig
	cd  -
	fi
done

```