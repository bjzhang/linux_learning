# git submodule example
https://github.com/bjzhang/git_submodule_test

git submodule是管理子模块的工具。
## 使用submodule
### checkout代码
- 在git clone时一起clone：git clone --recurse-submodules git@github.com:bjzhang/git_submodule_test.git
- clone时没有一起clone：git submodule update --init，是否加checkout是一样的。
- git submodule update --init。为什么这里不需要checkout呢？"If neither is given, a checkout is performed."。但是单独加--checkout不加--init是不行的。
## 新建submodule
默认命令是git submodule add git_remote，和git remote add alias git_remote非常类似。例如git submodule add git@github.com:bjzhang/linux_learning.git。会在当前目录建立名为仓库名字（例如例子的linux_learning）的目录。如果希望指定不同的名字，可以写成git submodule add git_remote dest_dir

和git clone一样，新建也可以是ssh协议，例如希望从本地某个机器clone: git submodule add bamvor@10.211.55.2:/Users/bamvor/works/open_log

## 更新submodule remote地址
上面的open_log repo通过本地clone之后，希望更新为remote：git submodule add -f git@github.com:bjzhang/open_log.git
从remote更新submodule：git submodule update --remote
