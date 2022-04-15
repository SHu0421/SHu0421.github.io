---
title: Zplot画图相关知识点
tags: zplot
categories:
  - 工具相关
date: 2022-01-04 16:04:52
---


Zplot-folder
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

1. 每次运行的时候只需要运行makefig文件就可以了，如果要修改所有生成的pdf在的目录，直接修改makefig.sh

2。 Makefile里面的文件主要是运行当前py文件生成eps文件，然后使用ps2pdf转为pdf并使用pdf2crop对生成的pdf文件进行裁剪
PS：一定要注意python文件的名字一定要和data文件名字相同，否则会报错


prequisuite

```bash
pip install zplot 
#注意可能会出现list错误，可能是由于python2 和python3的不兼容原因，只需要将zplot.py里面的ListType改为list就可以了

sudo apt-get install texlive-extra-utils  
```

Makefile文件分析
```bash
PY=python
EPS2PDF=ps2pdf
CROP=pdfcrop

SRC := $(wildcard *.py) #列出所有文件对应的py文件
SRC := $(filter-out zplot.py, $(SRC))
EPS = $(patsubst %.py,%.eps,$(SRC))
PDF = $(patsubst %.py,%.pdf,$(SRC)) #列出所有文件对应的eps和pdf文件

all: $(EPS) $(PDF)

%.eps: %.py  # 目标文件： 源文件
	$(PY) $< eps  #$< 表示源文件  $@表示目标文件//官方解释： $< 表示第一个依赖文件， $@ 表示目标集

%.pdf: %.eps
	$(EPS2PDF) $<
	$(CROP) $@ $@
	rm -rf $<

fig:
	# mv -f *.pdf ../../../fig/	 #将所有的文件都转移到zplot对应的root目录下面
	mv -f *.pdf ../../
	rm -rf *.eps *.pdf
```
makefile语法的参考链接： https://seisman.github.io/how-to-write-makefile/rules.html 


makefig.sh文件分析
```bash

rm -rf *.pdf #这是我自己家的，在执行生成之前，现将之前生成的pdf文件删除，应该是也不用

for  dir  in  `find .  -name Makefile`  #找到包含Makefile文件的dir
do
	path=`dirname $dir` #找到dir对应的路径path
    # echo $path
    # echo $dir
	if  [ $path  !=  . ]
	then
	echo $path #打印出path的路径
	cd $path  
	make    #执行make和makefig命令
	make fig
	cd  -
	fi
done

```