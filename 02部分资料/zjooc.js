function skip() {
    let videos = document.getElementsByTagName('video');
    for (let i = 0; i < videos.length; i++) {
        if (isFinite(videos[i].duration)) {
            videos[i].currentTime = videos[i].duration;
        }
    }
}

setInterval(skip, 200);