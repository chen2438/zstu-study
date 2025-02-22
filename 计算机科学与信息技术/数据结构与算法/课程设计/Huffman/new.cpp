#include <bitset>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

typedef unsigned char Byte;

// 存储哈夫曼编码的映射
std::unordered_map<Byte, std::string> codes;  // codes[字节]=哈夫曼编码

// 哈夫曼树 节点
struct Node {
    Byte data;           // 存储1字节
    unsigned frequency;  // 频率
    bool isLeaf;         // 是叶子节点
    Node *left, *right;  // 左右节点

    Node(Byte data, unsigned frequency, bool isLeaf) {
        left = right = nullptr;
        this->data = data;
        this->frequency = frequency;
        this->isLeaf = isLeaf;
    }
};

// 小根堆 频率升序排序
struct Compare {
    bool operator()(Node* l, Node* r) { return l->frequency > r->frequency; }
};

// 生成哈夫曼编码
void printCodes(Node* root, std::string str) {
    if (!root) return;

    if (root->isLeaf) codes[root->data] = str;

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// 构建哈夫曼树
Node* buildHuffmanTree(Byte data[], int freq[], int size) {
    struct Node *left, *right, *top;
    std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap;
    for (int i = 0; i < size; ++i)  // 创建节点 加入堆
        minHeap.push(new Node(data[i], freq[i], true));

    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();

        // 频率相加 data=0
        top = new Node('\0', left->frequency + right->frequency, false);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    return minHeap.top();
}

// 读取文件到字节数组
std::vector<Byte> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    // 检查文件是否成功打开
    if (!file) {
        std::cerr << "ERROR: 无法打开文件 '" << filename
                  << "' 以进行读取。可能是文件不存在或权限不足。" << std::endl;
        return std::vector<Byte>();  // 返回空数组
    }
    std::vector<Byte> bytes((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
    if (bytes.empty()) {
        std::cerr << "ERROR: 文件 '" << filename << "' 为空。" << std::endl;
        return std::vector<Byte>();  // 返回空数组
    }
    return bytes;
}

// 将字节数组写入文件
void writeFile(const std::string& filename, const std::vector<Byte>& bytes) {
    std::ofstream file(filename, std::ios::binary);
    // unsigned char* 强制转换为 const char*
    file.write(reinterpret_cast<const char*>(&bytes[0]), bytes.size());
}

// 累加编码数据 连接哈夫曼编码
std::vector<Byte> encodeHuffman(const std::vector<Byte>& bytes) {
    std::string encodedString;
    for (auto byte : bytes) {
        encodedString += codes[byte];
    }

    int lastByteLength = encodedString.size() % 8;
    while (encodedString.size() % 8 != 0) {
        encodedString += "0";  // 补齐长度为8的倍数
    }

    // 将字符串转换为字节
    std::vector<Byte> encodedData;
    for (size_t i = 0; i < encodedString.size(); i += 8) {
        std::string byteString = encodedString.substr(i, 8);

        // string->bitset
        std::bitset<8> bitset(byteString);
        // bitset->ulong->uchar
        encodedData.push_back(static_cast<Byte>(bitset.to_ulong()));
    }

    // 若最后一个字节完整 设置为8
    if (lastByteLength == 0) lastByteLength = 8;
    // 添加表示最后字节长度的字节 记录信息以便解码
    encodedData.push_back(lastByteLength);

    return encodedData;
}

// 解码数据
std::vector<Byte> decodeHuffman(const std::vector<Byte>& encodedData,
                                Node* root) {
    std::vector<Byte> decodedData;
    Node* current = root;

    // 获取最后字节的实际长度
    int lastByteLength = encodedData.back();

    // 遍历除最后一个字节之外的所有字节
    for (size_t i = 0; i < encodedData.size() - 1; i++) {
        std::bitset<8> bits(encodedData[i]);
        // 如果最后的字节，只处理 lastByteLength 位，否则处理8位
        int limit = (i == encodedData.size() - 2) ? lastByteLength : 8;
        for (int j = 7; j >= 8 - limit; --j) {  // 从最高位(左边)开始
            current = bits[j] ? current->right : current->left;  // 1往右,0往左
            if (current->left == nullptr && current->right == nullptr) {
                // 到达叶子结点
                decodedData.push_back(current->data);
                current = root;  // 重置根节点
            }
        }
    }
    return decodedData;
}

// 序列化哈夫曼树
void serializeHuffmanTree(Node* root, std::ostream& out) {
    if (!root) {  // 叶子节点的子节点 nullptr
        out.put(0);
        return;
    }

    // '1'表示节点，后跟数据
    out.put(1);
    out.put(root->data);

    serializeHuffmanTree(root->left, out);
    serializeHuffmanTree(root->right, out);
}

// 反序列化哈夫曼树
Node* deserializeHuffmanTree(std::istream& in) {
    if (!in.good()) return nullptr;  // 检查输入流 in 有效

    char flag;
    in.get(flag);
    if (flag == 0) return nullptr;  // 空节点

    char data;
    in.get(data);

    Node* node = new Node(data, 0, false);  // 不需要频率
    node->left = deserializeHuffmanTree(in);
    node->right = deserializeHuffmanTree(in);

    if (!node->left && !node->right) node->isLeaf = true;

    return node;
}

// 打印哈夫曼树到文件
void printHuffmanTree(Node* root, std::ostream& out, std::string path) {
    if (!root) return;

    if (root->isLeaf) {
        out << path << " -> " << root->data << " (" << root->frequency << ")\n";
    } else {
        printHuffmanTree(root->left, out, path + "0");
        printHuffmanTree(root->right, out, path + "1");
    }
}

int main() {
    std::string filePath;
    std::cout << "请输入要编码的文件的相对路径: ";
    std::cin >> filePath;

    // 读取原始文件
    auto originalData = readFile(filePath);

    if (originalData.empty()) return 0;

    // 提取文件后缀
    std::string extension;
    std::string::size_type idx = filePath.rfind('.');
    if (idx != std::string::npos && idx != filePath.find_last_of("/\\")) {
        extension = filePath.substr(idx);  // 包括.的扩展名
    }

    // 统计频率 Byte=unsigned char=1B
    std::unordered_map<Byte, int> freqMap;
    for (auto byte : originalData) {
        freqMap[byte]++;
    }

    // 构建哈夫曼树
    int size = freqMap.size();
    Byte* data = new Byte[size];
    int* freq = new int[size];
    int i = 0;
    for (auto& pair : freqMap) {
        data[i] = pair.first;
        freq[i] = pair.second;
        i++;
    }
    Node* root = buildHuffmanTree(data, freq, size);
    printCodes(root, "");

    // 测量编码时间
    auto startEncode = std::chrono::high_resolution_clock::now();
    // 进行哈夫曼编码
    auto encodedData = encodeHuffman(originalData);
    auto endEncode = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> encodeDuration =
        endEncode - startEncode;

    writeFile("encoded.bin", encodedData);

    // 打印哈夫曼树的可读形式到文件
    std::ofstream treeOutFile("tree.txt");
    printHuffmanTree(root, treeOutFile, "");
    treeOutFile.close();

    // 序列化哈夫曼树 写入文件
    std::ofstream treeFile("tree.bin", std::ios::binary);
    serializeHuffmanTree(root, treeFile);
    treeFile.close();

    // 读取编码文件
    auto encodedFileData = readFile("encoded.bin");

    // 读取并反序列化哈夫曼树
    std::ifstream treeFileIn("tree.bin", std::ios::binary);
    Node* deserializedRoot = deserializeHuffmanTree(treeFileIn);
    treeFileIn.close();

    // 测量解码时间
    auto startDecode = std::chrono::high_resolution_clock::now();
    // 用反序列化的哈夫曼树解码
    auto decodedData = decodeHuffman(encodedFileData, deserializedRoot);
    auto endDecode = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> decodeDuration =
        endDecode - startDecode;

    writeFile(("decoded" + extension).c_str(), decodedData);

    // 计算压缩率
    double originalSize = originalData.size();
    double compressedSize = encodedData.size();
    double compressionRate =
        (originalSize - compressedSize) / originalSize * 100;
    // if (compressionRate < 1e-3) compressionRate = 0;

    std::cout << "原始文件: " << filePath << std::endl;
    std::cout << "编码后文件: encoded.bin" << std::endl;
    std::cout << "哈夫曼树文件: tree.bin" << std::endl;
    std::cout << "哈夫曼树可读形式: tree.txt" << std::endl;
    std::cout << "解码后文件: decoded" << extension << std::endl;
    std::cout << "压缩率: " << compressionRate << "%" << std::endl;
    std::cout << "编码用时: " << encodeDuration.count() << " 毫秒" << std::endl;
    std::cout << "解码用时: " << decodeDuration.count() << " 毫秒" << std::endl;

    // macOS 系统调用
    system(("open " + filePath).c_str());  // 原始文件
    system("open tree.txt");               // 哈夫曼树的可读形式
    system(("open decoded" + extension).c_str());  // 解码后的文件

    delete[] data;
    delete[] freq;

    return 0;
}