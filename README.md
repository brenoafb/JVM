# JVM

Java .class file reader for Java SE 8 and virtual machine for a subset of the JVM instruction set.

## Building

```
make
```

## Running a class file

To run a Java 8 `class` file, use the `i` flag.

```
❯ ./main samples/MemoizedFibonacci i
memoFib(0)
0
memoFib(1)
1
memoFib(2)
1
memoFib(3)
2
memoFib(10)
55
memoFib(25)
75025
```

## Printing class file information

To print information about a Java `class` file, use the `le` flag.

```
❯ ./main samples/PrintInt le
class PrintInt
	minor version: 0
	major version: 52
	J2SE 8.0
	flags: ACC_PUBLIC ACC_SUPER
Constant pool:
	#1	= Methodref	java/lang/Object.<init>:()V (#5.#14)
	#2	= Fieldref	java/lang/System.out:Ljava/io/PrintStream; (#15.#16)
	#3	= Methodref	java/io/PrintStream.println:(I)V (#17.#18)
	#4	= Class	PrintInt (#19)
	#5	= Class	java/lang/Object (#20)
	#6	= Utf8:	<init>
	#7	= Utf8:	()V
	#8	= Utf8:	Code
	#9	= Utf8:	LineNumberTable
	#10	= Utf8:	main
	#11	= Utf8:	([Ljava/lang/String;)V
	#12	= Utf8:	SourceFile
	#13	= Utf8:	PrintInt.java
	#14	= NameAndType	<init>:()V (#6:#7)
	#15	= Class	java/lang/System (#21)
	#16	= NameAndType	out:Ljava/io/PrintStream; (#22:#23)
	#17	= Class	java/io/PrintStream (#24)
	#18	= NameAndType	println:(I)V (#25:#26)
	#19	= Utf8:	PrintInt
	#20	= Utf8:	java/lang/Object
	#21	= Utf8:	java/lang/System
	#22	= Utf8:	out
	#23	= Utf8:	Ljava/io/PrintStream;
	#24	= Utf8:	java/io/PrintStream
	#25	= Utf8:	println
	#26	= Utf8:	(I)V
Interfaces: (Count: 0) {
}
Fields: (Count: 0) {
}
Methods: (Count: 2) {
	<init>
	Descriptor: ()V
	Flags: ACC_PUBLIC
		Code:	(Lenght: 29)
		stack=1, locals=1
		0	aload_0	(0x2a)
		1	invokespecial #1  java/lang/Object.<init>:()V	(0xb7)
		4	return	(0xb1)
		LineNumberTable:	(Lenght: 6)
		line 1: 0

	main
	Descriptor: ([Ljava/lang/String;)V
	Flags: ACC_PUBLIC ACC_STATIC
		Code:	(Lenght: 49)
		stack=2, locals=1
		0	getstatic #2  java/lang/System.out:Ljava/io/PrintStream;	(0xb2)
		3	bipush 12	(0x10)
		5	invokevirtual #3  java/io/PrintStream.println:(I)V	(0xb6)
		8	getstatic #2  java/lang/System.out:Ljava/io/PrintStream;	(0xb2)
		11	bipush 223	(0x10)
		13	invokevirtual #3  java/io/PrintStream.println:(I)V	(0xb6)
		16	return	(0xb1)
		LineNumberTable:	(Lenght: 14)
		line 3: 0
		line 4: 8
		line 5: 16

}
		SourceFile:	(Lenght: 2)  "PrintInt.java"

```



