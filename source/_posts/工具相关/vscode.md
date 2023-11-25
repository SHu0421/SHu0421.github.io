---
layout: blog
title: vscode 配置
date: 2022-02-25 09:45:56
tags: vscode
index_img: https://img.xjh.me/random_img.php?type=bg&ctype=nature&return=302
---

1. 有关于在macos big sur上配置c/c++程序运行和调试详细步骤：
注意需要安装codellb
https://blog.csdn.net/weixin_44881648/article/details/111046381

2. 设置左边菜单栏：（只能通过放大来设置 ctrl+/-）
{
    "editor.fontSize": 15,
    "window.zoomLevel": 0.5,
}


3. coderunner的设置
settings.json里面
    "code-runner.executorMap": {
        "c": "cd $dir && gcc $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
        "cpp": "cd $dir && g++ -std=c++11 -stdlib=libc++ $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt"
    },
默认设置（不设置这两句话）运行会报错
./forward.cpp:185:42: error: a space is required between consecutive right angle brackets (use '> >')

下面这个问题是由于运行的不是main函数的文件
Undefined symbols for architecture x86_64:
  "_main", referenced from:
     implicit entry/start for main executable
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)


C文件的编译：
```Makefile
cc = gcc
prom = calc
deps = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.c")
obj = $(src:%.c=%.o) 
 
$(prom): $(obj)
    $(cc) -o $(prom) $(obj)
 
%.o: %.c $(deps)
    $(cc) -c $< -o $@
 
clean:
    rm -rf $(obj) $(prom)
```

makefile文件的编写:
https://scc.ustc.edu.cn/zlsc/czxt/200910/W020150417520333830657.pdf

