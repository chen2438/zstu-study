简单的Windows C++ WndProc函数的例子：

```cpp
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch (message){
        case WM_PAINT:{
            // 在窗口客户区域绘制图形
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在这里进行绘制操作
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_CLOSE:{
            // 关闭窗口
            DestroyWindow(hWnd);
            break;
        }
        case WM_DESTROY:{
            // 退出程序
            PostQuitMessage(0);
            break;
        }
        default:
            // 处理所有其他消息
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
```

该函数是Windows消息处理程序的核心，它处理窗口消息并响应它们。在该函数中，我们使用了一个switch语句来检查消息类型，并根据消息类型执行不同的操作。在本例中，我们处理了三个消息类型：WM_PAINT，WM_CLOSE和WM_DESTROY。

在WM_PAINT消息中，我们使用BeginPaint和EndPaint函数来获取和释放绘图设备环境（HDC），并在窗口客户区域绘制图形。在WM_CLOSE消息中，我们使用DestroyWindow函数来关闭窗口。在WM_DESTROY消息中，我们使用PostQuitMessage函数来退出程序。

如果收到的消息不是上述三种类型之一，则使用DefWindowProc函数将消息传递给默认窗口过程进行处理。最后，我们返回0以指示消息已被处理。