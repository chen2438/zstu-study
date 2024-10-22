from PySquashfsImage import SquashFsImage

# 打开ROM文件
rom_file = "your_rom_file_path"
with open(rom_file, 'rb') as f:
    rom_image = SquashFsImage(f)

# 遍历ROM文件中的所有文件
for file_entry in rom_image:
    # 找到密码文件
    if file_entry.name == "passwords.txt":
        # 读取密码文件内容
        with rom_image.extract_data(file_entry) as f:
            passwords_content = f.read().decode('utf-8')
        
        # 修改密码hash值
        # 例如，将用户名为"username"的密码hash改为123456的hash值
        passwords_content = passwords_content.replace("username:old_hash", "username:new_hash")

        # 重新写入修改后的密码文件内容
        with open(rom_file, 'wb') as f:
            f.write(passwords_content.encode('utf-8'))

# 关闭ROM文件
rom_image.close()