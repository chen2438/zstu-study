import binwalk
import os
import datetime

def format_result(result):
    # 格式化结果，确保每一行都以逗号和换行符结尾
    formatted_result = ""
    for line in result.split(", "):
        formatted_result += line.strip() + ",\n"
    return formatted_result

def get_file_info(file_path):
    # 获取文件信息，包括大小和最后修改时间
    file_size = os.path.getsize(file_path)
    last_modified_time = datetime.datetime.fromtimestamp(os.path.getmtime(file_path)).strftime('%Y-%m-%d %H:%M:%S')
    return file_size, last_modified_time

def process_firmware_file(input_file_path, output_file_path):
    try:
        # 检查输入文件路径是否存在
        if not os.path.exists(input_file_path):
            raise FileNotFoundError(f"文件 {input_file_path} 不存在.")

        # 获取文件信息
        file_size, last_modified_time = get_file_info(input_file_path)

        # 等同于执行 'binwalk --signature firmware1.bin firmware2.bin'。
        # 注意使用 'quiet=True' 来抑制正常的 binwalk 输出。
        with open(output_file_path, 'w') as output_file:
            # 输出文件信息
            output_file.write(f"分析结果文件: {os.path.basename(input_file_path)}\n")
            output_file.write(f"文件大小: {file_size} 字节\n")
            output_file.write(f"最后修改时间: {last_modified_time}\n\n")

            # 统计擦除次数的变量
            erase_count = 0

            for module in binwalk.scan(input_file_path, signature=True, quiet=True):

                # binwalk.scan 返回每个已执行模块的模块对象；
                output_file.write("%s 结果:\n" % module.name)

                # 初始化上一个结果的文件路径为 None
                prev_file_path = None

                # 每个模块都有一个结果对象列表，描述执行模块返回的结果。
                for result in module.results:
                    # 使用 os.path.basename 获取文件名，避免显示完整路径
                    file_name = os.path.basename(result.file.name)

                    # 检查是否与上一个结果的文件路径相同，避免重复输出文件路径。
                    if file_name != prev_file_path:
                        # 输出文件名
                        output_file.write("文件名: " + "%s\n" % file_name + "\n")
                        # 更新上一个结果的文件路径
                        prev_file_path = file_name

                    # 输出该文件下的结果，每个信息都换行
                    formatted_result = format_result(result.description)
                    output_file.write("0x%.8X    %s\n" % (result.offset, formatted_result))

                    # 检查描述信息中是否包含擦除计数相关的内容
                    if "UBI erase count" in result.description:
                        erase_count += 1

            # 输出擦除次数统计结果
            output_file.write(f"\n总擦除次数: {erase_count}\n")

        print(f"结果已写入 {output_file_path}")

    except FileNotFoundError as file_not_found_error:
        # 如果文件未找到，捕获 FileNotFoundError 异常并输出相应的错误信息
        print(f"文件未找到错误: {file_not_found_error}")

    except Exception as e:
        # 捕获其他异常，并输出相应的错误信息
        print(f"发生错误: {str(e)}")

# 自定义信息
firmware_input_path = 'C:/Users/27719/Downloads/python_course_design-master/python_course_design-master/openwrt-11.19.2023-ramips-mt7621-linksys_e5600-squashfs-factory.bin'
output_result_path = 'output.txt'
process_firmware_file(firmware_input_path, output_result_path)
