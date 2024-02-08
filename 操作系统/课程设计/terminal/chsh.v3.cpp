#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// 用户类
class User {
   public:
    std::string username;       // 用户名
    std::string password;       // 密码
    std::string group;          // 用户组
    std::string homeDirectory;  // 家目录

    User(const std::string& username, const std::string& password,
         const std::string& group, const std::string& homeDirectory)
        : username(username),
          password(password),
          group(group),
          homeDirectory(homeDirectory) {}
};

// 文件系统节点
class FileSystemNode {
   public:
    std::string name;     // 文件或目录名,不包含路径
    bool isDirectory;     // 是否为目录
    std::string owner;    // 拥有者
    std::string group;    // 用户组
    std::string content;  // 文件内容
    std::map<std::string, FileSystemNode*> children;  // 目录内容
    std::string userPermissions;                      // 用户权限
    std::string groupPermissions;                     // 用户组权限
    std::string otherPermissions;                     // 其他用户权限
    FileSystemNode* parent;  // 指向父节点的指针
    bool isBeingEdited;      // 编辑状态

    FileSystemNode(std::string name, bool isDirectory, std::string owner,
                   std::string group,
                   std::string userPermissions = "rwx",  // 默认用户权限
                   std::string groupPermissions = "r-x",  // 默认用户组权限
                   std::string otherPermissions = "r-x",  // 默认其他用户权限
                   FileSystemNode* parent = nullptr)
        : name(name),
          isDirectory(isDirectory),
          owner(owner),
          group(group),
          userPermissions(userPermissions),
          groupPermissions(groupPermissions),
          otherPermissions(otherPermissions),
          parent(parent),
          isBeingEdited(false) {}

    ~FileSystemNode() {
        for (auto& child : children) {
            delete child.second;
        }
    }

    // 设置权限
    void setPermissions(const std::string& newPermissions) {
        // newPermissions 格式为 "rwxr-xr-x"
        if (newPermissions.size() == 9) {
            userPermissions = newPermissions.substr(0, 3);
            groupPermissions = newPermissions.substr(3, 3);
            otherPermissions = newPermissions.substr(6, 3);
        }
    }

    // 获取权限
    std::string getPermissions() const {
        return userPermissions + groupPermissions + otherPermissions;
    }

    // 格式化文件或目录的权限表示
    std::string formatPermissions() const {
        std::ostringstream oss;
        oss << (isDirectory ? 'd' : '-') << userPermissions << groupPermissions
            << otherPermissions << " " << owner << " " << group;
        return oss.str();
    }
};

// 文件系统类
class FileSystem {
   private:
    FileSystemNode* root;                         // 根目录
    FileSystemNode* current;                      // 工作目录
    FileSystemNode* home;                         // 家目录
    std::unordered_map<std::string, User> users;  // 所有用户

   public:
    User* currentUser = nullptr;  // 当前登录的用户

    FileSystem() {
        // 新建根目录
        root = new FileSystemNode("/", true, "root", "root");
        current = root;
        // 新建家目录
        home = new FileSystemNode("root", true, "root", "root", "rwx", "r-x",
                                  "r-x", root);
        root->children["root"] = home;
        // 添加root用户
        users.emplace(
            std::piecewise_construct, std::forward_as_tuple("root"),
            std::forward_as_tuple("root", "password", "root", "/root"));
        // currentUser = &users.find("root")->second;  // 默认root登录
    }

    ~FileSystem() { delete root; }

    // 根据路径查找节点
    FileSystemNode* getNodeByPath(const std::string& path) {
        if (path == "/") return root;

        // 验证路径格式
        if (path.empty() || path[0] != '/') {
            std::cerr << "Error: Only absolute paths are supported.\n";
            return nullptr;
        }

        // 分解路径
        std::vector<std::string> parts;
        std::istringstream iss(path);
        std::string part;
        while (std::getline(iss, part, '/')) {  // 分割路径
            if (!part.empty()) {                // 忽略尾随斜杠
                parts.push_back(part);
            }
        }

        // 遍历路径
        FileSystemNode* node = root;
        for (const auto& p : parts) {
            if (node->children.find(p) == node->children.end()) return nullptr;
            node = node->children[p];
        }
        return node;
    }
    // 编码文件内容，转义换行符
    static std::string encodeContent(const std::string& content) {
        std::string encoded;
        for (char c : content) {
            if (c == '\n') {
                encoded += "\\n";  // 换行符替换
            } else if (c == '\\') {
                encoded += "\\\\";  // 反斜杠替换
            } else {
                encoded += c;
            }
        }
        return encoded;
    }

    // 解码文件内容
    static std::string decodeContent(const std::string& encodedContent) {
        std::string content;
        for (size_t i = 0; i < encodedContent.length(); i++) {
            if (encodedContent[i] == '\\' && i + 1 < encodedContent.length()) {
                if (encodedContent[i + 1] == 'n') {
                    content += '\n';
                    i++;
                } else if (encodedContent[i + 1] == '\\') {
                    content += '\\';
                    i++;
                } else {
                    content += encodedContent[i];
                }
            } else {
                content += encodedContent[i];
            }
        }
        return content;
    }

    // 保存文件系统到硬盘
    void saveToFile(const std::string& filename) {
        std::ofstream out(filename);
        if (!out) {
            std::cerr << "Error opening file for writing: " << filename
                      << std::endl;
            return;
        }
        saveNode(out, root, "");
        out.close();
    }

    // 从根目录开始保存每个节点
    void saveNode(std::ofstream& out, FileSystemNode* node,
                  const std::string& prefix) {
        if (node == nullptr) return;

        // 保存节点信息
        // prefix: 路径前缀
        out << prefix << node->name << " " << (node->isDirectory ? "d" : "f")
            << " " << node->owner << " " << node->group << " "
            << node->userPermissions << node->groupPermissions
            << node->otherPermissions << " " << node->isBeingEdited << " "
            << encodeContent(node->content) << "\n";

        // 递归保存子节点
        for (auto& child : node->children) {
            saveNode(out, child.second, prefix + node->name + "/");
        }
    }

    // 保存用户
    void saveUsersToFile(const std::string& filename) {
        std::ofstream out(filename, std::ios::out);
        if (!out) {
            std::cerr << "Error opening file for writing: " << filename
                      << std::endl;
            return;
        }

        for (const auto& userPair : users) {
            const User& user = userPair.second;
            out << user.username << " " << user.password << " " << user.group
                << " " << user.homeDirectory << "\n";
        }

        out.close();
    }

    // 从硬盘加载文件系统
    void loadFromFile(const std::string& filename) {
        std::ifstream in(filename);

        if (!in) {
            std::cerr << "Note: File not found, creating new file: " << filename
                      << std::endl;

            // 创建新文件
            std::ofstream outFile(filename);
            if (!outFile) {
                std::cerr << "Error creating file: " << filename << std::endl;
                return;
            }

            // 关闭新创建的文件并重新打开
            outFile.close();
            in.open(filename);

            // 再次失败，放弃操作
            if (!in) {
                std::cerr << "Error opening file after creating: " << filename
                          << std::endl;
                return;
            }
        }

        // 读取每一行
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            std::string path, type, owner, group, permissions, content;
            bool isBeingEdited;
            iss >> path >> type >> owner >> group >> permissions >>
                isBeingEdited >> content;

            FileSystemNode* node = getNodeByPath(path);
            if (node) {  // 检查节点是否存在
                // 更新已存在节点的属性
                node->owner = owner;
                node->group = group;
                node->setPermissions(permissions);
                node->isBeingEdited = isBeingEdited;
                if (type != "d") {  // 不是目录,设置内容
                    node->content = decodeContent(content);
                }
            } else {
                // 创建新节点
                create(path, type == "d", owner, group);
                node = getNodeByPath(path);
                if (node) {
                    node->setPermissions(permissions);
                    node->isBeingEdited = isBeingEdited;
                    if (type != "d") {
                        node->content = decodeContent(content);
                    }
                }
            }
        }
        in.close();
    }

    void loadUsersFromFile(const std::string& filename) {
        std::ifstream in(filename, std::ios::in);
        if (!in) {
            std::cerr << "Error opening file for reading: " << filename
                      << std::endl;
            return;
        }

        std::string username, password, group, homeDirectory;
        while (in >> username >> password >> group >> homeDirectory) {
            users.emplace(std::piecewise_construct,
                          std::forward_as_tuple(username),
                          std::forward_as_tuple(username, password, group,
                                                homeDirectory));
            // users[username] = User(username, password, group, homeDirectory);
        }

        in.close();
    }

    // 设置权限
    void setPermissions(const std::string& path,
                        const std::string& newPermissions) {
        FileSystemNode* node = getNodeByPath(path);
        if (!node) {
            std::cerr << "Error: File or directory does not exist\n";
            return;
        }
        node->setPermissions(newPermissions);
    }

    // 获取权限
    std::string getPermissions(const std::string& path) {
        FileSystemNode* node = getNodeByPath(path);
        if (!node) {
            std::cerr << "Error: File or directory does not exist\n";
            return "";
        }
        return node->getPermissions();
    }

    // 新增用户
    void addUser(const std::string& username, const std::string& password,
                 const std::string& group) {
        std::string homeDir = "/" + username;
        auto result = users.emplace(
            std::piecewise_construct, std::forward_as_tuple(username),
            std::forward_as_tuple(username, password, group, homeDir));
        if (result.second) {  // 插入成功
            // 检查家目录是否已存在
            if (!getNodeByPath(homeDir)) {
                // 创建家目录
                create(homeDir, true, username, group);
            }
        } else {
            std::cerr << "Error: User already exists\n";
        }
    }

    void changeUserPassword(const std::string& username,
                            const std::string& newPassword) {
        auto it = users.find(username);
        if (it == users.end()) {
            std::cerr << "Error: User does not exist\n";
            return;
        }
        it->second.password = newPassword;
        std::cout << "Password changed successfully for user: " << username
                  << std::endl;
    }

    bool login(const std::string& username, const std::string& password) {
        auto it = users.find(username);
        if (it == users.end() || it->second.password != password) {
            std::cerr << "Error: Invalid username or password\n";
            return false;
        }
        currentUser = &it->second;
        changeDirectory(currentUser->homeDirectory);
        return true;
    }

    // 检查权限
    bool checkPermissions(FileSystemNode* node, char permissionType) {
        // permissionType 检查的权限类型为r,w,x
        // if (currentUser->username == "root") {
        //     return true;  // root用户拥有所有权限
        // }
        std::string permissions = node->getPermissions();
        bool hasPermission = false;

        // 检查用户权限
        if (node->owner == currentUser->username) {
            hasPermission =
                permissions[permissionType == 'r'
                                ? 0
                                : (permissionType == 'w' ? 1 : 2)] != '-';
        }
        // 检查组权限
        else if (node->group == currentUser->group) {
            hasPermission =
                permissions[permissionType == 'r'
                                ? 3
                                : (permissionType == 'w' ? 4 : 5)] != '-';
        }
        // 检查其他用户权限
        else {
            hasPermission =
                permissions[permissionType == 'r'
                                ? 6
                                : (permissionType == 'w' ? 7 : 8)] != '-';
        }
        return hasPermission;
    }

    // 创建新文件或目录
    void create(const std::string& path, bool isDirectory,
                const std::string& owner, const std::string& group) {
        // 检查路径是否存在
        FileSystemNode* node = getNodeByPath(path);
        if (node) {
            std::cerr << "Error: File or directory already exists\n";
            return;
        }

        // 获取父目录路径和新节点名称
        size_t lastSlashPos = path.find_last_of('/');  // 查找最后斜杠的位置
        std::string parentPath;
        std::string name;
        if (lastSlashPos != std::string::npos) {        // 找到斜杠
            parentPath = path.substr(0, lastSlashPos);  // 提取父目录路径
            name = path.substr(lastSlashPos + 1);  // 提取新节点的名称
            if (parentPath.empty()) {              // 父目录是根目录
                parentPath = "/";
            }
        } else {
            // 没找到斜杠
            parentPath = "/";
            name = path;
        }

        // 获取父目录节点
        FileSystemNode* parent = getNodeByPath(parentPath);
        if (!parent || !parent->isDirectory) {
            std::cerr << "Error: Invalid path\n";
            return;
        }

        // 创建文件或目录
        FileSystemNode* newNode = new FileSystemNode(
            name, isDirectory, owner, group, "rwx", "r-x", "r-x", parent);
        // 将新节点添加到父目录的子节点
        parent->children[name] = newNode;
    }

    // 删除文件或目录
    void remove(const std::string& path) {
        if (path.empty() || path[0] != '/') {
            std::cerr << "Error: Only absolute paths are supported\n";
            return;
        }

        size_t lastSlashPos = path.find_last_of('/');
        std::string parentPath;  // 父目录路径
        if (lastSlashPos == 0) {
            // 删除的是根目录下的文件或目录
            parentPath = "/";
        } else {
            parentPath = path.substr(0, lastSlashPos);
        }
        std::string name = path.substr(lastSlashPos + 1);  // 节点名
        FileSystemNode* parent = getNodeByPath(parentPath);

        if (!parent || !parent->isDirectory ||
            parent->children.find(name) == parent->children.end()) {
            std::cerr << "Error: File or directory does not exist\n";
            return;
        }

        delete parent->children[name];  // 删除对象
        parent->children.erase(name);   // 删除map的键值对
    }

    // 更改当前工作目录
    void changeDirectory(const std::string& path) {
        if (path.empty() || path[0] != '/') {
            std::cerr << "Error: Only absolute paths are supported\n";
            return;
        }

        FileSystemNode* node = getNodeByPath(path);
        if (!node || !node->isDirectory) {
            std::cerr << "Error: Directory does not exist\n";
            return;
        }

        // 检查是否有读权限
        if (!checkPermissions(node, 'r')) {
            std::cerr << "Error: Permission denied\n";
            return;
        }

        current = node;
    }

    // 列出当前目录的内容
    void listDirectory(bool longFormat = false) {
        if (longFormat) {  // ls -l
            for (const auto& child : current->children) {
                std::cout << std::left << std::setw(10)
                          << child.second->formatPermissions() << " "
                          << child.first << "\n";
            }
        } else {  // ls
            for (const auto& child : current->children) {
                std::cout << (child.second->isDirectory ? "d " : "- ")
                          << child.first << "\n";  // d:目录,-:文件
            }
        }
    }

    // 读取文件内容
    void readFile(const std::string& path) {
        FileSystemNode* node = getNodeByPath(path);
        if (!node || node->isDirectory) {
            std::cerr << "Error: Invalid file path\n";
            return;
        }

        // 检查是否有读权限
        if (!checkPermissions(node, 'r')) {
            std::cerr << "Error: Permission denied\n";
            return;
        }

        // 检查文件是否正在被编辑
        loadFromFile("filesystem_state.txt");
        if (node->isBeingEdited) {
            std::cerr << "Error: File is currently being edited\n";
            return;
        }

        std::cout << node->content;
    }

    // 获取当前工作目录的绝对路径
    std::string getCurrentDirectoryPath() {
        std::vector<std::string> parts;
        FileSystemNode* node = current;
        while (node != nullptr && node != root) {  // 从当前节点向上找
            parts.push_back(node->name);
            node = node->parent;
        }
        std::reverse(parts.begin(), parts.end());
        std::string path = "/";
        for (const auto& part : parts) {
            path += part + "/";
        }
        return path;
    }
};

class SimpleShell {
   private:
    FileSystem fs;

    // 分割字符串
    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, delimiter)) {
            if (!token.empty()) tokens.push_back(token);
        }
        return tokens;
    }

    // login命令
    void login(const std::vector<std::string>& args) {
        if (args.size() != 2) {
            std::cerr << "Usage: login <username> <password>" << std::endl;
            return;
        }
        if (!fs.login(args[0], args[1])) {
            std::cerr << "Login failed for user: " << args[0] << std::endl;
        } else {
            std::cout << "Logged in as " << args[0] << std::endl;
        }
    }

    void changePassword(const std::vector<std::string>& args) {
        if (args.size() != 2) {
            std::cerr << "Usage: passwd <username> <newpassword>" << std::endl;
            return;
        }
        fs.changeUserPassword(args[0], args[1]);
    }

    // vim命令
    void editFile(const std::string& filename) {
        FileSystemNode* fileNode = fs.getNodeByPath(filename);
        if (!fileNode) {
            std::cout << "File does not exist. Creating new file: " << filename
                      << std::endl;
            // 不存在则创建文件
            fs.create(filename, false, fs.currentUser->username,
                      fs.currentUser->group);
            fileNode = fs.getNodeByPath(filename);
        }
        if (fileNode->isDirectory) {
            std::cerr << "Error: Path is a directory\n";
            return;
        }
        // 检查写权限
        if (!fs.checkPermissions(fileNode, 'w')) {
            std::cerr << "Error: Permission denied.\n";
            return;
        }
        // 读取读写状态
        fs.loadFromFile("filesystem_state.txt");
        if (fileNode->isBeingEdited) {
            std::cerr << "Error: File is currently being edited\n";
            return;
        }
        fileNode->isBeingEdited = true;
        fs.saveToFile("filesystem_state.txt");

        // 显示文件内容 进入插入模式
        std::cout << "Entering insert mode for file: " << filename << std::endl;
        std::cout << fileNode->content;

        // 编辑文件内容
        std::string newContent = fileNode->content;
        std::string inputLine;
        while (std::getline(std::cin, inputLine)) {
            if (inputLine == ":wq") {
                // 保存并退出
                fileNode->content = newContent;
                std::cout << "File saved and exiting editor." << std::endl;
                break;
            } else {
                // 添加新行
                newContent += inputLine + "\n";
            }
        }
        fileNode->isBeingEdited = false;
    }

    // 数字权限转换为字符权限
    std::string convertNumericToSymbolic(const std::string& numeric) {
        if (numeric.size() != 3) return "";

        std::string symbolic;
        const std::string rwx[8] = {"---", "--x", "-w-", "-wx",
                                    "r--", "r-x", "rw-", "rwx"};

        for (char c : numeric) {
            if (c < '0' || c > '7') return "";  // 非法数字
            symbolic += rwx[c - '0'];
        }

        return symbolic;
    }

    void executeCommand(const std::string& command,
                        const std::vector<std::string>& args) {
        if (command == "login") {
            login(args);
        } else {
            // 检查用户登录
            if (fs.currentUser == nullptr) {
                std::cerr << "Error: No user logged in" << std::endl;
                return;
            } else if (command == "chmod") {
                if (args.size() != 2) {
                    std::cerr
                        << "Usage: chmod <permissions> <filename/directory>"
                        << std::endl;
                    return;
                }
                // 将数字权限转换为字符权限
                std::string symbolicPermissions =
                    convertNumericToSymbolic(args[0]);
                if (symbolicPermissions.empty()) {
                    std::cerr << "Invalid numeric permissions: " << args[0]
                              << std::endl;
                    return;
                }
                fs.setPermissions(args[1], symbolicPermissions);
            } else if (command == "getperm") {
                if (args.size() != 1) {
                    std::cerr << "Usage: getperm <filename/directory>"
                              << std::endl;
                    return;
                }
                std::cout << fs.getPermissions(args[0]) << std::endl;
            } else if (command == "pwd") {
                std::cout << fs.getCurrentDirectoryPath() << std::endl;
            } else if (command == "cd") {
                if (args.size() == 1) {
                    fs.changeDirectory(args[0]);
                } else {
                    std::cerr << "Usage: cd [directory]" << std::endl;
                    return;
                }
            } else if (command == "ls") {
                bool longFormat = !args.empty() && args[0] == "-l";
                fs.listDirectory(longFormat);
            } else if (command == "touch") {
                if (args.size() != 1) {
                    std::cerr << "Usage: touch <filename>" << std::endl;
                    return;
                }
                fs.create(args[0], false, fs.currentUser->username,
                          fs.currentUser->group);
            } else if (command == "rm") {
                if (args.size() != 1) {
                    std::cerr << "Usage: rm <filename/directory>" << std::endl;
                    return;
                }
                fs.remove(args[0]);
            } else if (command == "mkdir") {
                if (args.size() != 1) {
                    std::cerr << "Usage: mkdir <directory>" << std::endl;
                    return;
                }
                fs.create(args[0], true, fs.currentUser->username,
                          fs.currentUser->group);
            } else if (command == "rmdir") {
                if (args.size() != 1) {
                    std::cerr << "Usage: rmdir <directory>" << std::endl;
                    return;
                }
                fs.remove(args[0]);
            } else if (command == "cat") {
                if (args.size() != 1) {
                    std::cerr << "Usage: cat <filename>" << std::endl;
                    return;
                }
                fs.readFile(args[0]);
            } else if (command == "vim") {
                if (args.size() != 1) {
                    std::cerr << "Usage: vim <filename>" << std::endl;
                    return;
                }
                editFile(args[0]);
            } else if (command == "adduser") {
                if (args.size() != 2) {
                    std::cerr << "Usage: adduser <username> <password>"
                              << std::endl;
                    return;
                }
                fs.addUser(args[0], args[1], "users");  // 默认用户组为"users"
            } else if (command == "su") {
                if (args.size() != 2) {
                    std::cerr << "Usage: su <username> <password>" << std::endl;
                    return;
                }
                if (!fs.login(args[0], args[1])) {
                    std::cerr << "Switch user failed for user: " << args[0]
                              << std::endl;
                } else {
                    std::cout << "Switched to user " << args[0] << std::endl;
                }
            } else if (command == "passwd") {
                if (args.size() != 2) {
                    std::cerr << "Usage: passwd <username> <newpassword>"
                              << std::endl;
                    return;
                }
                fs.changeUserPassword(args[0], args[1]);
            } else {
                std::cerr << "Unknown command: " << command << std::endl;
            }
        }
    }

   public:
    void run() {
        std::string line;
        while (true) {
            fs.loadFromFile("filesystem_state.txt");
            fs.loadUsersFromFile("users.txt");

            std::cout << fs.getCurrentDirectoryPath()
                      << "$ ";  // 当前工作目录和提示符
            std::getline(std::cin, line);

            if (line == "exit") {
                fs.saveToFile("filesystem_state.txt");
                fs.saveUsersToFile("users.txt");
                std::cout << "logout" << std::endl;
                break;
            }
            std::vector<std::string> tokens = split(line, ' ');
            if (tokens.empty()) continue;

            std::string command = tokens[0];
            std::vector<std::string> args(tokens.begin() + 1, tokens.end());
            executeCommand(command, args);
            fs.saveToFile("filesystem_state.txt");
            fs.saveUsersToFile("users.txt");
        }
    }
};

int main() {
    SimpleShell shell;
    shell.run();
    return 0;
}
