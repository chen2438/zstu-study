## String 常用方法

在C#中，string是一个非常常用的类型，表示一个不可变的Unicode字符序列。以下是一些常用的string方法：

1. Length：获取字符串的长度。

```csharp
string str = "Hello, world!";
int length = str.Length; // length = 13
```

2. IndexOf：查找子字符串在字符串中第一次出现的位置，返回其索引值。如果未找到子字符串，则返回-1。

```csharp
string str = "Hello, world!";
int index = str.IndexOf("world"); // index = 7
```

3. Substring：从字符串中提取一个子字符串，可以通过指定其起始位置和长度来实现。

```csharp
string str = "Hello, world!";
string substr1 = str.Substring(7, 5); // substr1 = "world"
string substr2 = str.Substring(0, 5); // substr2 = "Hello"
```

4. Replace：替换字符串中的指定子字符串。

```csharp
string str = "Hello, world!";
string newStr = str.Replace("world", "universe"); // newStr = "Hello, universe!"
```

5. ToUpper和ToLower：分别将字符串转换为大写和小写。

```csharp
string str = "Hello, world!";
string upperStr = str.ToUpper(); // upperStr = "HELLO, WORLD!"
string lowerStr = str.ToLower(); // lowerStr = "hello, world!"
```

6. Trim：去除字符串开头和结尾的空格字符。

```csharp
string str = "   Hello, world!   ";
string trimmedStr = str.Trim(); // trimmedStr = "Hello, world!"
```

7. StartsWith和EndsWith：分别检查字符串是否以指定的子字符串开头或结尾，返回True或False。

```csharp
string str = "Hello, world!";
bool startsWith = str.StartsWith("Hello"); // startsWith = True
bool endsWith = str.EndsWith("!"); // endsWith = True
```

8. Contains：检查字符串是否包含指定的子字符串，返回True或False。

```csharp
string str = "Hello, world!";
bool contains = str.Contains("world"); // contains = True
```

这些方法只是string类型中可用的一小部分。C#中的string类型还具有许多其他有用的方法，可以帮助我们更轻松地处理字符串。需要注意的是，由于string是一个不可变类型，因此在使用这些方法时，它们返回的都是新的字符串对象，并不会修改原始字符串。

## Array 常用方法

在C#中，数组是一种常用的数据结构，用于存储一组相同类型的元素。以下是一些常用的数组方法：

1. Length：获取数组的长度。

```csharp
int[] nums = { 1, 2, 3, 4, 5 };
int length = nums.Length; // length = 5
```

2. IndexOf：查找数组中指定元素的索引位置，返回其索引值。如果未找到元素，则返回-1。

```csharp
int[] nums = { 1, 2, 3, 4, 5 };
int index = Array.IndexOf(nums, 3); // index = 2
```

3. Sort：对数组进行排序。

```csharp
int[] nums = { 3, 1, 4, 2, 5 };
Array.Sort(nums); // nums = { 1, 2, 3, 4, 5 }
```

4. Clear：清空数组中的所有元素，将它们设置为默认值。

```csharp
int[] nums = { 1, 2, 3, 4, 5 };
Array.Clear(nums, 0, nums.Length); // nums = { 0, 0, 0, 0, 0 }
```

5. Copy：将一个数组的元素复制到另一个数组中。

```csharp
int[] nums1 = { 1, 2, 3, 4, 5 };
int[] nums2 = new int[nums1.Length];
Array.Copy(nums1, nums2, nums1.Length); // nums2 = { 1, 2, 3, 4, 5 }
```

6. Reverse：反转数组中的元素。

```csharp
int[] nums = { 1, 2, 3, 4, 5 };
Array.Reverse(nums); // nums = { 5, 4, 3, 2, 1 }
```

7. Resize：调整数组的大小。

```csharp
int[] nums = { 1, 2, 3 };
Array.Resize(ref nums, 5); // nums = { 1, 2, 3, 0, 0 }
```

8. Contains：检查数组是否包含指定的元素，返回True或False。

```csharp
int[] nums = { 1, 2, 3, 4, 5 };
bool contains = nums.Contains(3); // contains = True
```

这些方法只是数组中可用的一小部分。C#中的数组还具有许多其他有用的方法，可以帮助我们更轻松地处理数组。需要注意的是，这些方法大多数都是静态方法，可以直接通过Array类来调用。