在Web开发中制作[个人简历](https://so.csdn.net/so/search?q=%E4%B8%AA%E4%BA%BA%E7%AE%80%E5%8E%86&spm=1001.2101.3001.7020)（超简单版）
-------------------------------------------------------------------------------------------------------------------

#### 文章目录

*   *   *   [一、个人简历效果](#_3)
        *   [二、部分代码解析](#_6)
        *   [三、完整代码](#_68)
        *   [四、实验小结](#_184)

#### 一、个人简历效果

![](https://i-blog.csdnimg.cn/blog_migrate/37def5deb19ef69330947a9f45e2064b.png)

#### 二、部分代码解析

> 开头有部分代码以及在之前的文章中解析过，如果想看具体参数的可以，移步到下面这条链接[在Web开发中简单的HTML标签的使用](https://blog.csdn.net/qq_44640357/article/details/129290112)

> 在body中设置整个html在浏览器中显示的背景颜色为白色

```
`<body style="background-color: white;">
</body>` 

*   1
*   2


```

> 设置页面大标题并且居中

```
 `<center>
    <h1 style="color: black;">
      个人简历
    </h1>
  </center>` 

*   1
*   2
*   3
*   4
*   5


```

> 第二段为姓名、性别、联系方式、邮箱等一些个人信息  
> 设置整段的背景颜色为rgb(72, 209, 204)  
> 设置字体为strong类型并且字体为较大号，颜色为白色，[左对齐](https://so.csdn.net/so/search?q=%E5%B7%A6%E5%AF%B9%E9%BD%90&spm=1001.2101.3001.7020)  
> 并且在浏览器的绝对位置的右边设置一张自己的照片，自定义长度和高度

```
 `<p style="background-color: rgb(72, 209, 204);">
    <strong style="font-size: larger;">
      <font style="color: white;" align="left">
        姓名： <br>
        性别： <br>
        联系方式： <br>
        邮箱：<a href="mailto:"></a>
      </font>
    </strong>

    <img style="position: absolute; top:40px; right:0px;" src="white.jpg" width="145px" height="145px">
  </p>` 

*   1
*   2
*   3
*   4
*   5
*   6
*   7
*   8
*   9
*   10
*   11
*   12
*   13


```

> 设置标题，[自我评价](https://so.csdn.net/so/search?q=%E8%87%AA%E6%88%91%E8%AF%84%E4%BB%B7&spm=1001.2101.3001.7020)

```
`<h2 align="left" style="color:mediumturquoise;">
      自我评价
  </h2>sa` 

*   1
*   2
*   3


```

> 以下内容设置字体颜色为黑色  
> br为换行

```
 `<p>
    <font style="color:black;">
      <b>
        高考专业陪考户<br>
        大学生专业陪读<br>
        计算机专业陪敲<br>
        CET-6专业陪考<br>
      </b>
    </font>
  </p>` 

*   1
*   2
*   3
*   4
*   5
*   6
*   7
*   8
*   9
*   10


```

> 接下来的教育背景、实习经历、个人博客以及荣誉证书都与自我评价的标题及内容相似

> 这个为超链接标签，在href中赋一个网页链接，点击即可进入，在后面跟着的为显示出的内容

```
 `<a href="https://blog.csdn.net/qq_44640357">CSDN 创作者“临风.”的主页连接</a>` 

*   1


```

#### 三、完整代码

```
`<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>202141084097</title>
</head>
<body style="background-color: white;">
  <center>
    <h1 style="color: black;">
      个人简历
    </h1>
  </center>

  <p style="background-color: rgb(72, 209, 204);">
    <strong style="font-size: larger;">
      <font style="color: white;" align="left">
        姓名： <br>
        性别： <br>
        联系方式： <br>
        邮箱：<a href="mailto:"></a>
      </font>
    </strong>

    <img style="position: absolute; top:40px; right:0px;" src="white.jpg" width="145px" height="145px">
  </p>

  <h2 align="left" style="color:mediumturquoise;">
      自我评价
  </h2>

  <p>
    <font style="color:black;">
      <b>
        高考专业陪考户<br>
        大学生专业陪读<br>
        计算机专业陪敲<br>
        CET-6专业陪考<br>
      </b>
    </font>
  </p>

  <h2 align="left" style="color: mediumturquoise;">
      教育背景
  </h2>
  
  <p style="background-color: white;">

    <font style="color: black">
      <strong>
        数据科学与大数据技术本科 /  / 2021-2024
      </strong>
      <br>

      <font>
        
      </font>
      <br>

      <font>
        
      </font>

    </font>
  </p>

  <h2 align="left" style="color:mediumturquoise;">
      实习经历
  </h2>

  <p>
    <font style="color: black">
        在加里敦大学对几位国内本科生及几位海外留学生进行课程辅导
    </font>
  </p>

  <h2 align="left" style="color:mediumturquoise;">
      专业技能
  </h2>
  
  <p>
    <font style="color:black">
      <b>
        简单的Python程序编程<br>
        简单的MySQL程序编程<br>
        简单的pandas数据分析<br>
        简单的Java程序编程<br>
        熟练使用MarkDown语言<br>
        熟练使用office三件套<br>
      </b>
    </font>
  </p>
 
  <h2 align="left" style="color:mediumturquoise">
    个人博客
  </h2>

  <a href="https://blog.csdn.net/qq_44640357">CSDN 创作者“临风.”的主页连接</a>

  <h2 align="left" style="color:mediumturquoise">
    荣誉证书
  </h2>

  <p>
    <font style="color:black">
      <b>
        CET-4 证书
      </b>   
   </font>
  </p>
  
</body>
</html>` 

*   1
*   2
*   3
*   4
*   5
*   6
*   7
*   8
*   9
*   10
*   11
*   12
*   13
*   14
*   15
*   16
*   17
*   18
*   19
*   20
*   21
*   22
*   23
*   24
*   25
*   26
*   27
*   28
*   29
*   30
*   31
*   32
*   33
*   34
*   35
*   36
*   37
*   38
*   39
*   40
*   41
*   42
*   43
*   44
*   45
*   46
*   47
*   48
*   49
*   50
*   51
*   52
*   53
*   54
*   55
*   56
*   57
*   58
*   59
*   60
*   61
*   62
*   63
*   64
*   65
*   66
*   67
*   68
*   69
*   70
*   71
*   72
*   73
*   74
*   75
*   76
*   77
*   78
*   79
*   80
*   81
*   82
*   83
*   84
*   85
*   86
*   87
*   88
*   89
*   90
*   91
*   92
*   93
*   94
*   95
*   96
*   97
*   98
*   99
*   100
*   101
*   102
*   103
*   104
*   105
*   106
*   107
*   108
*   109
*   110
*   111
*   112


```

#### 四、实验小结

> 只是使用简单的HTML标签的确很难制作出正常的一份个人简历，还得学习以及使用更多的CSS样式。