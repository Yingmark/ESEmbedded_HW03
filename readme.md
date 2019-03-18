HW03
===

##1. 作業HW_03題目
1. 參數間如何傳遞和返回參數? 描述應用程序二進制接口(ABI).
2. 修改main.c以觀察`Calling Conventions`.
--------------------
##2. 實驗步驟
1. 先將資料夾 gnu-mcu-eclipse-qemu 完整複製到ESEmbedded_HW03資料夾中.
2. 設計測試程式 main.c , 目標觀察參數如何移動.

main.s:
```assembly

void reset_handler(void)
{	
	func1(1,2,3);
	while (1)
		;
}

void func1(int a, int b, int c)
{
	return a+b+c;
}

```
3. 將main.c 編譯並以`qemu`進行模擬, `$ make clean`, `$ make`, `$ make qemu`;開啟另一視窗Terminal並連線 `$arm-none-eabi-gdb`, 在輸入`target remote localhost:1234`並連接
, 輸入兩次的`ctrl+x`在輸入`2`, 其可開啟暫存器視窗以及指令, 並輸`si`執行單步執行以方便觀察.
 - 以下為反組譯出來結果.

![](https://github.com/Yingmark/ESEmbedded_HW03/blob/master/img-folder/Disassembly.png)

觀看主程式時pc為`0x0000000c`發現依序把資料移入暫存器`r2`,`r1`,`r0`.

![](https://github.com/Yingmark/ESEmbedded_HW03/blob/master/img-folder/movs.png)

當程式執行至`bl 18`時, 執行跳轉指令把返回地址放入`r14暫存器(lr)`中;pc跳至`0x00000018`, 執行`push{r7}`之前`sp`位址為`0x200000f8`, 程式第`0x0000001e`執行`str r0, [r7, #12]`將`r0`中的值寫入`r7+12`位址暫存器裡, 以此類推.

![](https://github.com/Yingmark/ESEmbedded_HW03/blob/master/img-folder/str.png)

而當主程式要跳入副程式時, 反組譯結果會以指令`bl <address>`, 而當返回主程式時, 以指令`bx lr`;`bl`是將當前指令位址保存至`lr`暫存器中, 而`bx lr`為具有切換狀態的跳轉,當`LSB`為`HIGH`時, 切換至Thumb;若為`LOW`則狀態會更改為arm.

可得參數是利用暫存器`r0~r3`進行傳輸.


--------------------
- [] **If you volunteer to give the presentation next week, check this.**

--------------------
