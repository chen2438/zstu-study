本篇主要讨论以下两种翻书动画的实现：

第一种是整页翻转的效果：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/1657671c57cee496~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

这种整页翻转的效果主要是做rotateY的动画，并结合一些CSS的3d属性实现。

第二种折线翻转的效果，如下图所示：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/16576719bf93f7ff~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

主要是通过计算页面翻折过来的位置。

这两种原理上都不是很复杂，需要各个细节配合好，形成一个连贯的翻书动画。

我们先重点说一下第一种翻页效果的实现。

1\. 基本布局
--------

这种的实现相对比较简单，我们先把DOM结构准备好，如下代码所示：

```htmlbars
<ul class="pages">
    
    <li class="paper" data-left>
        
        <div class="page page-1-back">
            <img src="1.jpg" alt>
        </div>
        <div class="page page-1">
            <img src="2.jpg" alt>
        </div>
    </li>
    <li class="paper" data-right>
        <div class="page page-2">
            <img src="3.jpg" alt>
        </div>
        <div class="page page-2-back">
            <img src="4.jpg" alt>
        </div>
    </li>
    
</ul>

```

一个`li.paper`就表示一张纸，包含了正反两页，data-left属性表示它是在左边的，而data-right表示是在右侧，通过absolute定位把它们放到相应的位置。所以如果是下一页，应该让data-right做左翻的动画，相反上一页则让data-left做右翻的动画。

.page-1是当前显示在左边的那一页，.page-2表示当前右边的那一页，而.page-1-back和.page-2-back则分别表示在.paeg-1和.page-2后面的那一页。它们置于背后是水平翻转的，这一点应该不难想象，所以需要借助transform: scale水平翻转一下：

```css
.page-1-back,
.page-2-back {
    transform: scale(-1, 1);
}

```

并且.page-1的z-index要比在后面的.page-1-back要高：

```css
.page-1,
.page-2 {
    z-index: 1;
}

```

通过这样排版之后，就得到了以下的布局：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/16576719753e0c1f~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

接下来让右边的那一页翻过来。

2\. 翻书动画
--------

就是做.paper的rotateY动画，很简单，如下代码所示：

```css
@keyframes flip-to-left {
    from {
        transform: rotateY(0);
    }
    to {
        transform: rotateY(-180deg);
    }
}
.paper[data-right] {
    transform-origin: left center;
    animation: flip-to-left 2s ease-in-out;
}

```

需要设置变换中心为左边中间的位置，效果如下：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/165767199c7f558e~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

我们发现有几个问题，第1个问题是翻过去的后面的那个paper没有显示出来，因为一开始把没显示出来的paper都隐藏了，所以需要把后面那个paper显示出来：

```css
.paper {
    display: none;
    position: absolute;
    
    right: 0;
}
.paper[data-left],
.paper[data-right] {
    display: block;
    z-index: 1;
}
.paper[data-left] {
    right: auto;
    left: 0;
}

.paper[data-right] + .paper {
    display: block;
}

```

这样翻过来之后就能显示后面的那个paper了，如下图所示：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/165767198a2a2085~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

第二个问题是：为什么.page-2-back没显示出来，仍然显示的是.page-2，猜测是因为.page-2的z-index比较高，把.page-2-back盖住了，所以即使整体rotate属性变了，它也是被盖住的状态。

所以第一个方法可以在翻转一半的时候就把z-index的高低关系互换一下，让page-2-back比page-2更高，但是这个方法不太好控制，因为动画的变化不是linear的，即使是linear的这个方法也不灵活，容易出现闪动的情况。

第二个方法是调整它们俩的translateZ关系，让page-2的translateZ值比page-2-back高1px就可以了，而不是直接设置z-index关系。为了让translateZ能生效，需要设置它们容器的**transform-style为preserve-3d**，如下代码所示：

```css
.paper {
    transform-style: preserve-3d;
}
.page-1,
.page-2 {
    transform: translateZ(1px);
}

```

这个可以让子元素从扁平空间(flat)变成一个3维空间，translateZ就能发挥作用了，效果如下所示：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/1657671a6d56f6f3~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

这样基本的效果就出来了，但是总感觉哪里不太对，就是这个翻转有点平，没有景深的效果。说到景深会想起另外一个CSS属性**transform-perspective**，我们不妨给它加一个perspective看看效果如何：

```css
@keyframes flip-to-left {
    from {
        transform: perspective(1000px) rotateY(0);
    }
    to {
        transform: perspective(1000px) rotateY(-180deg);
    }
}

```

效果如下图所示：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/1657671a168c51b1~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

这样看起来感觉就立体多了。perspective可以理解为摄像机的位置，如果值越大摄像机就推得越远。不同值对比如下：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/1657671a2d9c4cdc~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

这样翻书的动画基本就完成了，从左向右翻也是同样道理。接下来的问题是怎么形成连续翻书的动画。

3\. 连续翻书
--------

可以给动画加一个forwards属性，让动画保持在最后结束的那个状态：

```css
.paper[data-right] {
    transform-origin: left center;
    animation: flip-to-left 2s ease-in-out forwards;
}

```

停住之后，上面那些类的关系需要重新更新一下，例如翻过来之后原本的.page-2-back会变成.page-1。

比较科学的方法是使用[element.animate](https://link.juejin.cn/?target=https%3A%2F%2Fdeveloper.mozilla.org%2Fen-US%2Fdocs%2FWeb%2FAPI%2FElement%2Fanimate "https://developer.mozilla.org/en-US/docs/Web/API/Element/animate")做动画，因为它有一个onfinish的回调告诉我们动画结束了，动画由于这个API的兼容性不是很好，要么找个polyfill，要么还是用上面CSS的方法然后借助setTimeout。[polyfill的库](https://link.juejin.cn/?target=https%3A%2F%2Fgithub.com%2Fweb-animations%2Fweb-animations-js "https://github.com/web-animations/web-animations-js")比较大，这里还是用setTimeout模拟动画结束，使用setTimeout的风险是可能会不太准。

代码逻辑比较简单，就是找到对应的dom结点设置对应的类或者属性，就是代码比较繁琐一点，如下所示：

```javascript
let currentPage = 1;
let $ = document.querySelector.bind(document);
$('#next-page').addEventListener('click', goToNextPage);
const flipAnimateTime = 1000;
function goToNextPage () {
    
    $('.paper[data-right]').setAttribute('data-begin-animate', true);
    setTimeout(() => {
        
        let $rightPaper = $('.paper[data-right]'),
            $leftPaper = $('.paper[data-left]');
        $rightPaper.removeAttribute('data-right');
        $rightPaper.setAttribute('data-left', true);
        
        $leftPaper.removeAttribute('data-left');
        $leftPaper.querySelector('.page-1').classList.remove('page-1');
        $leftPaper.querySelector('.page-1-back').classList.remove('page-1-back');
        
        $leftPaper = $rightPaper;
        $rightPaper = $leftPaper.nextElementSibling;
        $leftPaper.querySelector('.page').classList.add('page-1-back');
        $leftPaper.querySelector('.page + .page').classList.add('page-1');
        
        if ($rightPaper) {
            $rightPaper.setAttribute('data-right', true);
            $rightPaper.querySelector('.page').classList.add('page-2');
            $rightPaper.querySelector('.page + .page').classList.add('page-2-back');
        }   
        currentPage++;
    }, flipAnimateTime);
}

```

效果如下图所示：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/1657671c57cee496~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

向左翻页也是类似。

这里有个问题，如果用户点下一页点得很快那应该怎么办？如果他点得很快的话前面的翻页还没有结束，会导致setTimeout里的代码还没有执行，那么整个模型就乱了。有两个解决方法，第一种是在翻页过程中禁掉下一页的操作，但是似乎不太友好，第二种是把翻页的过程当作一个task任务，一旦点了下一页或者上一页，就push一个task进来，每个task按顺序同步执行，如果task数组长度大于1那么就缩短动画的时间，让它翻得快一点。相似的处理我已经在《[实现内部组件轮播切换效果](https://link.juejin.cn/?target=https%3A%2F%2Fwww.rrfed.com%2F2018%2F04%2F06%2Fvue-component-slider%2F "https://www.rrfed.com/2018/04/06/vue-component-slider/")》讨论过，这里不再重复。

4\. 适配的问题
---------

你可能会担心动画结束后修改了dom结构，导致**CSS属性变了会闪一下**，例如原本的page-2-back是水平翻转的，但是在JS里面设置了之后它就变成非水平翻转了，虽然展示的效果是一样的，但是会不会闪一下呢？只要改之前和改之后浏览器进行layout计算的结果一模一样它就不会闪的，就像上面的例子，但是一旦位移差了1px，就会有闪动。

在实际的例子，你可能需要中间有1px的书缝的阴影，所以左右页的宽度就不是刚好50%，而是要减去1px，所以如果你的transform-origin还是left center的话翻过去之后就会往右移了1px，当动画结束重置状态，1px的偏移就会被修正，这个时候就会小闪一下。而当你把transform-origin改成-1px center之后，又会导致翻过去之后往左移了1px。所以最好别把中间的阴影单独弄出来，可以改成在每一个page里面用before/after画，每个page还是要占50%，这样就没问题。

另外一个要考虑的问题是，使用了**transform: scale + translateZ可能会导致模糊**，一个直接的例子可以见这个[codepen](https://link.juejin.cn/?target=https%3A%2F%2Fcodepen.io%2FVestride%2Fpen%2FCvBrw "https://codepen.io/Vestride/pen/CvBrw")，就是因为用了translateZ或者will-change: transform等触发了GPU渲染导致模糊了，这个过程可能是浏览器把当前图层截一张图给GPU计算，GPU把这张静态图缩放就会模糊。而当我们把translateZ等有promotion提升作用的属性去掉之后，在缩放的过程会模糊，但是最终状态是清晰的。如下图所示：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/1657671a45db0f35~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

在上面的例子里面我们用了transform: scale(-1, 1)做水平翻转，然后还用了translateZ(1px)做上下图层关系。理论上我们使用scale但是并没有放大或者缩小不应该模糊才对，但是在windows上的Chrome可以明显看到模糊了（在mac上的Chrome是不会模糊的），把translateZ去掉就不会模糊了。所以我想到的解法方法是一开始图层不要translateZ（使用z-index），只有开始做动画了才加上translateZ（并去掉z-index），动画结束后再把translateZ去掉。

5\. 变成一个插件
----------

当把上面的问题都解决了之后，可以把它变成一个插件，用的人只要引入，然后初始化一下就搞定了，不用关心这些类怎么变之类的问题。

并且，由于一个paper容器有两个page是正反面的关系，一旦中间突然插入了一页就会导致page的正反面关系发生变化，所以这个结构不是很灵活，最好是动态生成，也就是说使用插件的人，把所有的page并列排就好了，然后在插件里面再重新组织下DOM结构，把在正反面的两个page放到一个paper里面。

接着讨论下第二种翻书效果的实现。

6\. 折线翻书效果的实现
-------------

这个有一个现成的插件[turn.js](https://link.juejin.cn/?target=http%3A%2F%2Fwww.turnjs.com%2F%23 "http://www.turnjs.com/#")，使用起来非常简单，我们简单讨论一下它的内部实现。

这个东西乍看一下，似乎有曲面的效果：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/1657671a3eebaec0~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

但实际上是没有的，这个曲线效果是它添加的阴影和渐变产生的视觉效果，当我们把background-image的渐变去掉之后对比一下就能看出来了：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/1657671a62cd1b6a~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

没有渐变的伪装之后一下子就平了。它就变成了一个折纸的模型——给定一张纸和一个折过去的点，计算一下折过去的旋转角度和位移。它的源代码是在fold函数里面计算的：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/1657671a6289e0d0~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

它里面有各种余弦正弦的计算和角度的判断，具体实现还是比较复杂的，没有深入去研究，代码可见[turn.js](https://link.juejin.cn/?target=https%3A%2F%2Fgithub.com%2Fblasten%2Fturn.js%2Fblob%2Fmaster%2Fturn.js%23L1426 "https://github.com/blasten/turn.js/blob/master/turn.js#L1426").

还有一个问题是它是怎么实现三角形裁剪展示的效果？它是在上层又盖了一个div：

![](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/8/26/1657671a6687aed1~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp)

7\. 小结
------

本文讨论了两种翻书效果的实现，重点讨论了一下比较简单的整体翻页的方式，这种方式主要是做rotateY动画，同时打开perspective让其具有景深效果，并且用preserve-3d结合translateZ制造上下层级关系，这种方式可能会存在闪动和模糊的问题，为了让翻过去不会闪动关键的地方是保证每一个page占宽50%，模糊的问题是因为用了scale加上GPU提升导致的，所以只能通过不写3d属性保证清晰。

第二种的效果模型相对比较复杂，简单分析了一下它的原理和实现方式。主要是计算折纸过来的角度和位移，上层再盖一个div隐藏不露出来的部分。然后再加上阴影和渐变制造一种曲面的效果。这种翻书的效果还是挺好玩的。

《[一线大厂是如何开发微信小程序的](https://juejin.cn/post/6844903656131674119 "https://juejin.cn/post/6844903656131674119")》