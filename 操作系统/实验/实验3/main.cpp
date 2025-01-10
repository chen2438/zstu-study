#include <algorithm>
#include <iostream>
#include <list>

struct MemoryBlock {
    int startAddress;
    int size;
    std::string status;  // "操作系统", "作业X", "空闲区"

    MemoryBlock(int start, int sz, std::string st)
        : startAddress(start), size(sz), status(st) {}
};

bool compareMemoryBlock(const MemoryBlock& a, const MemoryBlock& b) {
    return a.size < b.size;
}

void initializeMemory(std::list<MemoryBlock>& freeList,
                      std::list<MemoryBlock>& allocatedList) {
    // 内存容量为256K
    // 已分配区
    allocatedList.push_back(MemoryBlock(0, 10, "操作系统"));
    allocatedList.push_back(MemoryBlock(10, 10, "作业1"));
    allocatedList.push_back(MemoryBlock(20, 25, "作业4"));
    allocatedList.push_back(MemoryBlock(65, 45, "作业2"));

    // 空闲区
    freeList.push_back(MemoryBlock(45, 20, "空闲区"));
    freeList.push_back(MemoryBlock(110, 146, "空闲区"));
}

bool allocateMemory(std::list<MemoryBlock>& freeList,
                    std::list<MemoryBlock>& allocatedList, int size,
                    std::string jobName) {
    std::cout << "为" << jobName << "分配" << size << "空间: ";
    auto bestFit = freeList.end();

    // 找最佳适应块
    for (auto it = freeList.begin(); it != freeList.end(); ++it) {
        if (it->size >= size &&
            (bestFit == freeList.end() || it->size < bestFit->size)) {
            bestFit = it;
        }
    }

    if (bestFit != freeList.end()) {
        // 分配内存
        allocatedList.push_back(
            MemoryBlock(bestFit->startAddress, size, jobName));

        // 更新空闲区块
        bestFit->startAddress += size;
        bestFit->size -= size;

        if (bestFit->size == 0) {
            freeList.erase(bestFit);
        }
        std::cout << "分配成功" << std::endl;
        return true;
    }
    std::cout << "分配失败" << std::endl;
    return false;
}

void deallocateMemory(std::list<MemoryBlock>& freeList,
                      std::list<MemoryBlock>& allocatedList,
                      std::string jobName) {
    std::cout << "为" << jobName << "回收空间" << std::endl;
    for (auto it = allocatedList.begin(); it != allocatedList.end(); ++it) {
        if (it->status == jobName) {
            int start = it->startAddress;
            int size = it->size;

            // 从已分配列表中删除
            allocatedList.erase(it);

            // 合并空闲区块
            for (auto fit = freeList.begin(); fit != freeList.end();) {
                if (fit->startAddress + fit->size ==
                    start) {  // 空闲区块在回收区块前
                    size += fit->size;
                    start = fit->startAddress;
                    fit = freeList.erase(fit);
                } else if (start + size ==
                           fit->startAddress) {  // 空闲区块在回收区块后
                    size += fit->size;
                    fit = freeList.erase(fit);
                } else {
                    ++fit;
                }
            }

            // 加入新空闲区块
            freeList.push_back(MemoryBlock(start, size, "空闲区"));
            freeList.sort([](const MemoryBlock& a, const MemoryBlock& b) {
                return a.startAddress < b.startAddress;
            });
            break;
        }
    }
}

void printMemoryState(const std::list<MemoryBlock>& freeList,
                      const std::list<MemoryBlock>& allocatedList) {
    std::list<MemoryBlock> mergedList = freeList;
    mergedList.insert(mergedList.end(), allocatedList.begin(),
                      allocatedList.end());

    mergedList.sort([](const MemoryBlock& a, const MemoryBlock& b) {
        return a.startAddress < b.startAddress;
    });

    std::cout << "主存状态：" << std::endl;
    for (const auto& block : mergedList) {
        std::cout << "起始地址：" << block.startAddress << ", 长度："
                  << block.size << ", 状态：" << block.status << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    std::list<MemoryBlock> freeList;
    std::list<MemoryBlock> allocatedList;

    // 初始化
    initializeMemory(freeList, allocatedList);
    printMemoryState(freeList, allocatedList);

    std::string command, jobName;
    int size;

    while (true) {
        std::cout
            << "输入命令（alloc <作业名> <大小> | dealloc <作业名> | exit）: ";
        std::cin >> command;

        if (command == "alloc") {
            std::cin >> jobName >> size;
            if (!allocateMemory(freeList, allocatedList, size, jobName)) {
                std::cout << "内存分配失败。" << std::endl;
            }
            printMemoryState(freeList, allocatedList);
        } else if (command == "dealloc") {
            std::cin >> jobName;
            deallocateMemory(freeList, allocatedList, jobName);
            printMemoryState(freeList, allocatedList);
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "无效命令。" << std::endl;
        }
    }

    return 0;
}
