---
title: Build Anaconda Environment
tags: Tools
categories:
  - Tools
date: 2023-07-24 16:40:16
---

#### Problem description

A server already has a set-up environment, but it needs to be migrated to another server, or another user needs to access the same environment. If the other server does not have the anaconda environment installed, then it needs to be installed from scratch, and then migrated.


#### Solution


1. Install anaconda3
```
# Download the anaconda3 installer using the following command:
wget https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/Anaconda3-5.3.1-Linux-x86_64.sh

#Execute the downloaded set-up file using the following command:
bash Anaconda3-5.3.1-Linux-x86_64.sh
```

​		During the process, the user may need to choose between ```no``` or ```yes```. in a 		selection pop-up. By Default, it will choose ```yes```. If ```no``` is selected, the user 		can manually add the environment. ([Reference Material](https://zhuanlan.zhihu.com/p/64930395), you can also refer to 		the method 2 in the following Step2: Activate environment)

2. Activate environment
    2.1 method 1 ( invalid sometimes )

    Open the ```.bashrc``` configuration file by using command```vim ~/.bashrc```. At the end of the file, add the following line:
    ```
    export PATH=/root/xxx/anaconda3/bin:$PATH
    ```
    ```/root/xxx``` is the installation directory. Save the file and exit, then run source  command ```~/.bashrc``` to activate environment.

    2.2 method 2 (invalid)
    Open profile by command```vi /etc/profile```. At the end, add:
    ```
    PATH=$PATH:/opt/anaconda3/bin
    export PATH
    ```
    Save the file and exit. Then, refresh the environment variables with:

    ```bash
    source /etc/profile
    echo $PATH
    ```

​				PS: If some problem reminder occor, use ```sudo vi ~/.bashrc``` to see 	    				whether the conda path is right.

   3. Anaconda Commands

      ```bash
      conda list # see the installation package
      conda info --envs # see the environment
      conda activate XXX # activate environment, XXX represent the environment name
      python -V #check python version
      
      # remove the anaconda
      rm -rf /root/xxx/anaconda
      ```

   4. migrate environment by``` conda-pack```

      In the source machine:

      ```bash
      conda pack -n env-name --ignore-editable-packages
      #important, error will occour without --ignore-editable-packages 
      ```

      then we get an compressed package named env_name.tar.gz,

      In the target machine:

      ```bash
      cd ~/anaconda3/envs;
      mkdir env_name;
      tar -xzvf env_name.tar.gz -C /home/root_name/anaconda3/envs/env_name
      ```

      

			4.  use the new environment

​				``` source activate attnGAN ```

​				Notice that use command ```conda activate``` will cause error sometimes. 				[Solution reference](https://blog.csdn.net/qq_43828332/article/details/114235922)

#### Reference Materials

​	[reference 1](https://blog.csdn.net/lwgkzl/article/details/89329383)

​	[reference 2](https://www.jianshu.com/p/1fddd11bcd25)

[	reference 3](https://blog.csdn.net/ds1302__/article/details/120027173)

#### Related Problems

1. Problem 1: run ```conda info --envs```, get info ```conda: command not found```

   Reason:  the ~/.bashrc file was not configured rightly.

   Solution:

   ``` bash
   sudo vim ~/.bashrc
   # add the following line at the end of the file
   export PATH=$PATH:/home/vincent/anaconda3/bin
   ```