from PySquashfsImage import SquashFsImage

image = SquashFsImage.from_file(
    './openwrt-11.19.2023-x86-64-generic-squashfs-combined.img')  # 注意，这里的文件因为太大，所以，不能放入打包的文件中
for item in image:
    print(item.name)
image.close()
