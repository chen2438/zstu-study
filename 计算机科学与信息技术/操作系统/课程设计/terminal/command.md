## 测试命令 chsh.v3

```bash
ls
login
login root 111
login root password
cd /
mkdir /dir
mkdir /dir/subdir
ls -l

cd /dir/subdir
# pwd
touch /dir/subdir/1.txt
mkdir /dir/subdir/subsubdir
ls -l

rm /dir/subdir/1.txt
ls -l
rm /dir/subdir/subsubdir
ls -l

cd /
ls -l
chmod 000 /dir
cd /dir
chmod 700 /dir
cd /dir
ls -l
adduser user1 pass1
# passwd user1 pass2
su user1 pass1
cd /
cd /dir
touch /2.txt
ls -l


# 开两个终端
# 终端1
login root password
cd /
touch /1.txt
chmod 770 /1.txt
# goto 2
chmod 774 /1.txt #r
chmod 776 /1.txt #rw
vim /1.txt
123
:wq

#终端2
login user1 pass1
cd /
cat /1.txt
vim /1.txt
```

