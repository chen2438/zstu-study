module.exports = {
    chainWebpack: config => {
        // 移除 eslint-loader
        config.module.rules.delete('eslint');
    }
}
