#!/bin/bash
# hexo clean && hexo g && cd en &&  hexo clean && hexo g && cd ../ && cp -r en/public/. public/en/ && hexo d

hexo clean && hexo g && cd en &&  hexo clean && hexo g && cd ../ && cp -r en/public/. public/en/  
# && sudo hexo d