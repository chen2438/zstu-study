// ==UserScript==
// @name         U校园英语网课答案显示[修复可用版本]
// @namespace    gongchen
// @version      1.1
// @description  小窗口显示U校园板块测试答案，修复可用版本
// @author       gongchen
// @compatible   Chrome
// @match        *://ucontent.unipus.cn/_pc_default/pc.html?*
// @connect      *://ucontent.unipus.cn/*
// @grant        GM_xmlhttpRequest
// @run-at       document-end
// @require      https://lib.baomitu.com/jquery/3.6.0/jquery.min.js
// @antifeature ads      脚本使用免费，广告内容不影响使用
// ==/UserScript==

$('head').append('<link href="https://lib.baomitu.com/layui/2.6.8/css/layui.css" rel="stylesheet" type="text/css" />');
$.getScript("https://lib.baomitu.com/layui/2.6.8/layui.js", function(data, status, jqxhr) {
    layui.use('element', function(){
        var element = layui.element;
    });
    layer.closeAll();
    show();
    showanswer();
});

var show = ()=>{
    layer.open({
        type: 1,
        area: ['400px', '400px'],
        offset: 'l',
        id: 'msgt',
        closeBtn: 1,
        title: "U校园网课助手(答案显示)",
        shade: 0,
        maxmin: true,
        anim: 2,
		content:'<div class="layui-collapse"><div class="layui-colla-item"><h2 class="layui-colla-title">公告</h2><div class="layui-colla-content layui-show">单元测试下载app搜索<img src="https://cdn.fm210.cn/img/huoxin.png" width="100px" /></div>'+
        '</div></div>'+
        '<div id="content"><ul></ul><table class="layui-table"> <colgroup> <col width="100"> <col> <col> </colgroup> <thead> <tr>  </tr> </thead> <tbody>  </tbody> </table></div></div></div>'
    });
}

var showanswer = ()=>{
    let url = location.href
    let arr = url.split("/")
    let unit = arr[arr.length-2]
    let answer = []
    GM_xmlhttpRequest({
        method: 'GET',
        url: 'https://ucontent.unipus.cn/course/api/content/course-v1:Unipus+nhce_3_rw_3+2018_09/'+unit+'/default/',
        headers: {
            'X-ANNOTATOR-AUTH-TOKEN': 'eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJvcGVuX2lkIjoidHV4NkNCQVc4aGRrcnFZdzc5SEpEWDF2aTR5Z2ptcDUiLCJuYW1lIjoiIiwiZW1haWwiOiIiLCJhZG1pbmlzdHJhdG9yIjoiZmFsc2UiLCJleHAiOjE5MDI5NzAxNTcwMDAsImlzcyI6IlI0aG03RmxQOFdvS0xaMUNmTkllIiwiYXVkIjoiZWR4LnVuaXB1cy5jbiJ9.CwuQmnSmIuts3hHAMf9lT954rKHXUNkps-PfRJp0KnU'
        },
        timeout: 5000,
        onload: function(xhr) {
            if (xhr.status == 200) {
                let obj = JSON.parse(xhr.responseText) || {};
                let questionList = JSON.parse(obj.content)['questions:scoopquestions']['questions']
                for (let question of questionList){
                    let el = '<tr class="layui-bg">' + '</td></tr>'
                    el = el + '<td>' + question.answers[0] + '</td></td></tr>'
                    $("#content>table>tbody").append($(el));
                }
            }
        }
    });
}

window.onhashchange=()=>{
    $("#content>table>tbody").empty();
    showanswer();
}