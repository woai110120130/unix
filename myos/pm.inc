; 描述符图

; 图示===
;
;   图示w

; 段界限 %1  段及地址1a %2  段基地址1b %3   属性1 %4 属性2 %5 段基地之2 %6

;(1) P： 存在（Present位）。
;        p=1表示描述符对地址转换是有效的，或者说描述符所描述的段存在;即在内存中
;        p=0表示描述符对地址转换无效，即该段不存在，使用该描述副进行内存访问会引起异常。
;
;(2) DPL ：   表示描述符号特权级（Descriptor Privilege level），共2位 ，共2位。它规定了所描述段的特权级，用于特权检查，以及决定该段是否访问
;
;（3）S： 说明描述符的类型。
;              对于存储描述符而言，S=1，以区别与系统描述符和门描述符（S=0）
;
;（4）TYPE: 说明存储描述符所描述的存储段的具体属性。

;数据段类型      类型值          说明
;                       ----------------------------------
;                       0               只读
;                       1               只读、已访问
;                       2               读/写
;                       3               读/写、已访问
;                       4               只读、向下扩展
;                       5               只读、向下扩展、已访问
;                       6               读/写、向下扩展
;                       7               读/写、向下扩展、已访问
;
;
;                       类型值          说明
;       代码段类型      ----------------------------------
;                       8               只执行
;                       9               只执行、已访问
;                       A               执行/读
;                       B               执行/读、已访问
;                       C               只执行、一致码段
;                       D               只执行、一致码段、已访问
;                       E               执行/读、一致码段
;                       F               执行/读、一致码段、已访问
;
;
;       系统段类型      类型编码        说明
;                       ----------------------------------
;                       0               <未定义>
;                       1               可用286TSS
;                       2               LDT
;                       3               忙的286TSS
;                       4               286调用门
;                       5               任务门
;                       6               286中断门
;                       7               286陷阱门
;                       8               未定义
;                       9               可用386TSS
;                       A               <未定义>
;                       B               忙的386TSS
;                       C               386调用门
;                       D               <未定义>
;                       E               386中断门
;                       F               386陷阱门
;(5) G:  段界限粒度（Granularity）位
;            G=0表示界限粒度为字节
;            G=1表示界限粒度为4K
;        注意，界限粒度只对段界限有效，对段及地址无效，段及地址总是以自己为单位。
; （6）D： D位是一个很特殊的位，在描述可执行段.向下扩展数据段或者由SS寄存器寻址的段通常是堆栈段 的三种描述符中的意义各不相同。
;        （1）在描述可执行段的描述符中，D位据定了指令使用的地址以及操作书的默认的大小。
;               1 D=1表示默认的情况下使用32位地址以及32位或8位的操作数，这样的代码段也曾为32位代码段。
;              2 D=0  表示默认情况下指令使用16位地址以及16位或者8位操作数，这样的代码段也成为16位代码段，它与80286兼容。可以使用地址大小前缀和操作书大小前缀分别改变默认的地址或操作数大小。
;   
;       （2）在向下扩展的数据描述符中，D位决定段的上不界限
;                1 D=1 表示段的上部界限为4G
;                2 D=0 表示段的上部界限为64K
;       （3）    在描述由SS寄存器寻址的段描述符中，D位决定饮食的对战访问指令如PUS
;POP指令使用和中堆栈指针寄存器
;                 1 D=1 表示使用32位的堆栈指针寄存器ESP
;                 2 D=0 表示使用16位指针寄存器SP，这与80286兼容
;
;  (7) AVL： 软件可利用位。80386对该位的使用未作规定，Intel公司保证今后开发生产处理器只与80386兼容，就不会对该位使用做任何定义或规定
;


;----------------------------------------------------------------------------
;在下列类型值明明中：
; DA  : Descriptor  Attribute
; D   : 数据段
; C   : 代码段
; S   : 系统段
; R   : 只读
; RW  : 读写
; A   : 已访问
; 其他: 可以按照字面意思理解
;------------------------------------------------------------------------------

;描述副类型
DA_32             EQU        4000h   ; 32位段00000000 00000000 10000000 0000000

DA_DPL0           EQU          00h   ; PDL=0  0000 0000
DA_DPL1           EQU          20h   ; DPL=1  0010 0000
DA_DPL2           EQU          40h   ; DPL=1  0100 0000
DA_DPL3           EQU          60h   ; DPL=3  0110 0000


;存储段描述符类型 
DA_DR             EQU          90h ;存在的只读数据段的值1001 0000
DA_DRW            EQU          92h ;存在的读写数据段的值1001 0010
DA_DRWA           EQU          93h ;存在的以访问读写数据段的值1001 0011
DA_C              EQU          98h ;存在只执行代码段属性值1001 1000
DA_CR             EQU          9Ah ;存在的可执行可读代码段属性值1001 1010
DA_CCO            EQU          9Ch ;存在的可执行可读一致性代码属性值1001 1100
DA_CCOR           EQU          9Eh ;存在的可执行一致性代码属性值

; 系统段描述类型
DA_LDT            EQU          82h ; 局部描述符表段类型值 1000 0010
DA_TaskGate       EQU          85h ; 任务门类型值 1000 0101
DA_386TSS         EQU          89h ; 可用386任务状态段类型值 1000 1001
DA_386Gate        EQU          9Ch ; 386 调用门类型值
DA_386IGate       EQU          8Eh ; 386 陷阱门类型值
DA_386TGate       EQU          8Fh ; 386 陷阱门类型值

; PRL(Reqyested Privilege level)： 请求权限级，用于特权检查
;
; TI（Table Indicator）： 用用描述符表描述位
;      TI=1 指示从卷据描述附表GDT中读取描述符
;      TI=0 指示从局部描述符表LDT中读取描述符

;-----------------------------------------------------------------
;选择子类型值说明
;其中：
;      SA ：Selector Attrubute
SA_PRL0               EQU        0
SA_PRL1               EQU        1
SA_PRL2               EQU        2
SA_PRL3               EQU        3

SA_TIG                EQU        0
SA_TIL                EQU        4
;-------------------------------------------------------------------


;宏 ----------------------------------------------------------------------

;
;描述符
;usage : Descriptor Base Limit, Attr
;        Base: dd
;        Limit: dd(low 20 bits available)
;        Attr:  dw (lower 4 bits of higher byte are alawys 0) 
%macro Descriptor 3
    dw   %2 & 0FFFFh             ;段界限1
    dw   %1 & 0FFFFh             ;段及地址1
    db   (%1 >> 16) & 0FFh       ;段及地址2 
    db   ((%2 >> 8) & 0F00h) | (%3 & 0F0FFh) ; 属性1 + 段界限2 +属性2 
    db   (%1 >> 24) & 0FFh       ;段基地址3
%endmacro ;  共8字节
;
; 门
; usage: gate Selector , Offset, DCout, Attr
; Selector : dw
; Offset   : dd
; DCount   : db
; Attr     : db

%macro Gate 4
    dw    (%2 & 0FFFFh)                     ; 偏移1
    dw    %1                                ; 选择子
    dw    (%3 & 1Fh) | ((%4 << 8) & 0FF00h) ; 属性
    dw    ((%2 >> 16) & 0FFFFh)             ; 偏移 2
%endmacro ;共8字节

;--------------------------------------------------------------