# BrainFuck-interpreter
BrainFuck interpreter | BrainFuck解释器

<del>When I realized that this code was just big enough to fit into my embedded device...<br>当我发现这个代码的大小刚好能够塞进我的嵌入式设备时...</del>

I'm trying to implement a small BrainFuck interpreter and make it as small as possible.
<br>
我尝试实现一个小型的BrainFuck解释器，并且让它尽可能的小。



## Some small precautions | 注意事项

The default starting pointer position for this interpreter is 0.
<br>
这个解释器默认起始位置为0。

The default available memory size is 1048576 bytes (1 Mbyte).
<br>
默认内存大小为1MB。

## Command Line Parameters | 命令行参数
`BrainFuck <file|文件> [<option|可选参数>]`

Options|参数:

`show` Show commands on execution|执行时显示命令

`step` Single Step Execution|单步执行

`<number|数字>`  Set Memory Size|设置内存大小
