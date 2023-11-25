#!/bin/bash
# hexo clean && hexo g && cd en &&  hexo clean && hexo g && cd ../ && cp -r en/public/. public/en/ && hexo d
# git config --global --unset http.proxy;
# git config --global --unset https.proxy;
# git config --global user.name "SHu0421" ;
# git config --global user.email "1320517578@qq.com";
hexo clean && hexo g && cd en &&  hexo clean && hexo g && cd ../ && cp -r en/public/. public/en/  && hexo d