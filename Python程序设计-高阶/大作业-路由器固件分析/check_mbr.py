import struct

# 打开硬盘设备
disk = open(r'./openwrt-11.19.2023-x86-64-generic-squashfs-combined.img', 'rb')

# 读取MBR
mbr = disk.read(512)

# 解析MBR中的分区表
def parse_mbr(mbr):
    # 分区表从第446字节开始，每个表项占16字节，共4个表项
    part_table = mbr[446:510]
    # 扩展分区的类型代码为0x05或0x0F
    ext_types = [0x05, 0x0F]
    # 遍历分区表，找到扩展分区
    for i in range(4):
        # 每个表项的结构为：1字节状态 + 3字节起始磁头/柱面/扇区 + 1字节类型 + 3字节结束磁头/柱面/扇区 + 4字节起始扇区LBA + 4字节扇区数
        part_entry = part_table[i*16:(i+1)*16]
        # 获取分区类型
        part_type = part_entry[4]
        # 如果是扩展分区，返回其起始扇区和扇区数
        if part_type in ext_types:
            part_start = struct.unpack('<I', part_entry[8:12])[0]
            part_size = struct.unpack('<I', part_entry[12:16])[0]
            return part_start, part_size
    # 如果没有找到扩展分区，返回None
    return None, None

# 读取扩展分区中的逻辑分区信息
def read_ext(disk, ext_start, ext_size):
    # 扩展分区的起始地址
    ext_base = ext_start
    # 逻辑分区列表
    log_parts = []
    # 循环读取每个逻辑分区
    while True:
        # 读取逻辑分区的引导扇区
        disk.seek(ext_start * 512)
        log_boot = disk.read(512)
        # 逻辑分区的分区表从第446字节开始，每个表项占16字节，只有前两个表项有效
        log_table = log_boot[446:462]
        # 第一个表项描述了当前逻辑分区的信息
        log_entry = log_table[:16]
        # 获取逻辑分区的起始扇区和扇区数，相对于当前引导扇区
        log_start = struct.unpack('<I', log_entry[8:12])[0]
        log_size = struct.unpack('<I', log_entry[12:16])[0]
        # 计算逻辑分区的绝对起始扇区，相对于硬盘
        log_start += ext_start
        # 将逻辑分区的信息添加到列表中
        log_parts.append((log_start, log_size))
        # 第二个表项描述了下一个逻辑分区的引导扇区的位置，相对于扩展分区
        ext_entry = log_table[16:32]
        # 获取下一个逻辑分区的引导扇区的起始扇区和扇区数
        ext_start = struct.unpack('<I', ext_entry[8:12])[0]
        ext_size = struct.unpack('<I', ext_entry[12:16])[0]
        # 如果下一个逻辑分区的引导扇区的起始扇区为0，表示没有更多的逻辑分区，退出循环
        if ext_start == 0:
            break
        # 否则，计算下一个逻辑分区的引导扇区的绝对起始扇区，相对于硬盘
        ext_start += ext_base
    # 返回逻辑分区列表
    return log_parts

# 判断一个分区是否包含squashfs文件
def is_squashfs(disk, part_start, part_size):
    # 读取分区的前4个字节，squashfs文件的魔术字为'h' 's' 'q' 's'
    disk.seek(part_start * 512)
    magic = disk.read(4)
    # 如果是squashfs文件，返回True，否则返回False
    return magic == b'hsqs'

# 读取一个分区中的squashfs文件
def read_squashfs(disk, part_start, part_size):
    # 读取分区的所有数据，返回一个字节串
    disk.seek(part_start * 512)
    data = disk.read(part_size * 512)
    return data

# 解压缩一个squashfs文件
def unzip_squashfs(sqsh):
    # 这里可以使用第三方库或者调用系统命令来解压缩squashfs文件，例如使用squashfs-tools库
    import squashfs
    # 创建一个SquashFS对象，传入squashfs文件的字节串
    fs = squashfs.SquashFS(sqsh)
    # 遍历squashfs文件中的所有文件和目录
    for entry in fs.list():
        # 打印文件或目录的名称和大小
        print(entry.name, entry.size)
        # 如果是文件，可以读取其内容，例如
        if entry.is_file():
            content = fs.read(entry)
            # 对文件内容进行处理，例如保存到本地或者显示出来
            # ...

# 获取扩展分区的起始地址和大小
ext_start, ext_size = parse_mbr(mbr)

# 如果存在扩展分区，进入扩展分区
if ext_start and ext_size:
    # 读取扩展分区中的逻辑分区信息
    log_parts = read_ext(disk, ext_start, ext_size)
    # 遍历每个逻辑分区
    for part_start, part_size in log_parts:
        # 判断是否包含squashfs文件
        if is_squashfs(disk, part_start, part_size):
            # 读取squashfs文件
            sqsh = read_squashfs(disk, part_start, part_size)
            # 解压缩squashfs文件
            unzip_squashfs(sqsh)

# 关闭硬盘设备
disk.close()
