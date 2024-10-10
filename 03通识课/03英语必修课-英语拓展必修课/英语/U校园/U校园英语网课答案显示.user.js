// ==UserScript==
// @name         U校园英语网课答案显示
// @namespace    https://github.com/the-eric-kwok/my_userscripts
// @version      1.2
// @description  小窗口显示U校园板块测试答案
// @author       gongchen, EricKwok
// @icon         https://ucontent.unipus.cn/favicon.ico
// @match        *://ucontent.unipus.cn/_pc_default/pc.html?*
// @match        *://u.unipus.cn/*
// @connect      unipus.cn
// @connect      fanyi.youdao.com
// @connect      translate.google.cn
// @connect      translate.google.com
// @connect      api.microsofttranslator.com
// @connect      api.fanyi.baidu.com
// @grant        GM_xmlhttpRequest
// @grant        GM_setClipboard
// @run-at       document-end
// @require      https://cdn.bootcdn.net/ajax/libs/jquery/3.6.0/jquery.min.js
// @License      GPLv3
// ==/UserScript==

/**
 * Generate a random string
 * @param {number} length Length of this random string
 * @returns {string} The random string
 */
function randomString(length) {
    let abc = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    let ret = "";
    for (let i = 0; i < length; i++) {
        ret += abc.charAt(Math.floor(Math.random() * abc.length));
    }
    return ret
}

/**
 * Generate a random num string
 * @param {number} length Length of this random num string
 * @returns {string} The random num string
 */
function randomNumString(length) {
    let nums = "0123456789";
    let ret = "";
    for (let i = 0; i < length; i++) {
        ret += nums.charAt(Math.floor(Math.random() * nums.length));
    }
    return ret
}

/**
 * 异步等待，只阻塞当前脚本调用处函数，不阻塞整个浏览器，默认等待 10 ms
 *
 * 调用方法：await sleep() 或 await sleep (1000)
 *
 * @param {number} ms 等待的毫秒数
 * @returns 一个匿名函数的 Promise
 */
function sleep(ms = 10) {
    // 异步等待，只阻塞当前脚本调用处函数，不阻塞整个浏览器
    // 调用方法：await sleep() 或 await sleep (1000)
    return new Promise(function (resolve, reject) {
        setTimeout(() => {
            resolve();
        }, ms);
    })
}

async function getRequest(url, headers = {}, timeout = 5000) {
    return new Promise(function (resolve, reject) {
        GM_xmlhttpRequest({
            method: 'GET',
            url: url,
            headers: headers,
            timeout: timeout,
            onload: (xhr) => {
                resolve(xhr);
            },
            onerror: (err) => {
                reject(err);
            },
            ontimeout: (err) => {
                reject(err);
            }
        });
    });
}

/**
 * Copy a string to clipboard
 * @param {string} str String to be copy
 */
function copyMe(str) {
    function _legacyCopy() {
        console.log("正在使用传统方法复制");
        let tmpInput = document.createElement('input');
        elem.insertAdjacentHTML("afterend", tmpInput)
        tmpInput.value = str;
        tmpInput.focus();
        tmpInput.select();
        if (document.execCommand('copy')) {
            document.execCommand('copy');
        }
        tmpInput.blur();
        console.log('复制成功');
        tmpInput.remove();

    }

    if (GM_setClipboard) {
        GM_setClipboard(str);
    } else if (navigator.clipboard && window.isSecureContext) {
        console.log("正在使用 navigator clipboard api 进行复制操作");
        navigator.clipboard.writeText(str)
            .catch(err => {
                console.log("navigator clipboard api 复制时出错，将使用传统方法进行复制")
                _legacyCopy();
            })
    } else {
        _legacyCopy();
    }
}

function main() {
    if (window.location.href.includes("u.unipus.cn")) {
        window.setInterval(function () {
            if (document.getElementsByClassName("layui-layer-shade").length > 0) {
                // 去除环境检测弹窗
                document.querySelector(".layui-layer-shade").remove();
            }
        }, 100);
    }
    if (window.location.href.includes("ucontent.unipus.cn")) {
        $.getScript("https://cdn.staticaly.com/gh/placemarker/jQuery-MD5/master/jquery.md5.js");
        $('head').append('<link href="https://lib.baomitu.com/layui/2.6.8/css/layui.css" rel="stylesheet" type="text/css" />');
        $.getScript("https://lib.baomitu.com/layui/2.6.8/layui.js", function (data, status, jqxhr) {
            layui.use('element', function () {
                let element = layui.element;
            });
            layer.closeAll();
            show();
            showanswer();
        });

        window.setInterval(function () {
            if (document.getElementsByClassName("dialog-header-pc--close-yD7oN").length > 0) {
                // 关闭单元学习时间弹窗
                document.querySelector(".dialog-header-pc--close-yD7oN").click();
            }
        }, 100);

        let autoClickPlay = window.setInterval(async function () {
            if (document.querySelector(".audio--aplayer-mute-2VMS7")) {
                window.clearInterval(autoClickPlay);
                await sleep(500);
                document.querySelector(".audio--aplayer-rate-ms-ZWyM6.audio--aplayer-rate-m-aH2Eu").querySelectorAll("span")[2].click();
                await sleep(300);
                document.querySelector(".audio--aplayer-mute-2VMS7").click();
                await sleep(300);
                document.querySelector(".audio--aplayer-play-3oL9n").click();
            }
        }, 100);

        function show() {
            layer.open({
                type: 1,
                area: ['310px', '400px'],
                offset: 'r',
                id: 'msgt',
                closeBtn: 1,
                title: " ",
                shade: 0,
                maxmin: true,
                anim: 2,
                content: `<div class="layui-collapse"><div class="layui-colla-item"></div></div>
                <div id="content">
                    <table class="layui-table">
                        <colgroup>
                            <col width="100">
                            <col>
                            <col>
                        </colgroup>
                        <thead><tr></tr></thead>
                        <tbody></tbody>
                    </table>
                </div>`
            });
        }

        async function showanswer() {
            let url = location.href
            let arr = url.split("/")
            let unit = arr[arr.length - 2]
            let course = /course-v1:.*?\//g.exec(url);
            course = course[0];
            let xhr = await getRequest(
                `https://ucontent.unipus.cn/course/api/content/${course}${unit}/default/`,
                {
                    'X-ANNOTATOR-AUTH-TOKEN': 'eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJvcGVuX2lkIjoidHV4NkNCQVc4aGRrcnFZdzc5SEpEWDF2aTR5Z2ptcDUiLCJuYW1lIjoiIiwiZW1haWwiOiIiLCJhZG1pbmlzdHJhdG9yIjoiZmFsc2UiLCJleHAiOjE5MDI5NzAxNTcwMDAsImlzcyI6IlI0aG03RmxQOFdvS0xaMUNmTkllIiwiYXVkIjoiZWR4LnVuaXB1cy5jbiJ9.CwuQmnSmIuts3hHAMf9lT954rKHXUNkps-PfRJp0KnU'
                },
                5000
            ).catch((err) => {
                console.error(err);
                let el = `<tr class="layui-bg"><td>答案加载失败，请刷新重试。</td></tr>`;
                $("#content>table>tbody").append($(el));
            });
            if (xhr.status != 200) {
                let el = `<tr class="layui-bg"><td>答案加载失败，请刷新重试。</td></tr>`;
                $("#content>table>tbody").append($(el));
                return;
            }
            let obj = JSON.parse(xhr.responseText) || {};
            if (!obj.content) {
                throw Error("U校园返回的内容中不包含'content'字段，请检查api是否改变！");
            }
            let rawContent = JSON.parse(obj.content) || {};

            let pages = {};
            for (let key in rawContent) {
                let pageNo = 1;
                if (key.includes("content_")) {
                    let re = /content_(\d+):/g.exec(key);
                    pageNo = parseInt(re[1]);
                }
                pages[pageNo] = {
                    key: key,
                    content: rawContent[key]
                };
            }

            let quesNo = /p_(\d+)/g.exec(url);
            quesNo = quesNo[1];
            let key = pages[quesNo].key;
            let content = pages[quesNo].content;
            if (key.includes(":questions")) {
                // 选择题
                let questionList = content.questions;
                for (let num = 0; num < questionList.length; num++) {
                    let question = questionList[num];
                    let answerId = randomString(5);
                    let btnId = randomString(5);
                    let el = `<tr class="layui-bg"><td><b>${num + 1}. </b><code id="${answerId}">${question.answers.join("、")}</code></td></tr>`;
                    $("#content>table>tbody").append($(el));
                    $(`#${btnId}`).on("click", function () {
                        let _answer = $(`#${answerId}`).text();
                        copyMe(_answer);
                    })
                }
                let interval = window.setInterval(async function () {
                    if (document.querySelector(".questions--questionDefault-2XLzl.undefined")) {
                        window.clearInterval(interval);
                        for (let num = 0; num < questionList.length; num++) {
                            let question = questionList[num];
                            let questionElem = document.querySelectorAll(".questions--questionDefault-2XLzl.undefined")[num]
                            let options = questionElem.querySelectorAll(".clearfix");
                            if (options.length == 0) {
                                options = questionElem.querySelectorAll(".MultipleChoice--checkbox-2_VGC");
                            }
                            for (let answer of question.answers) {
                                let sel = answer.toUpperCase().charCodeAt(0) - "A".charCodeAt(0);
                                options[sel].click();
                            }
                            await sleep(200);
                        }
                    }
                }, 1000);
            } else if (key.includes(":scoopquestions")) {
                // 填空题
                let questionList = content.questions;
                for (let num = 0; num < questionList.length; num++) {
                    let question = questionList[num];
                    let answerId = randomString(5);
                    let btnId = randomString(5);
                    let el = `<tr class="layui-bg"><td><b>${num + 1}. </b><code id="${answerId}">${question.answers[0]}</code><button style="float:right;" id="${btnId}">复制</button></td></tr>`;
                    $("#content>table>tbody").append($(el));
                    $(`#${btnId}`).on("click", function () {
                        let _answer = $(`#${answerId}`).text();
                        copyMe(_answer);
                    });
                }
                let interval = window.setInterval(function () {
                    if (document.querySelector(".htmlViewBlank--holder_style-2dnxi")) {
                        window.clearInterval(interval);
                        $("#content>table>tbody").prepend($(
                            `<tr class="layui-bg"><td><b>无需在此面板中复制，点击题目中的空，直接粘贴即可。</b></td></tr>`
                        ))
                        for (let num = 0; num < questionList.length; num++) {
                            let answer = questionList[num].answers[0];
                            $(document.querySelectorAll(".htmlViewBlank--holder_style-2dnxi")[num]).on("click", function () {
                                copyMe(answer);
                            });
                        }
                    }
                }, 500);
            } else if (key.includes(':shortanswer') && content.category === "shortanswer:shortAnswer") {
                // 翻译题
                let question = content.content[0].html.html;
                question = question.replace(/<.*?>|\(.*?\)|（.*?）/g, "");
                let direction = 'zh2en';
                if (/^[a-zA-Z\.,\s]+$/g.test(question.substring(0, 5))) direction = 'en2zh';
                try {
                    // 谷歌翻译
                    let googleTranslateXhr = await getRequest(
                        `http://translate.google.cn/translate_a/single?client=gtx&dt=t&dj=1&ie=UTF-8&sl=${direction.split("2")[0]}&tl=${direction.split("2")[1]}&q=${encodeURIComponent(question)}`
                    );
                    let googleTranslatedObj = JSON.parse(googleTranslateXhr.responseText);
                    let googleTranslateResult = "";
                    for (let sentence of googleTranslatedObj.sentences) {
                        googleTranslateResult += sentence.trans;
                    }
                    let answerId = randomString(5);
                    let btnId = randomString(5);
                    $("#content>table>tbody").append($(`<tr class="layui-bg"><td><b>谷歌翻译：</b><code id="${answerId}">${googleTranslateResult}</code><button style="float:right;" id="${btnId}">复制</button></td></tr>`));
                    $(`#${btnId}`).on("click", function () {
                        let _answer = $(`#${answerId}`).text();
                        copyMe(_answer);
                    });
                } catch (e) {
                    console.error(e);
                }
                try {
                    // 百度翻译
                    let appid = "20211128001012194";
                    let salt = randomString(10);
                    let sec = "LmBTDmGsvh2Ww2ws2F2S";
                    let sign = md5(appid + question + salt + sec);
                    let baiduTranslateXhr = await getRequest(
                        `http://api.fanyi.baidu.com/api/trans/vip/translate?q=${encodeURIComponent(question)}&from=${direction.split("2")[0]}&to=${direction.split("2")[1]}&appid=${appid}&salt=${salt}&sign=${sign}`
                    );
                    let baiduTranslateObj = JSON.parse(baiduTranslateXhr.responseText);
                    let baiduTranslateResult = "";
                    for (let item of baiduTranslateObj.trans_result) {
                        baiduTranslateResult += item.dst;
                    }
                    let answerId = randomString(5);
                    let btnId = randomString(5);
                    $("#content>table>tbody").append($(`<tr class="layui-bg"><td><b>百度翻译：</b><code id="${answerId}">${baiduTranslateResult}</code><button style="float:right;" id="${btnId}">复制</button></td></tr>`));
                    $(`#${btnId}`).on("click", function () {
                        let _answer = $(`#${answerId}`).text();
                        copyMe(_answer);
                    });
                } catch (e) {
                    console.error(e);
                }
                try {
                    // 必应翻译
                    let bingTranslateXhr = await getRequest(
                        `http://api.microsofttranslator.com/v2/Http.svc/Translate?appId=AFC76A66CF4F434ED080D245C30CF1E71C22959C&from=${direction.split("2")[0]}&to=${direction.split("2")[1]}&text=${encodeURIComponent(question)}`
                    );
                    let bingTranslateResult = bingTranslateXhr.responseText.replace(/<.*?>/g, "");
                    if (!bingTranslateResult.includes("TranslateApiExceptionMethod")) {
                        let answerId = randomString(5);
                        let btnId = randomString(5);
                        $("#content>table>tbody").append($(`<tr class="layui-bg"><td><b>必应翻译：</b><code id="${answerId}">${bingTranslateResult}</code><button style="float:right;" id="${btnId}">复制</button></td></tr>`));
                        $(`#${btnId}`).on("click", function () {
                            let _answer = $(`#${answerId}`).text();
                            copyMe(_answer);
                        });
                    }
                } catch (e) {
                    console.error(e);
                }
                try {
                    let answer = content.analysis.html;
                    answer = answer.replace(/<.*?>/g, "");
                    let el = `<tr class="layui-bg"><td><b>标准答案（仅供参考）：</b>${answer}</td></tr>`;
                    $("#content>table>tbody").append($(el));
                } catch (e) {
                    console.error(e);
                }
            } else if (key.includes(':shortanswer') && content.category === "shortanswerScoop") {
                // 简答题
                if (content.analysis.html.length > 0) {
                    try {
                        let answer = content.analysis.html;
                        answer = answer.replace(/<.*?>/g, "").replace(/\d\.\s?(&nbsp;)?/g, "");
                        let answerId = randomString(5);
                        let btnId = randomString(5);
                        let el = `<tr class="layui-bg"><td><b>标准答案（仅供参考）：</b><code id="${answerId}">${answer}</code><button style="float:right;" id="${btnId}">复制</button></td></tr>`;
                        $("#content>table>tbody").append($(el));
                        $(`#${btnId}`).on("click", function () {
                            let _answer = $(`#${answerId}`).text();
                            copyMe(_answer);
                        });
                    } catch (e) {
                        console.error(e);
                    }
                } else {
                    let questionList = content.questions;
                    for (let i = 0; i < questionList.length; i++) {
                        let question = questionList[i];
                        let answerId = randomString(5);
                        let btnId = randomString(5);
                        try {
                            let answer = question.analysis.html.replace(/<.*?>/g, "").replace(/\d\.\s?(&nbsp;)?/g, "");
                            let el = `<tr class="layui-bg"><td><b>${i + 1}.（仅供参考）</b><code id="${answerId}">${answer}</code><button style="float:right;" id="${btnId}">复制</button></td></tr>`;
                            $("#content>table>tbody").append($(el));
                            $(`#${btnId}`).on("click", function () {
                                let _answer = $(`#${answerId}`).text();
                                copyMe(_answer);
                            });
                        } catch (e) {
                            console.error(e);
                        }
                    }
                }
            } else if (key.includes(":shortanswer") || key.includes(":scoopshortanswer")) {
                // 简答题
                let questionList = content.questions;
                for (let i = 0; i < questionList.length; i++) {
                    let question = questionList[i];
                    let answerId = randomString(5);
                    let btnId = randomString(5);
                    try {
                        let answer = question.analysis.html.replace(/<.*?>/g, "").replace(/\d\.\s?(&nbsp;)?/g, "");
                        let el = `<tr class="layui-bg"><td><b>${i + 1}.（仅供参考）</b><code id="${answerId}">${answer}</code><button style="float:right;" id="${btnId}">复制</button></td></tr>`;
                        $("#content>table>tbody").append($(el));
                        $(`#${btnId}`).on("click", function () {
                            let _answer = $(`#${answerId}`).text();
                            copyMe(_answer);
                        });
                    } catch (e) {
                        console.error(e);
                    }
                }
            } else if (key.includes(":sequence")) {
                // 排序题
                for (let question of content.questions) {
                    let answer = question.answer;
                    let el = `<tr class="layui-bg"><td><code>${answer}</code></td></tr>`;
                    $("#content>table>tbody").append($(el));
                }
            }
        }

        window.onhashchange = () => {
            $("#content>table>tbody").empty();
            main();
        }
    }
}

(function () {
    'use strict';
    window.addEventListener('pjax:success', function () {
        // 将 main 函数绑定到 pjax 监听器上
        console.log("pjax success");
        main();
    });
    window.addEventListener('pushState', function (e) {
        console.log('change pushState');
        main();
    });
    window.addEventListener('replaceState', function (e) {
        console.log('change replaceState');
        main();
    });
    window.addEventListener('hashchange', function (event) {
        console.log(event, 'hashchange');
        //main();
    })
    main();
})();