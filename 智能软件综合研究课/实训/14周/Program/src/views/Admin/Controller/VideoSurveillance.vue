<template>
    <div>
        <!--面包屑-->
        <el-breadcrumb separator-class="el-icon-arrow-right"
            style="padding-left: 10px;padding-bottom: 10px;font-size: 12px">
            <el-breadcrumb-item :to="{ path: '/adminmain' }">首页</el-breadcrumb-item>
            <el-breadcrumb-item>监控中心</el-breadcrumb-item>
            <el-breadcrumb-item>视频监控</el-breadcrumb-item>
        </el-breadcrumb>

        <el-div class="allVideo">
            <el-div class="leftVideo" :data="userList1">
                <el-card shadow="hover" style="width: 90%; margin-bottom: 20px;">
                    <video ref="videoElement" autoplay style="display: none;"></video>
                    <img :src="imageSrc1" />
                </el-card>
                <el-card shadow="hover" style="width: 90%; margin-bottom: 8px;">
                    <div style="padding: 14px;">
                        <a>司机ID：{{ userId }}，司机姓名：{{ driverName }}，司机车牌：{{ plate }}</a><br>
                        <p>疲劳次数: {{ fatigueCount }}，当前疲劳等级：{{ status }}</p>
                        {{ ' '.repeat(2) }}<br>
                        <template slots-scope="scope">
                            <el-button size="mini" type="warning" @click="warningClick(userId)">警示</el-button>
                        </template>
                    </div>
                </el-card>
            </el-div>

            <el-div class="leftVideo" :data="userList2">
                <el-card shadow="hover" style="width: 90%; margin-bottom: 20px;">
                    <video ref="videoElement" autoplay style="display: none;"></video>
                    <img :src="imageSrc2" />
                </el-card>
                <el-card shadow="hover" style="width: 90%; margin-bottom: 8px;">
                    <div style="padding: 14px;">
                        <a>司机ID：{{ userId }}，司机姓名：{{ driverName }}，司机车牌：{{ plate }}</a><br>
                        <p>疲劳次数: {{ fatigueCount }}，当前疲劳等级：{{ status }}</p>
                        {{ ' '.repeat(2) }}<br>
                        <template slots-scope="scope">
                            <el-button size="mini" type="warning" @click="warningClick(userId)">警示</el-button>
                        </template>
                    </div>
                </el-card>
            </el-div>

        </el-div>
        <div class="footer" margin="20px" align="center">
            <el-button type="primary" @click="refresh()">刷新下一组</el-button>
        </div>
    </div>
</template>

<script>
import io from 'socket.io-client';
import { warningtiredUserById } from '@/api/driver'
import { videoGetUserList } from '@/api/data'


export default {
    name: 'AdminFatigueDetection',
    data() {
        return {
            videoElement: null,
            outputElement: null,
            imageSrc: '',
            userList1: [],
            userList2: [],
            // status: 'Normal',
            socket: io(process.env.VUE_APP_SOCKET_URL)
        };
    },
    created() {
        this.video_getUserList();
    },

    methods: {
        async video_getUserList() {
            const { data } = await videoGetUserList()
            console.log(data.data.UserAll)


            // this.total = data.data.total
            // this.userList = data.data.UserAll
            // console.log('current:' + data.data.current)
            // console.log('total:' + data.data.total)
        },
        async warningClick(userId) {
            console.log('userId', userId)
            //userId=1;
            const confirmResult = await this.$confirm('是否提醒该用户疲劳驾驶?', '警示', {
                confirmButtonText: '确定',
                cancelButtonText: '取消',
                type: 'warning'
            }).catch(err => {
                return err
            })
            if (confirmResult !== 'confirm') {
                return this.$message.info('已经取消提醒')
            }
            const { data } = await warningtiredUserById(userId)
            console.log(data)
            if (data.code === 3014) {
                return this.$message.error('本用户未驾驶车辆')
            }
            this.$message.success('警示成功')
        },
    },

    // startStream() {
    //     const videoElement = this.$refs.video;
    //     const streamUrl = '/getVideo'; // 与后端路由对应

    //     if (window.MediaSource && MediaSource.isTypeSupported('video/mp4')) {
    //     const mediaSource = new MediaSource();
    //     videoElement.src = URL.createObjectURL(mediaSource);

    //     mediaSource.addEventListener('sourceopen', () => {
    //         const sourceBuffer = mediaSource.addSourceBuffer('video/mp4; codecs="avc1.42E01E, mp4a.40.2"');

    //         const xhr = new XMLHttpRequest();
    //         xhr.open('GET', streamUrl);
    //         xhr.responseType = 'arraybuffer';
    //         xhr.onerror = () => console.log('Error loading video stream');
    //         xhr.onprogress = (event) => {
    //             if (event.lengthComputable) {
    //                 const percentComplete = (event.loaded / event.total * 100 | 0);
    //                 console.log(`Loading video stream ${percentComplete}%`);
    //             }
    //         };
    //         xhr.onload = () => {
    //             const uint8Array = new Uint8Array(xhr.response);
    //             let i = 0;

    //             (function readChunk() {
    //                 const length = ((uint8Array[i] << 24) | (uint8Array[i + 1] << 16) | (uint8Array[i + 2] << 8) | uint8Array[i + 3]) >>> 0;
    //                 i += 4;

    //                 if (length === 0) {
    //                     mediaSource.endOfStream();
    //                 } else {
    //                     const chunk = uint8Array.subarray(i, i + length);
    //                     i += length;

    //                     sourceBuffer.appendBuffer(chunk);
    //                     readChunk();
    //                 }
    //             })();
    //         };
    //         xhr.send();
    //     });
    //     } else {
    //         console.log('Unsupported MIME type or codec: video/mp4; codecs="avc1.42E01E, mp4a.40.2"');
    //     }
    // },

    mounted() {
        this.videoElement = this.$refs.videoElement;
        this.outputElement = this.$refs.outputElement;

        if (navigator.mediaDevices && navigator.mediaDevices.getUserMedia) {
            navigator.mediaDevices.getUserMedia({ video: true }).then((stream) => {
                this.videoElement.srcObject = stream;
                this.videoElement.play();

                const canvas = document.createElement('canvas');
                const context = canvas.getContext('2d');

                setInterval(() => {
                    context.drawImage(this.videoElement, 0, 0, canvas.width, canvas.height);
                    const dataURL = canvas.toDataURL('image/jpeg');
                    this.socket.emit('frame', dataURL.split(',')[1]); // Send the frame to the server
                }, 200); // Send frames every 100ms
            });
        }

        this.socket.on('response', (data) => {
            this.imageSrc = 'data:image/jpeg;base64,' + data.data; // Update the image source
            this.driverName = data.driverName;
            this.plate = data.plate;
            this.fatigueCount = data.count;
            this.status = data.status;
        });
    },
    async refresh() {
        this.mounted();
    },

    beforeDestroy() {
        this.socket.disconnect();
    },
};
</script>

<style>
.allVideo {
    width: 94%;
    height: 90%;
    display: grid;
    margin-top: 20px;
    grid-template-rows: 1fr, 1fr;
    grid-template-columns: 47% 47%;
    grid-gap: 10px;
    justify-items: center;
    align-items: center;
    border: 1px solid #ccc;
    border-radius: 10px;
}

.leftVideo {
    width: 94%;
    height: auto;
    display: flex;
    flex-direction: column;
    justify-items: center;
    align-items: center;
    border: 1px solid #ccc;
    margin-right: 16px;
}

.el-button {
    align-items: "center";
}

.el-card {
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
    /* 添加阴影效果 */
    margin: 10px;
    justify-items: center;
    align-items: center;
}

.footer {
    margin: 10px;
    justify-items: center;
    align-items: center;
    padding: 5px;
}

/* .rowVideo{
    height:100%;
    display: grid;
    grid-template-rows: 1fr;
    grid-template-columns: 50% 50%;
    grid-gap: 10px;
    justify-items: center;
    align-items: center;
}
.eachVideo{
    width:80%;
    height:auto;
    justify-items: center;
    align-items: center;
    border: 1px solid #ccc;
    border-radius: 10px;
    padding: 10px;
} */

img {
    width: 100%;
    max-width: 720px;
    height: auto;

}
</style>
